/*
 * File:          Hypre_StructSMG_IOR.c
 * Symbol:        Hypre.StructSMG-v0.1.6
 * Symbol Type:   class
 * Babel Version: 0.8.0
 * SIDL Created:  20030121 14:39:22 PST
 * Generated:     20030121 14:39:23 PST
 * Description:   Intermediate Object Representation for Hypre.StructSMG
 * 
 * WARNING: Automatically generated; changes will be lost
 * 
 * babel-version = 0.8.0
 * source-line   = 456
 * source-url    = file:/home/painter/linear_solvers/babel/Interfaces.idl
 */

#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "Hypre_StructSMG_IOR.h"
#ifndef included_SIDL_BaseClass_Impl_h
#include "SIDL_BaseClass_Impl.h"
#endif
#ifndef included_SIDL_BaseClass_h
#include "SIDL_BaseClass.h"
#endif
#ifndef included_SIDL_ClassInfo_h
#include "SIDL_ClassInfo.h"
#endif
#ifndef included_SIDL_ClassInfoI_h
#include "SIDL_ClassInfoI.h"
#endif

#ifndef NULL
#define NULL 0
#endif

/*
 * Static variables to hold version of IOR
 */

static const int32_t s_IOR_MAJOR_VERSION = 0;
static const int32_t s_IOR_MINOR_VERSION = 8;
/*
 * Static variable to hold shared ClassInfo interface.
 */

static SIDL_ClassInfo s_classInfo = NULL;
static int s_classInfo_init = 1;

/*
 * Static variables for managing EPV initialization.
 */

static int s_method_initialized = 0;
static int s_remote_initialized = 0;

static struct Hypre_StructSMG__epv s_new__hypre_structsmg;
static struct Hypre_StructSMG__epv s_rem__hypre_structsmg;

static struct Hypre_Operator__epv s_new__hypre_operator;
static struct Hypre_Operator__epv s_rem__hypre_operator;

static struct Hypre_Solver__epv s_new__hypre_solver;
static struct Hypre_Solver__epv s_rem__hypre_solver;

static struct SIDL_BaseClass__epv  s_new__sidl_baseclass;
static struct SIDL_BaseClass__epv* s_old__sidl_baseclass;
static struct SIDL_BaseClass__epv  s_rem__sidl_baseclass;

static struct SIDL_BaseInterface__epv  s_new__sidl_baseinterface;
static struct SIDL_BaseInterface__epv* s_old__sidl_baseinterface;
static struct SIDL_BaseInterface__epv  s_rem__sidl_baseinterface;

/*
 * Declare EPV routines defined in the skeleton file.
 */

extern void Hypre_StructSMG__set_epv(
  struct Hypre_StructSMG__epv* epv);

/*
 * CAST: dynamic type casting support.
 */

static void* ior_Hypre_StructSMG__cast(
  struct Hypre_StructSMG__object* self,
  const char* name)
{
  void* cast = NULL;

  struct Hypre_StructSMG__object* s0 = self;
  struct SIDL_BaseClass__object*  s1 = &s0->d_sidl_baseclass;

  if (!strcmp(name, "Hypre.StructSMG")) {
    cast = (void*) s0;
  } else if (!strcmp(name, "Hypre.Operator")) {
    cast = (void*) &s0->d_hypre_operator;
  } else if (!strcmp(name, "Hypre.Solver")) {
    cast = (void*) &s0->d_hypre_solver;
  } else if (!strcmp(name, "SIDL.BaseClass")) {
    cast = (void*) s1;
  } else if (!strcmp(name, "SIDL.BaseInterface")) {
    cast = (void*) &s1->d_sidl_baseinterface;
  }

  return cast;
}

/*
 * DELETE: call destructor and free object memory.
 */

static void ior_Hypre_StructSMG__delete(
  struct Hypre_StructSMG__object* self)
{
  Hypre_StructSMG__fini(self);
  memset((void*)self, 0, sizeof(struct Hypre_StructSMG__object));
  free((void*) self);
}

/*
 * EPV: create method entry point vector (EPV) structure.
 */

static void Hypre_StructSMG__init_epv(
  struct Hypre_StructSMG__object* self)
{
  struct Hypre_StructSMG__object* s0 = self;
  struct SIDL_BaseClass__object*  s1 = &s0->d_sidl_baseclass;

  struct Hypre_StructSMG__epv*    epv = &s_new__hypre_structsmg;
  struct Hypre_Operator__epv*     e0  = &s_new__hypre_operator;
  struct Hypre_Solver__epv*       e1  = &s_new__hypre_solver;
  struct SIDL_BaseClass__epv*     e2  = &s_new__sidl_baseclass;
  struct SIDL_BaseInterface__epv* e3  = &s_new__sidl_baseinterface;

  s_old__sidl_baseinterface = s1->d_sidl_baseinterface.d_epv;
  s_old__sidl_baseclass     = s1->d_epv;

  epv->f__cast                   = ior_Hypre_StructSMG__cast;
  epv->f__delete                 = ior_Hypre_StructSMG__delete;
  epv->f__ctor                   = NULL;
  epv->f__dtor                   = NULL;
  epv->f_addRef                  = (void (*)(struct Hypre_StructSMG__object*)) 
    s1->d_epv->f_addRef;
  epv->f_deleteRef               = (void (*)(struct Hypre_StructSMG__object*)) 
    s1->d_epv->f_deleteRef;
  epv->f_isSame                  = (SIDL_bool (*)(struct 
    Hypre_StructSMG__object*,
    struct SIDL_BaseInterface__object*)) s1->d_epv->f_isSame;
  epv->f_queryInt                = (struct SIDL_BaseInterface__object* 
    (*)(struct Hypre_StructSMG__object*,const char*)) s1->d_epv->f_queryInt;
  epv->f_isType                  = (SIDL_bool (*)(struct 
    Hypre_StructSMG__object*,const char*)) s1->d_epv->f_isType;
  epv->f_getClassInfo            = (struct SIDL_ClassInfo__object* (*)(struct 
    Hypre_StructSMG__object*)) s1->d_epv->f_getClassInfo;
  epv->f_SetCommunicator         = NULL;
  epv->f_GetDoubleValue          = NULL;
  epv->f_GetIntValue             = NULL;
  epv->f_SetDoubleParameter      = NULL;
  epv->f_SetIntParameter         = NULL;
  epv->f_SetStringParameter      = NULL;
  epv->f_SetIntArrayParameter    = NULL;
  epv->f_SetDoubleArrayParameter = NULL;
  epv->f_Setup                   = NULL;
  epv->f_Apply                   = NULL;
  epv->f_SetOperator             = NULL;
  epv->f_GetResidual             = NULL;
  epv->f_SetLogging              = NULL;
  epv->f_SetPrintLevel           = NULL;

  Hypre_StructSMG__set_epv(epv);

  e0->f__cast                   = (void* (*)(void*,const char*)) epv->f__cast;
  e0->f__delete                 = (void (*)(void*)) epv->f__delete;
  e0->f_addRef                  = (void (*)(void*)) epv->f_addRef;
  e0->f_deleteRef               = (void (*)(void*)) epv->f_deleteRef;
  e0->f_isSame                  = (SIDL_bool (*)(void*,
    struct SIDL_BaseInterface__object*)) epv->f_isSame;
  e0->f_queryInt                = (struct SIDL_BaseInterface__object* (*)(void*,
    const char*)) epv->f_queryInt;
  e0->f_isType                  = (SIDL_bool (*)(void*,
    const char*)) epv->f_isType;
  e0->f_SetCommunicator         = (int32_t (*)(void*,
    void*)) epv->f_SetCommunicator;
  e0->f_GetDoubleValue          = (int32_t (*)(void*,const char*,
    double*)) epv->f_GetDoubleValue;
  e0->f_GetIntValue             = (int32_t (*)(void*,const char*,
    int32_t*)) epv->f_GetIntValue;
  e0->f_SetDoubleParameter      = (int32_t (*)(void*,const char*,
    double)) epv->f_SetDoubleParameter;
  e0->f_SetIntParameter         = (int32_t (*)(void*,const char*,
    int32_t)) epv->f_SetIntParameter;
  e0->f_SetStringParameter      = (int32_t (*)(void*,const char*,
    const char*)) epv->f_SetStringParameter;
  e0->f_SetIntArrayParameter    = (int32_t (*)(void*,const char*,
    struct SIDL_int__array*)) epv->f_SetIntArrayParameter;
  e0->f_SetDoubleArrayParameter = (int32_t (*)(void*,const char*,
    struct SIDL_double__array*)) epv->f_SetDoubleArrayParameter;
  e0->f_Setup                   = (int32_t (*)(void*,
    struct Hypre_Vector__object*,struct Hypre_Vector__object*)) epv->f_Setup;
  e0->f_Apply                   = (int32_t (*)(void*,
    struct Hypre_Vector__object*,struct Hypre_Vector__object**)) epv->f_Apply;

  e1->f__cast                   = (void* (*)(void*,const char*)) epv->f__cast;
  e1->f__delete                 = (void (*)(void*)) epv->f__delete;
  e1->f_addRef                  = (void (*)(void*)) epv->f_addRef;
  e1->f_deleteRef               = (void (*)(void*)) epv->f_deleteRef;
  e1->f_isSame                  = (SIDL_bool (*)(void*,
    struct SIDL_BaseInterface__object*)) epv->f_isSame;
  e1->f_queryInt                = (struct SIDL_BaseInterface__object* (*)(void*,
    const char*)) epv->f_queryInt;
  e1->f_isType                  = (SIDL_bool (*)(void*,
    const char*)) epv->f_isType;
  e1->f_SetCommunicator         = (int32_t (*)(void*,
    void*)) epv->f_SetCommunicator;
  e1->f_GetDoubleValue          = (int32_t (*)(void*,const char*,
    double*)) epv->f_GetDoubleValue;
  e1->f_GetIntValue             = (int32_t (*)(void*,const char*,
    int32_t*)) epv->f_GetIntValue;
  e1->f_SetDoubleParameter      = (int32_t (*)(void*,const char*,
    double)) epv->f_SetDoubleParameter;
  e1->f_SetIntParameter         = (int32_t (*)(void*,const char*,
    int32_t)) epv->f_SetIntParameter;
  e1->f_SetStringParameter      = (int32_t (*)(void*,const char*,
    const char*)) epv->f_SetStringParameter;
  e1->f_SetIntArrayParameter    = (int32_t (*)(void*,const char*,
    struct SIDL_int__array*)) epv->f_SetIntArrayParameter;
  e1->f_SetDoubleArrayParameter = (int32_t (*)(void*,const char*,
    struct SIDL_double__array*)) epv->f_SetDoubleArrayParameter;
  e1->f_Setup                   = (int32_t (*)(void*,
    struct Hypre_Vector__object*,struct Hypre_Vector__object*)) epv->f_Setup;
  e1->f_Apply                   = (int32_t (*)(void*,
    struct Hypre_Vector__object*,struct Hypre_Vector__object**)) epv->f_Apply;
  e1->f_SetOperator             = (int32_t (*)(void*,
    struct Hypre_Operator__object*)) epv->f_SetOperator;
  e1->f_GetResidual             = (int32_t (*)(void*,
    struct Hypre_Vector__object**)) epv->f_GetResidual;
  e1->f_SetLogging              = (int32_t (*)(void*,
    int32_t)) epv->f_SetLogging;
  e1->f_SetPrintLevel           = (int32_t (*)(void*,
    int32_t)) epv->f_SetPrintLevel;

  e2->f__cast        = (void* (*)(struct SIDL_BaseClass__object*,
    const char*)) epv->f__cast;
  e2->f__delete      = (void (*)(struct SIDL_BaseClass__object*)) 
    epv->f__delete;
  e2->f_addRef       = (void (*)(struct SIDL_BaseClass__object*)) epv->f_addRef;
  e2->f_deleteRef    = (void (*)(struct SIDL_BaseClass__object*)) 
    epv->f_deleteRef;
  e2->f_isSame       = (SIDL_bool (*)(struct SIDL_BaseClass__object*,
    struct SIDL_BaseInterface__object*)) epv->f_isSame;
  e2->f_queryInt     = (struct SIDL_BaseInterface__object* (*)(struct 
    SIDL_BaseClass__object*,const char*)) epv->f_queryInt;
  e2->f_isType       = (SIDL_bool (*)(struct SIDL_BaseClass__object*,
    const char*)) epv->f_isType;
  e2->f_getClassInfo = (struct SIDL_ClassInfo__object* (*)(struct 
    SIDL_BaseClass__object*)) epv->f_getClassInfo;

  e3->f__cast     = (void* (*)(void*,const char*)) epv->f__cast;
  e3->f__delete   = (void (*)(void*)) epv->f__delete;
  e3->f_addRef    = (void (*)(void*)) epv->f_addRef;
  e3->f_deleteRef = (void (*)(void*)) epv->f_deleteRef;
  e3->f_isSame    = (SIDL_bool (*)(void*,
    struct SIDL_BaseInterface__object*)) epv->f_isSame;
  e3->f_queryInt  = (struct SIDL_BaseInterface__object* (*)(void*,
    const char*)) epv->f_queryInt;
  e3->f_isType    = (SIDL_bool (*)(void*,const char*)) epv->f_isType;

  s_method_initialized = 1;
}

/*
 * initClassInfo: create a ClassInfo interface if necessary.
 */

static void
initClassInfo(SIDL_ClassInfo *info)
{
  if (s_classInfo_init) {
    SIDL_ClassInfoI impl;
    s_classInfo_init = 0;
    impl = SIDL_ClassInfoI__create();
    s_classInfo = SIDL_ClassInfo__cast(impl);
    if (impl) {
      SIDL_ClassInfoI_setName(impl, "Hypre.StructSMG");
      SIDL_ClassInfoI_setIORVersion(impl, s_IOR_MAJOR_VERSION,
        s_IOR_MINOR_VERSION);
    }
  }
  if (s_classInfo) {
    if (*info) {
      SIDL_ClassInfo_deleteRef(*info);
    }
    *info = s_classInfo;
    SIDL_ClassInfo_addRef(*info);
  }
}

/*
 * initMetadata: store IOR version & class in SIDL.BaseClass's data
 */

static void
initMetadata(struct Hypre_StructSMG__object* self)
{
  if (self) {
    struct SIDL_BaseClass__data *data = 
      SIDL_BaseClass__get_data(SIDL_BaseClass__cast(self));
    if (data) {
      data->d_IOR_major_version = s_IOR_MAJOR_VERSION;
      data->d_IOR_minor_version = s_IOR_MINOR_VERSION;
      initClassInfo(&(data->d_classinfo));
    }
  }
}

/*
 * NEW: allocate object and initialize it.
 */

struct Hypre_StructSMG__object*
Hypre_StructSMG__new(void)
{
  struct Hypre_StructSMG__object* self =
    (struct Hypre_StructSMG__object*) malloc(
      sizeof(struct Hypre_StructSMG__object));
  Hypre_StructSMG__init(self);
  initMetadata(self);
  return self;
}

/*
 * INIT: initialize a new instance of the class object.
 */

void Hypre_StructSMG__init(
  struct Hypre_StructSMG__object* self)
{
  struct Hypre_StructSMG__object* s0 = self;
  struct SIDL_BaseClass__object*  s1 = &s0->d_sidl_baseclass;

  SIDL_BaseClass__init(s1);

  if (!s_method_initialized) {
    Hypre_StructSMG__init_epv(s0);
  }

  s1->d_sidl_baseinterface.d_epv = &s_new__sidl_baseinterface;
  s1->d_epv                      = &s_new__sidl_baseclass;

  s0->d_hypre_operator.d_epv = &s_new__hypre_operator;
  s0->d_hypre_solver.d_epv   = &s_new__hypre_solver;
  s0->d_epv                  = &s_new__hypre_structsmg;

  s0->d_hypre_operator.d_object = self;

  s0->d_hypre_solver.d_object = self;

  s0->d_data = NULL;

  (*(self->d_epv->f__ctor))(self);
}

/*
 * FINI: deallocate a class instance (destructor).
 */

void Hypre_StructSMG__fini(
  struct Hypre_StructSMG__object* self)
{
  struct Hypre_StructSMG__object* s0 = self;
  struct SIDL_BaseClass__object*  s1 = &s0->d_sidl_baseclass;

  (*(s0->d_epv->f__dtor))(s0);

  s1->d_sidl_baseinterface.d_epv = s_old__sidl_baseinterface;
  s1->d_epv                      = s_old__sidl_baseclass;

  SIDL_BaseClass__fini(s1);
}

/*
 * VERSION: Return the version of the IOR used to generate this IOR.
 */

void
Hypre_StructSMG__IOR_version(int32_t *major, int32_t *minor)
{
  *major = s_IOR_MAJOR_VERSION;
  *minor = s_IOR_MINOR_VERSION;
}
static const struct Hypre_StructSMG__external
s_externalEntryPoints = {
  Hypre_StructSMG__new,
  Hypre_StructSMG__remote,
};

/*
 * This function returns a pointer to a static structure of
 * pointers to function entry points.  Its purpose is to provide
 * one-stop shopping for loading DLLs.
 * loading DLLs
 */

const struct Hypre_StructSMG__external*
Hypre_StructSMG__externals(void)
{
  return &s_externalEntryPoints;
}

/*
 * REMOTE CAST: dynamic type casting for remote objects.
 */

static void* remote_Hypre_StructSMG__cast(
  struct Hypre_StructSMG__object* self,
  const char* name)
{
  return NULL;
}

/*
 * REMOTE DELETE: call the remote destructor for the object.
 */

static void remote_Hypre_StructSMG__delete(
  struct Hypre_StructSMG__object* self)
{
  free((void*) self);
}

/*
 * REMOTE METHOD STUB:addRef
 */

static void
remote_Hypre_StructSMG_addRef(
  struct Hypre_StructSMG__object* self)
{
}

/*
 * REMOTE METHOD STUB:deleteRef
 */

static void
remote_Hypre_StructSMG_deleteRef(
  struct Hypre_StructSMG__object* self)
{
}

/*
 * REMOTE METHOD STUB:isSame
 */

static SIDL_bool
remote_Hypre_StructSMG_isSame(
  struct Hypre_StructSMG__object* self,
  struct SIDL_BaseInterface__object* iobj)
{
  return 0;
}

/*
 * REMOTE METHOD STUB:queryInt
 */

static struct SIDL_BaseInterface__object*
remote_Hypre_StructSMG_queryInt(
  struct Hypre_StructSMG__object* self,
  const char* name)
{
  return (struct SIDL_BaseInterface__object*) 0;
}

/*
 * REMOTE METHOD STUB:isType
 */

static SIDL_bool
remote_Hypre_StructSMG_isType(
  struct Hypre_StructSMG__object* self,
  const char* name)
{
  return 0;
}

/*
 * REMOTE METHOD STUB:getClassInfo
 */

static struct SIDL_ClassInfo__object*
remote_Hypre_StructSMG_getClassInfo(
  struct Hypre_StructSMG__object* self)
{
  return (struct SIDL_ClassInfo__object*) 0;
}

/*
 * REMOTE METHOD STUB:SetCommunicator
 */

static int32_t
remote_Hypre_StructSMG_SetCommunicator(
  struct Hypre_StructSMG__object* self,
  void* comm)
{
  return 0;
}

/*
 * REMOTE METHOD STUB:GetDoubleValue
 */

static int32_t
remote_Hypre_StructSMG_GetDoubleValue(
  struct Hypre_StructSMG__object* self,
  const char* name,
  double* value)
{
  return 0;
}

/*
 * REMOTE METHOD STUB:GetIntValue
 */

static int32_t
remote_Hypre_StructSMG_GetIntValue(
  struct Hypre_StructSMG__object* self,
  const char* name,
  int32_t* value)
{
  return 0;
}

/*
 * REMOTE METHOD STUB:SetDoubleParameter
 */

static int32_t
remote_Hypre_StructSMG_SetDoubleParameter(
  struct Hypre_StructSMG__object* self,
  const char* name,
  double value)
{
  return 0;
}

/*
 * REMOTE METHOD STUB:SetIntParameter
 */

static int32_t
remote_Hypre_StructSMG_SetIntParameter(
  struct Hypre_StructSMG__object* self,
  const char* name,
  int32_t value)
{
  return 0;
}

/*
 * REMOTE METHOD STUB:SetStringParameter
 */

static int32_t
remote_Hypre_StructSMG_SetStringParameter(
  struct Hypre_StructSMG__object* self,
  const char* name,
  const char* value)
{
  return 0;
}

/*
 * REMOTE METHOD STUB:SetIntArrayParameter
 */

static int32_t
remote_Hypre_StructSMG_SetIntArrayParameter(
  struct Hypre_StructSMG__object* self,
  const char* name,
  struct SIDL_int__array* value)
{
  return 0;
}

/*
 * REMOTE METHOD STUB:SetDoubleArrayParameter
 */

static int32_t
remote_Hypre_StructSMG_SetDoubleArrayParameter(
  struct Hypre_StructSMG__object* self,
  const char* name,
  struct SIDL_double__array* value)
{
  return 0;
}

/*
 * REMOTE METHOD STUB:Setup
 */

static int32_t
remote_Hypre_StructSMG_Setup(
  struct Hypre_StructSMG__object* self,
  struct Hypre_Vector__object* b,
  struct Hypre_Vector__object* x)
{
  return 0;
}

/*
 * REMOTE METHOD STUB:Apply
 */

static int32_t
remote_Hypre_StructSMG_Apply(
  struct Hypre_StructSMG__object* self,
  struct Hypre_Vector__object* b,
  struct Hypre_Vector__object** x)
{
  return 0;
}

/*
 * REMOTE METHOD STUB:SetOperator
 */

static int32_t
remote_Hypre_StructSMG_SetOperator(
  struct Hypre_StructSMG__object* self,
  struct Hypre_Operator__object* A)
{
  return 0;
}

/*
 * REMOTE METHOD STUB:GetResidual
 */

static int32_t
remote_Hypre_StructSMG_GetResidual(
  struct Hypre_StructSMG__object* self,
  struct Hypre_Vector__object** r)
{
  return 0;
}

/*
 * REMOTE METHOD STUB:SetLogging
 */

static int32_t
remote_Hypre_StructSMG_SetLogging(
  struct Hypre_StructSMG__object* self,
  int32_t level)
{
  return 0;
}

/*
 * REMOTE METHOD STUB:SetPrintLevel
 */

static int32_t
remote_Hypre_StructSMG_SetPrintLevel(
  struct Hypre_StructSMG__object* self,
  int32_t level)
{
  return 0;
}

/*
 * REMOTE EPV: create remote entry point vectors (EPVs).
 */

static void Hypre_StructSMG__init_remote_epv(void)
{
  struct Hypre_StructSMG__epv*    epv = &s_rem__hypre_structsmg;
  struct Hypre_Operator__epv*     e0  = &s_rem__hypre_operator;
  struct Hypre_Solver__epv*       e1  = &s_rem__hypre_solver;
  struct SIDL_BaseClass__epv*     e2  = &s_rem__sidl_baseclass;
  struct SIDL_BaseInterface__epv* e3  = &s_rem__sidl_baseinterface;

  epv->f__cast                   = remote_Hypre_StructSMG__cast;
  epv->f__delete                 = remote_Hypre_StructSMG__delete;
  epv->f__ctor                   = NULL;
  epv->f__dtor                   = NULL;
  epv->f_addRef                  = remote_Hypre_StructSMG_addRef;
  epv->f_deleteRef               = remote_Hypre_StructSMG_deleteRef;
  epv->f_isSame                  = remote_Hypre_StructSMG_isSame;
  epv->f_queryInt                = remote_Hypre_StructSMG_queryInt;
  epv->f_isType                  = remote_Hypre_StructSMG_isType;
  epv->f_getClassInfo            = remote_Hypre_StructSMG_getClassInfo;
  epv->f_SetCommunicator         = remote_Hypre_StructSMG_SetCommunicator;
  epv->f_GetDoubleValue          = remote_Hypre_StructSMG_GetDoubleValue;
  epv->f_GetIntValue             = remote_Hypre_StructSMG_GetIntValue;
  epv->f_SetDoubleParameter      = remote_Hypre_StructSMG_SetDoubleParameter;
  epv->f_SetIntParameter         = remote_Hypre_StructSMG_SetIntParameter;
  epv->f_SetStringParameter      = remote_Hypre_StructSMG_SetStringParameter;
  epv->f_SetIntArrayParameter    = remote_Hypre_StructSMG_SetIntArrayParameter;
  epv->f_SetDoubleArrayParameter = 
    remote_Hypre_StructSMG_SetDoubleArrayParameter;
  epv->f_Setup                   = remote_Hypre_StructSMG_Setup;
  epv->f_Apply                   = remote_Hypre_StructSMG_Apply;
  epv->f_SetOperator             = remote_Hypre_StructSMG_SetOperator;
  epv->f_GetResidual             = remote_Hypre_StructSMG_GetResidual;
  epv->f_SetLogging              = remote_Hypre_StructSMG_SetLogging;
  epv->f_SetPrintLevel           = remote_Hypre_StructSMG_SetPrintLevel;

  e0->f__cast                   = (void* (*)(void*,const char*)) epv->f__cast;
  e0->f__delete                 = (void (*)(void*)) epv->f__delete;
  e0->f_addRef                  = (void (*)(void*)) epv->f_addRef;
  e0->f_deleteRef               = (void (*)(void*)) epv->f_deleteRef;
  e0->f_isSame                  = (SIDL_bool (*)(void*,
    struct SIDL_BaseInterface__object*)) epv->f_isSame;
  e0->f_queryInt                = (struct SIDL_BaseInterface__object* (*)(void*,
    const char*)) epv->f_queryInt;
  e0->f_isType                  = (SIDL_bool (*)(void*,
    const char*)) epv->f_isType;
  e0->f_SetCommunicator         = (int32_t (*)(void*,
    void*)) epv->f_SetCommunicator;
  e0->f_GetDoubleValue          = (int32_t (*)(void*,const char*,
    double*)) epv->f_GetDoubleValue;
  e0->f_GetIntValue             = (int32_t (*)(void*,const char*,
    int32_t*)) epv->f_GetIntValue;
  e0->f_SetDoubleParameter      = (int32_t (*)(void*,const char*,
    double)) epv->f_SetDoubleParameter;
  e0->f_SetIntParameter         = (int32_t (*)(void*,const char*,
    int32_t)) epv->f_SetIntParameter;
  e0->f_SetStringParameter      = (int32_t (*)(void*,const char*,
    const char*)) epv->f_SetStringParameter;
  e0->f_SetIntArrayParameter    = (int32_t (*)(void*,const char*,
    struct SIDL_int__array*)) epv->f_SetIntArrayParameter;
  e0->f_SetDoubleArrayParameter = (int32_t (*)(void*,const char*,
    struct SIDL_double__array*)) epv->f_SetDoubleArrayParameter;
  e0->f_Setup                   = (int32_t (*)(void*,
    struct Hypre_Vector__object*,struct Hypre_Vector__object*)) epv->f_Setup;
  e0->f_Apply                   = (int32_t (*)(void*,
    struct Hypre_Vector__object*,struct Hypre_Vector__object**)) epv->f_Apply;

  e1->f__cast                   = (void* (*)(void*,const char*)) epv->f__cast;
  e1->f__delete                 = (void (*)(void*)) epv->f__delete;
  e1->f_addRef                  = (void (*)(void*)) epv->f_addRef;
  e1->f_deleteRef               = (void (*)(void*)) epv->f_deleteRef;
  e1->f_isSame                  = (SIDL_bool (*)(void*,
    struct SIDL_BaseInterface__object*)) epv->f_isSame;
  e1->f_queryInt                = (struct SIDL_BaseInterface__object* (*)(void*,
    const char*)) epv->f_queryInt;
  e1->f_isType                  = (SIDL_bool (*)(void*,
    const char*)) epv->f_isType;
  e1->f_SetCommunicator         = (int32_t (*)(void*,
    void*)) epv->f_SetCommunicator;
  e1->f_GetDoubleValue          = (int32_t (*)(void*,const char*,
    double*)) epv->f_GetDoubleValue;
  e1->f_GetIntValue             = (int32_t (*)(void*,const char*,
    int32_t*)) epv->f_GetIntValue;
  e1->f_SetDoubleParameter      = (int32_t (*)(void*,const char*,
    double)) epv->f_SetDoubleParameter;
  e1->f_SetIntParameter         = (int32_t (*)(void*,const char*,
    int32_t)) epv->f_SetIntParameter;
  e1->f_SetStringParameter      = (int32_t (*)(void*,const char*,
    const char*)) epv->f_SetStringParameter;
  e1->f_SetIntArrayParameter    = (int32_t (*)(void*,const char*,
    struct SIDL_int__array*)) epv->f_SetIntArrayParameter;
  e1->f_SetDoubleArrayParameter = (int32_t (*)(void*,const char*,
    struct SIDL_double__array*)) epv->f_SetDoubleArrayParameter;
  e1->f_Setup                   = (int32_t (*)(void*,
    struct Hypre_Vector__object*,struct Hypre_Vector__object*)) epv->f_Setup;
  e1->f_Apply                   = (int32_t (*)(void*,
    struct Hypre_Vector__object*,struct Hypre_Vector__object**)) epv->f_Apply;
  e1->f_SetOperator             = (int32_t (*)(void*,
    struct Hypre_Operator__object*)) epv->f_SetOperator;
  e1->f_GetResidual             = (int32_t (*)(void*,
    struct Hypre_Vector__object**)) epv->f_GetResidual;
  e1->f_SetLogging              = (int32_t (*)(void*,
    int32_t)) epv->f_SetLogging;
  e1->f_SetPrintLevel           = (int32_t (*)(void*,
    int32_t)) epv->f_SetPrintLevel;

  e2->f__cast        = (void* (*)(struct SIDL_BaseClass__object*,
    const char*)) epv->f__cast;
  e2->f__delete      = (void (*)(struct SIDL_BaseClass__object*)) 
    epv->f__delete;
  e2->f_addRef       = (void (*)(struct SIDL_BaseClass__object*)) epv->f_addRef;
  e2->f_deleteRef    = (void (*)(struct SIDL_BaseClass__object*)) 
    epv->f_deleteRef;
  e2->f_isSame       = (SIDL_bool (*)(struct SIDL_BaseClass__object*,
    struct SIDL_BaseInterface__object*)) epv->f_isSame;
  e2->f_queryInt     = (struct SIDL_BaseInterface__object* (*)(struct 
    SIDL_BaseClass__object*,const char*)) epv->f_queryInt;
  e2->f_isType       = (SIDL_bool (*)(struct SIDL_BaseClass__object*,
    const char*)) epv->f_isType;
  e2->f_getClassInfo = (struct SIDL_ClassInfo__object* (*)(struct 
    SIDL_BaseClass__object*)) epv->f_getClassInfo;

  e3->f__cast     = (void* (*)(void*,const char*)) epv->f__cast;
  e3->f__delete   = (void (*)(void*)) epv->f__delete;
  e3->f_addRef    = (void (*)(void*)) epv->f_addRef;
  e3->f_deleteRef = (void (*)(void*)) epv->f_deleteRef;
  e3->f_isSame    = (SIDL_bool (*)(void*,
    struct SIDL_BaseInterface__object*)) epv->f_isSame;
  e3->f_queryInt  = (struct SIDL_BaseInterface__object* (*)(void*,
    const char*)) epv->f_queryInt;
  e3->f_isType    = (SIDL_bool (*)(void*,const char*)) epv->f_isType;

  s_remote_initialized = 1;
}

/*
 * REMOTE: generate remote instance given URL string.
 */

struct Hypre_StructSMG__object*
Hypre_StructSMG__remote(const char *url)
{
  struct Hypre_StructSMG__object* self =
    (struct Hypre_StructSMG__object*) malloc(
      sizeof(struct Hypre_StructSMG__object));

  struct Hypre_StructSMG__object* s0 = self;
  struct SIDL_BaseClass__object*  s1 = &s0->d_sidl_baseclass;

  if (!s_remote_initialized) {
    Hypre_StructSMG__init_remote_epv();
  }

  s1->d_sidl_baseinterface.d_epv    = &s_rem__sidl_baseinterface;
  s1->d_sidl_baseinterface.d_object = NULL; /* FIXME */

  s1->d_data = NULL; /* FIXME */
  s1->d_epv  = &s_rem__sidl_baseclass;

  s0->d_hypre_operator.d_epv    = &s_rem__hypre_operator;
  s0->d_hypre_operator.d_object = NULL; /* FIXME */

  s0->d_hypre_solver.d_epv    = &s_rem__hypre_solver;
  s0->d_hypre_solver.d_object = NULL; /* FIXME */

  s0->d_data = NULL; /* FIXME */
  s0->d_epv  = &s_rem__hypre_structsmg;

  return self;
}
