#include "dyna.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

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
  assert (el_size);
  if (!el_size)
    return NULL;

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

size_t
DynA_get_capacity (DynamicArr_t *a)
{
  assert (a);
  if (!a)
    return 0;

  return a->capacity;
}

size_t
DynA_get_size (DynamicArr_t *a)
{
  assert (a);
  if (!a)
    return 0;

  return a->size;
}

int
DynA_resize (DynamicArr_t *a, size_t new_cap)
{
  assert (a);
  assert (new_cap > 0);
  if ((!a) || (new_cap <= 0))
    return -1;

  void *tmp = realloc (a->data, new_cap * a->el_size);
  assert (tmp);
  if (tmp == NULL)
    return -1;

  if (new_cap > a->capacity)
    {
      // Zero out new elements
      memset ((char *)tmp + (a->el_size * a->capacity), 0,
              (new_cap - a->capacity) * a->el_size);
    }

  a->capacity = new_cap;
  a->data = tmp;
  return 0;
}

void *
DynA_at (DynamicArr_t *a, size_t i)
{
  assert (a);
  if (!a)
    return NULL;

  size_t size = DynA_get_size (a);
  assert (i < size);
  if (i >= size)
    return NULL;

  return (void *)((char *)(a->data) + (a->el_size * i));
}

static int
double_size (DynamicArr_t a[static 1])
{
  return DynA_resize (a, a->capacity * 2);
}

int
DynA_append (DynamicArr_t *a, void *el)
{
  assert (a);
  assert (el);
  if (!a || !el)
    return -1;

  if ((a->size == a->capacity) && (double_size (a) != 0))
    return -1;

  void *ptr = (void *)((char *)(a->data) + (a->el_size * a->size));
  memcpy (ptr, el, a->el_size);
  a->size++;
  return 0;
}
