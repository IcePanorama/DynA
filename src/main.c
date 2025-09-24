/** A collection of unit tests for the DynA library. */
#include "dyna.h"

#ifdef NDEBUG
// we still want our local asserts to work when testing NDEBUG builds
#undef NDEBUG
#include <assert.h>
#define NDEBUG
#else /* not NDEBUG */
#include <assert.h>
#endif /* not NDEBUG */

#include <stdio.h>

#define TEST_START() (printf ("Running test: %s\n", __func__))
#define FAIL_PRINT(msg) (fprintf (stderr, "%s: " msg "\n", __func__))

static int
DynA_CanAllocateArrOfSize1 (void)
{
  TEST_START ();
  DynamicArr_t *a = DynA_alloc (1);
  if (!a)
    {
      FAIL_PRINT ("Failed to alloc array w/ el size of 1.");
      return 0;
    }

  DynA_free (a);
  return 1;
}

static int
DynA_DefaultCapacityIs1 (void)
{
  TEST_START ();
  DynamicArr_t *a = DynA_alloc (1);
  if (!a)
    {
      FAIL_PRINT ("Out of memory error.");
      return 0;
    }

  const size_t cap = DynA_get_capacity (a);
  DynA_free (a);

  return cap == 1;
}

static int
DynA_DefaultSizeIs0 (void)
{
  TEST_START ();
  DynamicArr_t *a = DynA_alloc (1);
  if (!a)
    {
      FAIL_PRINT ("Out of memory error.");
      return 0;
    }

  const size_t size = DynA_get_size (a);
  DynA_free (a);

  return size == 0;
}

static int
DynA_ResizeCanDoubleOriginalSize (void)
{
  TEST_START ();
  DynamicArr_t *a = DynA_alloc (1);
  if (!a)
    {
      FAIL_PRINT ("Out of memory error.");
      return 0;
    }

  const size_t old = DynA_get_capacity (a);
  const size_t target = old * 2;
  DynA_resize (a, target);
  const size_t new = DynA_get_capacity (a);
  DynA_free (a);

  return new == target;
}

static int
DynA_ResizeCanReduceSizeOfArray (void)
{
  TEST_START ();
  DynamicArr_t *a = DynA_alloc (1);
  if (!a)
    {
      FAIL_PRINT ("Out of memory error.");
      return 0;
    }

  DynA_resize (a, 2);
  DynA_resize (a, 1);
  const size_t new = DynA_get_capacity (a);
  DynA_free (a);

  return new == 1;
}

static int
DynA_AppendingSingleElementWorksAsExpected (void)
{
  TEST_START ();
  DynamicArr_t *a = DynA_alloc (1);
  if (!a)
    {
      FAIL_PRINT ("Out of memory error.");
      return 0;
    }

  char exp = 'a';
  DynA_append (a, (void *)&exp);
  char act = *((char *)DynA_at (a, 0));
  DynA_free (a);

  return exp == act;
}

#ifdef NDEBUG
static int
DynA_ReturnsNULLWhenElSizeIsZero (void)
{
  TEST_START ();
  DynamicArr_t *a = DynA_alloc (0);
  return a == NULL;
}

static void
DynA_FreeBehavesWellOnNULLInput (void)
{
  TEST_START ();
  DynA_free (NULL);
}

static int
DynA_GetCapReturnsZeroOnNULLInput (void)
{
  TEST_START ();
  return DynA_get_capacity (NULL) == 0;
}

static int
DynA_GetSizeReturnsZeroOnNULLInput (void)
{
  TEST_START ();
  return DynA_get_size (NULL) == 0;
}

static int
DynA_ResizeReturnsNonZeroOnNULLInput (void)
{
  TEST_START ();
  return DynA_resize (NULL, 2);
}

static int
DynA_ResizeReturnsNonZeroOnZeroNewCap (void)
{
  TEST_START ();
  DynamicArr_t *a = DynA_alloc (1);
  if (!a)
    {
      FAIL_PRINT ("Out of memory error.");
      return 0;
    }

  int ret = DynA_resize (a, 0);
  DynA_free (a);

  return ret;
}

static int
DynA_AtBehavesWellOnNULLInput (void)
{
  TEST_START ();
  return DynA_at (NULL, 0) == NULL;
}

static int
DynA_AtReturnsNullOnInvalidIdx (void)
{
  TEST_START ();
  DynamicArr_t *a = DynA_alloc (1);
  if (!a)
    {
      FAIL_PRINT ("Out of memory error.");
      return 0;
    }

  void *ret = DynA_at (a, 0);
  DynA_free (a);
  return ret == NULL;
}
#endif /* NDEBUG */

int
main (void)
{
  assert (DynA_CanAllocateArrOfSize1 ());
  assert (DynA_DefaultCapacityIs1 ());
  assert (DynA_DefaultSizeIs0 ());
  assert (DynA_ResizeCanDoubleOriginalSize ());
  assert (DynA_ResizeCanReduceSizeOfArray ());
  assert (DynA_AppendingSingleElementWorksAsExpected ());

#ifdef NDEBUG
  assert (DynA_ReturnsNULLWhenElSizeIsZero ());
  DynA_FreeBehavesWellOnNULLInput ();
  assert (DynA_GetCapReturnsZeroOnNULLInput ());
  assert (DynA_GetSizeReturnsZeroOnNULLInput ());
  assert (DynA_ResizeReturnsNonZeroOnNULLInput ());
  assert (DynA_ResizeReturnsNonZeroOnZeroNewCap ());
  assert (DynA_AtBehavesWellOnNULLInput ());
  assert (DynA_AtReturnsNullOnInvalidIdx ());
#endif /* NDEBUG */

  return 0;
}
