#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define VERIFY  0   // check that handmade code does "miss" and "hit"

struct cacheentry
{
   uintptr_t   uniqueid;
   void        *(*functionpointer)( void *, uintptr_t, void *);
};


#define S_CACHE_ENTRIES 8

struct cache
{
   uintptr_t           mask;
   struct cacheentry   entries[ S_CACHE_ENTRIES];
};


struct xclass
{
   struct cacheentry   *entries;
   void                *(*functionpointer)( void *, uintptr_t, void *);
};


struct runtime
{
   char            *name;
   struct xclass   *ctab[ 8];
};

static void  *imp( void *self, uintptr_t _cmd, void *_param)
{
#if VERIFY
   printf( "hit\n");
#endif
   return( self);
}


static void  *continue_call( void *self, uintptr_t _cmd, void *_param)
{
#if VERIFY
   printf( "miss\n");
#endif
   return( self);
}


struct cache    class0cache =
{
   (S_CACHE_ENTRIES - 1) * sizeof( struct cacheentry),
   {
      { 0, 0 }
   }
};


static struct xclass   class0 =
{
   class0cache.entries,
   continue_call
};


static struct runtime   runtime =
{
   "runtime",
   {
      0,
      &class0
   }
};


struct obj_with_header
{
   struct xclass   *isa;
};


int   main( int argc, char *argv[])
{
   unsigned int             i, j, n;
   void                     *obj;
   extern void              *call( void *obj,uintptr_t uniqueid, void *parameter);
   struct obj_with_header   space;
   struct cacheentry        *entry;

   // create an object with isa pointer
   space.isa = &class0;
   obj       = &space + 1;

   assert( sizeof( uintptr_t) == sizeof( uint64_t));
   assert( sizeof( struct cacheentry) == 2 * sizeof( uint64_t));

   entry = &class0cache.entries[ (0x18481848 & class0cache.mask) / sizeof( *entry)];
#if VERIFY
   call( obj, 0x18481848, (void *) 0x1848);
   entry->uniqueid        = 0x18481848;
   entry->functionpointer = imp;
   call( obj, 0x18481848, (void *) 0x1848);
   return( 0);
#endif

   if( argc >= 2)
      if( argv[ 1][ 0] == 'm')
         entry = NULL;

   if( entry)
   {
      entry->uniqueid        = 0x18481848;
      entry->functionpointer = imp;
   }

   n = 1000;
   if( argc >= 3)
      n = atoi( argv[ 2]);

   for( i = 0; i < n; i++)
      for( j = 0; j < 1000000; j++)
         call( obj, 0x18481848, (void *) 0x1848);
   return( 0);
}

