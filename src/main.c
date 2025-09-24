/** A collection of unit tests for the DynA library. */
#include "dyna.h"

#include <stdio.h>

#ifdef NDEBUG
#undef NDEBUG // for assert.h below
#endif        /* NDEBUG */
#include <assert.h>

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
main (void)
{
  assert (!DynA_CanAllocateArrOfSize1 ());
  return 0;
}
