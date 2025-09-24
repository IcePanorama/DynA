#include "dyna.h"

#include <assert.h>
#include <stdlib.h>

struct _DynamicArr_s
{
  size_t size;     // logical size of `data`
  size_t capacity; // physical size of `data`
  size_t el_size;  // size in bytes of one element of `data`
  void *data;
};

DynamicArr_t *
DynA_alloc (size_t el_size)
{
  DynamicArr_t *a = calloc (1, sizeof (DynamicArr_t));
  assert (a);
  if (!a)
    return NULL;

  a->size = 0;
  a->capacity = 1;
  a->el_size = el_size;
  a->data = calloc (a->capacity, a->el_size);
  assert (a->data);
  if (!a->data)
    {
      DynA_free (a);
      return NULL;
    }

  return a;
}

void
DynA_free (DynamicArr_t *a)
{
  assert (a);
  if (!a)
    return;

  if (a->data)
    free (a->data);
  free (a);
  a = NULL;
}
