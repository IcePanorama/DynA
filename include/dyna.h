/** dyna.h - a type-agnostic dynamic array C library. */
#ifndef _DYNA_DYNAMIC_ARRAY_LIBRARY_H_
#define _DYNA_DYNAMIC_ARRAY_LIBRARY_H_

#include <stddef.h>

typedef struct _DynamicArr_s DynamicArr_t;

/**
 *  An `el_size` of 0 is treated as an unhandled exception when NDEBUG is
 *  undefined, else this returns NULL. May return NULL upon calloc failure.
 *  Param:  el_size  Size of a single element in bytes.
 */
DynamicArr_t *DynA_alloc (size_t el_size);

/**
 *  When NDEBUG is undefined, a NULL `a` is treated like an unhandled
 *  exception, otherwise this will behave well upon receiving such input.
 */
void DynA_free (DynamicArr_t *a);

/**
 *  Returns the physical size of `a` in bytes. Returns 0 upon NULL input when
 *  NDEBUG is defined, otherwise NULL input is treated as an unhandled
 *  exception.
 */
size_t DynA_get_capacity (DynamicArr_t *a);

#endif /* _DYNA_DYNAMIC_ARRAY_LIBRARY_H_ */
