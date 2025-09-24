/** A collection of unit tests for the DynA library. */
#include "dyna.h"

#ifdef NDEBUG
#undef NDEBUG
#include <assert.h>
#define NDEBUG
#else /* not NDEBUG */
#include <assert.h>
#endif /* not NDEBUG */

#include <stdio.h>

#define TEST_START() (printf ("Running test: %s\n", __func__))
#define FAIL_PRINT(msg) (fprintf (stderr, "%s: " msg "\n", __func__))

int
DynA_CanAllocateArrOfSize1 (void)
{
  TEST_START ();
  DynamicArr_t *a = DynA_alloc (1);
  if (!a)
    {
      FAIL_PRINT ("Failed to alloc array w/ el size of 1.");
      return -1;
    }

  DynA_free (a);
  return 0;
}

int
DynA_ReturnsNULLWhenElSizeIsZero (void)
{
  TEST_START ();
  DynamicArr_t *a = DynA_alloc (0);
  return a == NULL;
}

void
DynA_FreeBehavesWellOnNULLInput (void)
{
  TEST_START ();
  DynA_free (NULL);
}

int
main (void)
{
  assert (DynA_CanAllocateArrOfSize1 () == 0);

#ifdef NDEBUG
  assert (DynA_ReturnsNULLWhenElSizeIsZero ());
  DynA_FreeBehavesWellOnNULLInput ();
#endif /* NDEBUG */
  return 0;
}
