/*BHEADER**********************************************************************
 * Copyright (c) 2014,  Lawrence Livermore National Security, LLC.
 * Produced at the Lawrence Livermore National Laboratory.
 * This file is part of HYPRE.  See file COPYRIGHT for details.
 *
 * HYPRE is free software; you can redistribute it and/or modify it under the
 * terms of the GNU Lesser General Public License (as published by the Free
 * Software Foundation) version 2.1 dated February 1999.
 *
 * $Revision$
 ***********************************************************************EHEADER*/

#include "_hypre_sstruct_mv.h"

#define DEBUG_MATMULT 0

/*--------------------------------------------------------------------------
 * hypre_SStructMatmult
 *
 * Recursive multiplication of SStructMatrices A_i (i=1,...,n) computed as
 *
 * M_1 = A_1           = (sA_1 + uA_1)
 * M_2 = A_2 * M_1     = (sA_2 + uA_2) * (sM_1 + uM_1)
 *                     = sA_2*sM_1 + (sA_2*uM_1 + uA_2 * (sM_1 + uM_1))
 *                          \.../                 \.../
 *                           \./                   \./
 *                            |                     |
 *                     =    sM_2   +              uM_2
 * ...
 * M_n = A_n * M_{n-1} = (sA_n + uA_n) * (sM_{n-1} + uM_{n-1})
 *                     = sA_n*sM_{n-1} + (sA_n*uM_{n-1} + uA_n * (sM_{n-1} + uM_{n-1}))
 *                           \.../                         \.../
 *                            \./                           \./
 *                             |                             |
 *                     =    sM_n       +                   uM_n
 *
 * Notes:
 *         1) A is transposed in each call to hypre_ParTMatmul. This operation
 *            could be done only once and At reused...
 *         2) Should we phase out domain grid and have only a base grid?
 *--------------------------------------------------------------------------*/
HYPRE_Int
hypre_SStructMatmult( HYPRE_Int             nmatrices,
                      hypre_SStructMatrix **ssmatrices,
                      HYPRE_Int             nterms,
                      HYPRE_Int            *terms,
                      HYPRE_Int            *transposes,
                      hypre_SStructMatrix **M_ptr )
{
   MPI_Comm                 comm   = hypre_SStructMatrixComm(ssmatrices[0]);
   HYPRE_Int                ndim   = hypre_SStructMatrixNDim(ssmatrices[0]);
   HYPRE_Int                nparts = hypre_SStructMatrixNParts(ssmatrices[0]);
   hypre_SStructMatrix     *M;
   hypre_SStructGraph      *graph_M;
   hypre_SStructGrid       *grid_M;
   hypre_SStructPMatrix    *pmatrix;
   hypre_StructMatrix     **smatrices;   /* nmatrices array */
   hypre_StructMatrix     **smatrices_M; /* nparts array */

   /* Temporary data structures */
   hypre_ParCSRMatrix     **parcsr;
   hypre_ParCSRMatrix      *parcsr_sA;
   hypre_ParCSRMatrix      *parcsr_uA;
   hypre_ParCSRMatrix      *parcsr_uM;
   hypre_ParCSRMatrix      *parcsr_uMold;
   hypre_ParCSRMatrix      *parcsr_sM;
   hypre_ParCSRMatrix      *parcsr_sMold;
   hypre_IJMatrix          *ijmatrix;
   hypre_IJMatrix         **ij_sA;
   hypre_IJMatrix          *ij_M;

   /* Stencil data */
   hypre_StructStencil     *stencil_M;
   hypre_SStructStencil   **stencils_M;
   hypre_Index             *stencil_shape_M;
   HYPRE_Int                stencil_size_M;

   /* This function works for a single variable type only */
   HYPRE_Int                vi = 0, vj = 0;
   HYPRE_Int                m, s, t;
   HYPRE_Int                part;

   HYPRE_ANNOTATE_FUNC_BEGIN;

   /*-------------------------------------------------------
    * Safety checks
    *-------------------------------------------------------*/

   /* TODO: add a check for the number and types of variables */

   /* TODO: check if we can multiply each of the matrices */

   /*-------------------------------------------------------
    * Compute structured component
    *-------------------------------------------------------*/
   smatrices   = hypre_TAlloc(hypre_StructMatrix *, nmatrices);
   smatrices_M = hypre_TAlloc(hypre_StructMatrix *, nparts);
   stencils_M  = hypre_TAlloc(hypre_SStructStencil *, nparts);
   for (part = 0; part < nparts; part++)
   {
      for (m = 0; m < nmatrices; m++)
      {
         pmatrix = hypre_SStructMatrixPMatrix(ssmatrices[m], part);
         smatrices[m] = hypre_SStructPMatrixSMatrix(pmatrix, vi, vj);
      }

      /* Multiply StructMatrices (part, vi, vj)-block */
      hypre_StructMatmult(nmatrices, smatrices, nterms, terms,
                          transposes, &smatrices_M[part]);

      /* Create SStructStencil object for M */
      stencil_M       = hypre_StructMatrixStencil(smatrices_M[part]);
      stencil_size_M  = hypre_StructStencilSize(stencil_M);
      stencil_shape_M = hypre_StructStencilShape(stencil_M);

      HYPRE_SStructStencilCreate(ndim, stencil_size_M, &stencils_M[part]);
      for (s = 0; s < stencil_size_M; s++)
      {
         HYPRE_SStructStencilSetEntry(stencils_M[part], s, stencil_shape_M[s], vj);
      }
   }

   /*-------------------------------------------------------
    * Compute unstructured component
    *-------------------------------------------------------*/

   /* Temporary work matrices */
   parcsr = hypre_TAlloc(hypre_ParCSRMatrix *, 3);
   ij_sA  = hypre_TAlloc(hypre_IJMatrix *, nmatrices);
   for (m = 0; m < nmatrices; m++)
   {
      ij_sA[m] = NULL;
   }

   /* Set initial data */
   t = terms[nmatrices - 2];
   ijmatrix = hypre_SStructMatrixIJMatrix(ssmatrices[t]);
   HYPRE_IJMatrixGetObject(ijmatrix, (void **) &parcsr_uM);

   t = terms[nmatrices - 1];
   ijmatrix = hypre_SStructMatrixIJMatrix(ssmatrices[t]);
   HYPRE_IJMatrixGetObject(ijmatrix, (void **) &parcsr_uMold);
   hypre_SStructMatrixBoundaryToUMatrix(ssmatrices[t], parcsr_uM, &ij_sA[t]);
   //ij_sA[t] = hypre_SStructMatrixToUMatrix(ssmatrices[t]);
   HYPRE_IJMatrixGetObject(ij_sA[t], (void **) &parcsr_sMold);

#if DEBUG_MATMULT
   char matname[64];

   hypre_ParCSRMatrixPrintIJ(parcsr_uMold, 0, 0, "parcsr_uP");
   hypre_ParCSRMatrixPrintIJ(parcsr_sMold, 0, 0, "parcsr_sP");
#endif

   /* Compute M recursively */
   for (m = (nmatrices - 2); m >= 0; m--)
   {
      t = terms[m];

      /* Convert sA_n to IJMatrix */
      if (ij_sA[t] == NULL)
      {
         hypre_SStructMatrixBoundaryToUMatrix(ssmatrices[t], parcsr_uMold, &ij_sA[t]);
      }
      HYPRE_IJMatrixGetObject(ij_sA[t], (void **) &parcsr_sA);
#if DEBUG_MATMULT
      hypre_sprintf(matname, "parcsr_sA_%d", m);
      hypre_ParCSRMatrixPrintIJ(parcsr_sA, 0, 0, matname);
#endif

      /* 1) Compute sA_n*uMold */
      if (transposes[m])
      {
         parcsr[0] = hypre_ParTMatmul(parcsr_sA, parcsr_uMold);
      }
      else
      {
         parcsr[0] = hypre_ParMatmul(parcsr_sA, parcsr_uMold);
      }
#if DEBUG_MATMULT
      hypre_sprintf(matname, "parcsr_0a_%d", m);
      hypre_ParCSRMatrixPrintIJ(parcsr[0], 0, 0, matname);
#endif

      /* 2) Compute uA_n*uMold */
      ijmatrix = hypre_SStructMatrixIJMatrix(ssmatrices[t]);
      HYPRE_IJMatrixGetObject(ijmatrix, (void **) &parcsr_uA);
#if DEBUG_MATMULT
      hypre_sprintf(matname, "parcsr_uA_%d", m);
      hypre_ParCSRMatrixPrintIJ(parcsr_uA, 0, 0, matname);
#endif
      if (transposes[m])
      {
         parcsr[1] = hypre_ParTMatmul(parcsr_uA, parcsr_uMold);
      }
      else
      {
         parcsr[1] = hypre_ParMatmul(parcsr_uA, parcsr_uMold);
      }
#if DEBUG_MATMULT
      hypre_sprintf(matname, "parcsr_1_%d", m);
      hypre_ParCSRMatrixPrintIJ(parcsr[1], 0, 0, matname);
#endif

      if (m != (nmatrices - 2))
      {
         hypre_ParCSRMatrixDestroy(parcsr_uMold);
      }

      /* 3) Compute (sA_n*uMold + uA_n*uMold) */
      hypre_ParcsrAdd(1.0, parcsr[0], 1.0, parcsr[1], &parcsr[2]);
#if DEBUG_MATMULT
      hypre_sprintf(matname, "parcsr_2_%d", m);
      hypre_ParCSRMatrixPrintIJ(parcsr[2], 0, 0, matname);
#endif

      /* Free sA_n*uMold and uA_n*uMold */
      hypre_ParCSRMatrixDestroy(parcsr[0]);
      hypre_ParCSRMatrixDestroy(parcsr[1]);

      /* 4) Compute uA_n*sMold */
      if (transposes[m])
      {
         parcsr[0] = hypre_ParTMatmul(parcsr_uA, parcsr_sMold);
      }
      else
      {
         parcsr[0] = hypre_ParMatmul(parcsr_uA, parcsr_sMold);
      }
#if DEBUG_MATMULT
      hypre_sprintf(matname, "parcsr_0b_%d", m);
      hypre_ParCSRMatrixPrintIJ(parcsr[0], 0, 0, matname);
#endif

      /* 5) Compute (uA_n*uMold + sA_n*uMold + uA_n*uMold) */
      hypre_ParcsrAdd(1.0, parcsr[0], 1.0, parcsr[2], &parcsr_uM);
#if DEBUG_MATMULT
      hypre_sprintf(matname, "parcsr_uM_%d", m);
      hypre_ParCSRMatrixPrintIJ(parcsr_uM, 0, 0, matname);
#endif

      /* Free temporary work matrices */
      hypre_ParCSRMatrixDestroy(parcsr[0]);
      hypre_ParCSRMatrixDestroy(parcsr[2]);

      /* 6) Compute sA_n*sMold */
      if (transposes[m])
      {
         parcsr_sM = hypre_ParTMatmul(parcsr_sA, parcsr_sMold);
      }
      else
      {
         parcsr_sM = hypre_ParMatmul(parcsr_sA, parcsr_sMold);
      }
#if DEBUG_MATMULT
      hypre_sprintf(matname, "parcsr_sM_%d", m);
      hypre_ParCSRMatrixPrintIJ(parcsr_sM, 0, 0, matname);
#endif

      if (m < (nmatrices - 2))
      {
         hypre_ParCSRMatrixDestroy(parcsr_sMold);
      }

      /* 7) Update pointers */
      parcsr_sMold = parcsr_sM;
      parcsr_uMold = parcsr_uM;
   }

   /* Free temporary work matrices */
   hypre_TFree(parcsr);
   hypre_ParCSRMatrixDestroy(parcsr_sM);
   for (m = 0; m < nmatrices; m++)
   {
      if (ij_sA[m] != NULL)
      {
         HYPRE_IJMatrixDestroy(ij_sA[m]);
      }
   }
   hypre_TFree(ij_sA);

   /*-------------------------------------------------------
    * Create the resulting SStructMatrix
    *-------------------------------------------------------*/

   /* Create graph_M */
   grid_M = hypre_SStructGraphDomGrid(hypre_SStructMatrixGraph(ssmatrices[1]));
   HYPRE_SStructGraphCreate(comm, grid_M, (HYPRE_SStructGraph*) &graph_M);
   HYPRE_SStructGraphSetObjectType(graph_M, HYPRE_SSTRUCT);
   for (part = 0; part < nparts; part++)
   {
      HYPRE_SStructGraphSetStencil(graph_M, part, 0, stencils_M[part]);
   }
   HYPRE_SStructGraphAssemble(graph_M);

   /* Create matrix M */
   HYPRE_SStructMatrixCreate(comm, graph_M, &M);
   HYPRE_SStructMatrixInitialize(M);
   for (part = 0; part < nparts; part++)
   {
      pmatrix = hypre_SStructMatrixPMatrix(M, part);
      hypre_StructMatrixDestroy(hypre_SStructPMatrixSMatrix(pmatrix, vi, vj));
      hypre_SStructPMatrixSMatrix(pmatrix, vi, vj) = hypre_StructMatrixRef(smatrices_M[part]);
   }

   ij_M = hypre_SStructMatrixIJMatrix(M);
   hypre_IJMatrixDestroyParCSR(ij_M);
   hypre_IJMatrixObject(ij_M) = NULL;
   hypre_IJMatrixTranslator(ij_M) = NULL;
   hypre_IJMatrixAssembleFlag(ij_M) = 1;
   hypre_IJMatrixSetObject(ij_M, parcsr_uM);
   HYPRE_SStructMatrixAssemble(M);

   /*-------------------------------------------------------
    * Free memory
    *-------------------------------------------------------*/
   HYPRE_SStructGraphDestroy(graph_M);
   for (part = 0; part < nparts; part++)
   {
      hypre_StructMatrixDestroy(smatrices_M[part]);
      HYPRE_SStructStencilDestroy(stencils_M[part]);
   }
   hypre_TFree(smatrices);
   hypre_TFree(smatrices_M);
   hypre_TFree(stencils_M);

   /* Set pointer to output matrix */
   *M_ptr = M;

   HYPRE_ANNOTATE_FUNC_END;

   return hypre_error_flag;
}


/*--------------------------------------------------------------------------
 * hypre_SStructMatmult
 *--------------------------------------------------------------------------*/
HYPRE_Int
hypre_SStructMatPtAP( hypre_SStructMatrix   *P,
                      hypre_SStructMatrix   *A,
                      hypre_SStructMatrix  **PtAP_ptr )
{
   hypre_SStructMatrix  *matrices[3] = {A, P, P};
   HYPRE_Int             nmatrices   = 3;
   HYPRE_Int             nterms      = 3;
   HYPRE_Int             terms[3]    = {1, 0, 1};
   HYPRE_Int             trans[3]    = {1, 0, 0};

   hypre_SStructMatmult(nmatrices, matrices, nterms, terms, trans, PtAP_ptr);

   return hypre_error_flag;
}

/*--------------------------------------------------------------------------
 * Notes:
 *         *) Consider a single variable type for now.
 *--------------------------------------------------------------------------*/
HYPRE_Int
hypre_SStructMatrixBoundaryToUMatrix( hypre_SStructMatrix   *A,
                                      hypre_ParCSRMatrix    *B,
                                      hypre_IJMatrix       **ij_Ahat_ptr)
{
   MPI_Comm               comm     = hypre_SStructMatrixComm(A);
   HYPRE_Int              ndim     = hypre_SStructMatrixNDim(A);
   HYPRE_Int              nparts   = hypre_SStructMatrixNParts(A);
   HYPRE_Int             *Sentries = hypre_SStructMatrixSEntries(A);
   HYPRE_IJMatrix         ij_A     = hypre_SStructMatrixIJMatrix(A);
   hypre_SStructGraph    *graph    = hypre_SStructMatrixGraph(A);
   hypre_SStructGrid     *grid     = hypre_SStructGraphGrid(graph);
   hypre_SStructPGrid    *pgrid;
   hypre_StructGrid      *sgrid;
   hypre_SStructStencil  *stencil;

   hypre_SStructPMatrix  *pA;
   hypre_IJMatrix        *ij_Ahat;

   HYPRE_Int             *split;
   hypre_BoxArrayArray ***convert_boxaa;
   hypre_BoxArrayArray   *pbnd_boxaa;
   hypre_BoxArray        *convert_boxa;
   hypre_BoxArray        *pbnd_boxa;
   hypre_BoxArray        *grid_boxes;
   hypre_Box             *box;
   hypre_Box             *grow_box;
   hypre_Box             *grid_box;
   hypre_Box             *ghost_box;
   hypre_Box             *convert_box;

   hypre_Index            ustride;
   hypre_Index            loop_size;
   hypre_IndexRef         start;
   hypre_IndexRef         ilower, iupper;

   HYPRE_Int              nrows;
   HYPRE_Int             *row_sizes;
   HYPRE_Complex         *values;

   HYPRE_Int              entry, part, var, nvars;
   HYPRE_Int              nnzs;
   HYPRE_Int              sizes[4];
   HYPRE_Int              nvalues, i, j, m, mi;
   HYPRE_Int              num_boxes;
   HYPRE_Int             *num_ghost;
   HYPRE_Int              nSentries;

   HYPRE_ANNOTATE_FUNC_BEGIN;

   /* Get row and column ranges */
   HYPRE_IJMatrixGetLocalRange(ij_A, &sizes[0], &sizes[1], &sizes[2], &sizes[3]);
   nrows = sizes[1] - sizes[0] + 1;

   /* Find boxes to be converted */
   convert_box   = hypre_BoxCreate(ndim);
   grow_box      = hypre_BoxCreate(ndim);
   ghost_box     = hypre_BoxCreate(ndim);
   convert_boxaa = hypre_TAlloc(hypre_BoxArrayArray **, nparts);
   for (part = 0; part < nparts; part++)
   {
      pgrid = hypre_SStructGridPGrid(grid, part);
      nvars = hypre_SStructPGridNVars(pgrid);

      convert_boxaa[part] = hypre_TAlloc(hypre_BoxArrayArray *, nvars);
      for (var = 0; var < nvars; var++)
      {
         sgrid = hypre_SStructPGridSGrid(pgrid, var);
         grid_boxes = hypre_StructGridBoxes(sgrid);
         num_boxes  = hypre_StructGridNumBoxes(sgrid);
         pbnd_boxaa = hypre_SStructPGridPBndBoxArrayArray(pgrid, var);

         convert_boxaa[part][var] = hypre_BoxArrayArrayCreate(num_boxes, ndim);
         hypre_ForBoxArrayI(i, pbnd_boxaa)
         {
            convert_boxa = hypre_BoxArrayArrayBoxArray(convert_boxaa[part][var], i);
            pbnd_boxa = hypre_BoxArrayArrayBoxArray(pbnd_boxaa, i);
            grid_box  = hypre_BoxArrayBox(grid_boxes, i);
            hypre_ForBoxI(j, pbnd_boxa)
            {
               box = hypre_BoxArrayBox(pbnd_boxa, j);
               hypre_CopyBox(box, grow_box);
               hypre_BoxGrowByValue(grow_box, 1);
               hypre_IntersectBoxes(grow_box, grid_box, convert_box);

               hypre_AppendBox(convert_box, convert_boxa);
            }

            /* Eliminate duplicated entries */
            hypre_UnionBoxes(convert_boxa);
         }
      }
   }
   hypre_BoxDestroy(grow_box);
   hypre_BoxDestroy(convert_box);

   /* Set row sizes */
   nvalues = 0; m = 0;
   hypre_SetIndex(ustride, 1);
   row_sizes = hypre_CTAlloc(HYPRE_Int, nrows);
   for (part = 0; part < nparts; part++)
   {
      pA    = hypre_SStructMatrixPMatrix(A, part);
      pgrid = hypre_SStructGridPGrid(grid, part);
      nvars = hypre_SStructPMatrixNVars(pA);

      for (var = 0; var < nvars; var++)
      {
         sgrid   = hypre_SStructPGridSGrid(pgrid, var);
         split   = hypre_SStructMatrixSplit(A, part, var);
         stencil = hypre_SStructPMatrixStencil(pA, var);
         grid_boxes = hypre_StructGridBoxes(sgrid);
         num_ghost  = hypre_StructGridNumGhost(sgrid);

         nnzs = 0;
         for (entry = 0; entry < hypre_SStructStencilSize(stencil); entry++)
         {
            if (split[entry] > -1)
            {
               nnzs++;
            }
         }

         hypre_ForBoxArrayI(i, convert_boxaa[part][var])
         {
            convert_boxa = hypre_BoxArrayArrayBoxArray(convert_boxaa[part][var], i);
            grid_box = hypre_BoxArrayBox(grid_boxes, i);
            hypre_CopyBox(grid_box, ghost_box);
            hypre_BoxGrowByArray(ghost_box, num_ghost);

            hypre_ForBoxI(j, convert_boxa)
            {
               convert_box = hypre_BoxArrayBox(convert_boxa, j);

               start = hypre_BoxIMin(convert_box);
               hypre_BoxGetSize(convert_box, loop_size);

               hypre_BoxLoop1Begin(ndim, loop_size, ghost_box, start, ustride, mi);
#ifdef HYPRE_USING_OPENMP
#pragma omp parallel for private(HYPRE_BOX_PRIVATE,mi) HYPRE_SMP_SCHEDULE
#endif
               hypre_BoxLoop1For(mi)
               {
                  row_sizes[m + mi] = nnzs;
               }
               hypre_BoxLoop1End(mi);

               nvalues += nnzs*hypre_BoxVolume(convert_box);
            } /* Loop over convert_boxa */

            m += hypre_BoxVolume(ghost_box);
         } /* Loop over convert_boxaa */
      } /* Loop over vars */
   } /* Loop over parts */
   hypre_BoxDestroy(ghost_box);

   /* Create and initialize ij_Ahat */
   HYPRE_IJMatrixCreate(comm, sizes[0], sizes[1], sizes[2], sizes[3], &ij_Ahat);
   HYPRE_IJMatrixSetObjectType(ij_Ahat, HYPRE_PARCSR);
   HYPRE_IJMatrixSetRowSizes(ij_Ahat, (const HYPRE_Int *) row_sizes);
   HYPRE_IJMatrixInitialize(ij_Ahat);

   /* Free/Allocate memory */
   hypre_TFree(row_sizes);
   values = hypre_CTAlloc(HYPRE_Complex, nvalues);

   /* Set entries of ij_Ahat */
   for (part = 0; part < nparts; part++)
   {
      pA    = hypre_SStructMatrixPMatrix(A, part);
      pgrid = hypre_SStructGridPGrid(grid, part);
      nvars = hypre_SStructPMatrixNVars(pA);

      for (var = 0; var < nvars; var++)
      {
         split   = hypre_SStructMatrixSplit(A, part, var);
         stencil = hypre_SStructPMatrixStencil(pA, var);

         nSentries = 0;
         for (entry = 0; entry < hypre_SStructStencilSize(stencil); entry++)
         {
            if (split[entry] > -1)
            {
               Sentries[nSentries] = split[entry];
               nSentries++;
            }
         }

         hypre_ForBoxArrayI(i, convert_boxaa[part][var])
         {
            convert_boxa = hypre_BoxArrayArrayBoxArray(convert_boxaa[part][var], i);
            hypre_ForBoxI(j, convert_boxa)
            {
               convert_box = hypre_BoxArrayBox(convert_boxa, j);
               ilower = hypre_BoxIMin(convert_box);
               iupper = hypre_BoxIMax(convert_box);

               /* GET values from this box */
               hypre_SStructPMatrixSetBoxValues(pA, ilower, iupper, var,
                                                nSentries, Sentries, values, -1);

               /* SET values to ij_Ahat */
               hypre_SStructUMatrixSetBoxValuesHelper(A, part, ilower, iupper,
                                                      var, nSentries, Sentries,
                                                      values, 0, ij_Ahat);
            } /* Loop over convert_boxa */
         } /* Loop over convert_boxaa */
      } /* Loop over vars */
   } /* Loop over parts */

   /* Assemble ij_A */
   HYPRE_IJMatrixAssemble(ij_Ahat);

   /* Free memory */
   hypre_TFree(values);

   /* Set pointer to ij_Ahat */
   *ij_Ahat_ptr = ij_Ahat;

   HYPRE_ANNOTATE_FUNC_END;

   return hypre_error_flag;
}