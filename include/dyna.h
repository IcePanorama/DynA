/** dyna.h - a type-agnostic dynamic array C library. */
#ifndef _DYNA_DYNAMIC_ARRAY_LIBRARY_H_
#define _DYNA_DYNAMIC_ARRAY_LIBRARY_H_

#include <stddef.h>

typedef struct _DynamicArr_s DynamicArr_t;

/** Param:  el_size  Size of a single element in bytes. */
DynamicArr_t *DynA_alloc (size_t el_size);

void DynA_free (DynamicArr_t *arr);

#endif /* _DYNA_DYNAMIC_ARRAY_LIBRARY_H_ */
