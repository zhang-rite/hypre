/*BHEADER**********************************************************************
 * (c) 1999   The Regents of the University of California
 *
 * See the file COPYRIGHT_and_DISCLAIMER for a complete copyright
 * notice, contact person, and disclaimer.
 *
 * $Revision$
 *********************************************************************EHEADER*/
/******************************************************************************
 *
 * HYPRE_DDILUT interface
 *
 *****************************************************************************/

#ifndef __HYPRE_DDILUT__
#define __HYPRE_DDILUT__

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <math.h>

#include "utilities/utilities.h"
#include "parcsr_linear_solvers/HYPRE_parcsr_ls.h"
#include "parcsr_matrix_vector/parcsr_matrix_vector.h"

#ifdef __cplusplus
extern "C"
{
#endif

extern int HYPRE_LSI_DDIlutCreate( MPI_Comm comm, HYPRE_Solver *solver );
extern int HYPRE_LSI_DDIlutDestroy( HYPRE_Solver solver );
extern int HYPRE_LSI_DDIlutSetFillin( HYPRE_Solver solver, double fillin);
extern int HYPRE_LSI_DDIlutSetOutputLevel( HYPRE_Solver solver, int level);
extern int HYPRE_LSI_DDIlutSetDropTolerance( HYPRE_Solver solver, double thresh);
extern int HYPRE_LSI_DDIlutSolve( HYPRE_Solver solver, HYPRE_ParCSRMatrix A,
                                  HYPRE_ParVector b,   HYPRE_ParVector x );
extern int HYPRE_LSI_DDIlutSetup( HYPRE_Solver solver, HYPRE_ParCSRMatrix A,
                                  HYPRE_ParVector b,   HYPRE_ParVector x );

#ifdef __cplusplus
}
#endif

#endif

