#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>


struct cacheentry
{
   uintptr_t   uniqueid;
   void        *(*functionpointer)( void *, uintptr_t, void *);
};


struct cache
{
   uintptr_t           mask;
   struct cacheentry   entries[ 8];
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


static void  *messenger( void *self, uintptr_t _cmd, void *_param)
{
   return( self);
}


struct cache    class0cache =
{
   sizeof( struct cacheentry) * 8 - 1,
   {
      { 0x18480000, messenger }  // abuse messenger again
   }
};


static struct xclass   class0 =
{
   class0cache.entries,
   messenger
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

   n = 1000;
   if( argc == 2)
      n = atoi( argv[ 1]);

   // create an object with isa pointer
   space.isa = &class0;
   obj       = &space + 1;

   for( i = 0; i < n; i++)
      for( j = 0; j < 1000000; j++)
         call( obj, 0x18480000, (void *) 0x1848);  // modified to be index zero
   return( 0);
}

