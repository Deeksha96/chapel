#ifndef _chpl_mem_H_
#define _chpl_mem_H_

#ifndef LAUNCHER

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include "arg.h"
#include "chpl-mem-hook.h"
#include "chpltypes.h"
#include "chpl-tasks.h"
#include "error.h"

// runtime/include/mem/*/chpl-mem-impl.h defines
// chpl_calloc, chpl_malloc, chpl_realloc, chpl_free
// with the same signatures as the standard functions
// and no additional error checking.
#include "chpl-mem-impl.h"


void chpl_mem_init(void);
void chpl_mem_exit(void);

int chpl_mem_inited(void);


//
// Inform callers as to the memory layer's actual starting address
// and length for the shared heap, if that is known.  The *start_p
// value will be set to NULL if the memory layer does not know this
// information.
//
void chpl_mem_actualSharedHeap(void** start_p, size_t* size_p);


static ___always_inline
void* chpl_mem_allocMany(size_t number, size_t size,
                         chpl_mem_descInt_t description,
                         int32_t lineno, chpl_string filename) {
  void* memAlloc;
  chpl_memhook_malloc_pre(number, size, description, lineno, filename);
  memAlloc = chpl_malloc(number*size);
  chpl_memhook_malloc_post(memAlloc, number, size, description,
                           lineno, filename);
  return memAlloc;
}

static ___always_inline
void* chpl_mem_alloc(size_t size, chpl_mem_descInt_t description, int32_t lineno, chpl_string filename) {
  return chpl_mem_allocMany(1, size, description, lineno, filename);
}

static ___always_inline
void* chpl_mem_allocManyZero(size_t number, size_t size,
                             chpl_mem_descInt_t description,
                             int32_t lineno, chpl_string filename) {
  void* memAlloc;
  chpl_memhook_malloc_pre(number, size, description, lineno, filename);
  memAlloc = chpl_calloc(number, size);
  chpl_memhook_malloc_post(memAlloc, number, size, description,
                           lineno, filename);
  return memAlloc;
}

static ___always_inline
void chpl_mem_free(void* memAlloc, int32_t lineno, chpl_string filename) {
  chpl_memhook_free_pre(memAlloc, lineno, filename);
  chpl_free(memAlloc);
}

static ___always_inline
void* chpl_mem_realloc(void* memAlloc, size_t number, size_t size, 
                       chpl_mem_descInt_t description,
                       int32_t lineno, chpl_string filename) {
  void* moreMemAlloc;

  chpl_memhook_realloc_pre(memAlloc, number, size, description,
                           lineno, filename);
  if( number == 0 || size == 0 ) {
    chpl_mem_free(memAlloc, lineno, filename);
    return NULL;
  }
  moreMemAlloc = chpl_realloc(memAlloc, number*size);
  chpl_memhook_realloc_post(moreMemAlloc, memAlloc, number, size, description,
                            lineno, filename);
  return moreMemAlloc;
}


void chpl_mem_layerInit(void);
void chpl_mem_layerExit(void);
void chpl_mem_layerActualSharedHeap(void**, size_t*);
void* chpl_mem_layerAlloc(size_t, int32_t, chpl_string);
void* chpl_mem_layerRealloc(void*, size_t, int32_t, chpl_string);
void chpl_mem_layerFree(void*, int32_t, chpl_string);

#else // LAUNCHER

#include <stdlib.h>
#include "arg.h"

#define chpl_mem_allocMany(number, size, description, lineno, filename)        \
  malloc((number)*(size))

#define chpl_mem_free(ptr, lineno, filename)        \
  free(ptr)

#endif // LAUNCHER

#endif
