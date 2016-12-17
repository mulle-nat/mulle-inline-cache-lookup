#include <stddef.h>
#include <stdint.h>


#define HAVE_TPS  0


struct cacheentry
{
   uintptr_t   uniqueid;
   void        *(*functionpointer)( void *, uintptr_t, void *);
};


struct cache
{
   uintptr_t           mask;
   struct cacheentry   entries[ 1];
};


struct xclass
{
   struct cacheentry   *entries;
   void                *(*functionpointer)( void *, uintptr_t, void *);
};


struct runtime
{
   char           *name;
   struct xclass   *ctab[ 8];
};


static inline struct cache  *get_cache_from_entries( struct cacheentry *entries)
{
   return( (cache *) &((char *) entries)[ -(int)  offsetof( struct cache, entries)]);
}


static inline void  *call( void *obj,
                           uintptr_t methodid,
                           void *parameter)
{
   extern struct runtime   global;
   int                     index;
   void                    *(*f)( void *, uintptr_t, void *);
   struct cache            *cache;
   struct cacheentry       *entries;
   struct cacheentry       *entry;
   struct xclass            *cls;
   uintptr_t               offset;

   if( __builtin_expect( ! obj, 0))
      return( obj);

   // get class from object or tagged pointer table
#if HAVE_TPS
   index = (uintptr_t) obj & 0x7;
   if( __builtin_expect( index, 0))
      cls = global.ctab[ index];
   else
#endif
      cls = ((xclass **) obj)[ -1];

   // get cache from class
   entries = cls->entries;
   cache   = get_cache_from_entries( entries);

   // get entry for method in cache
   offset  = methodid & cache->mask;
   entry   = (cacheentry *) &((char *) entries)[ offset];

   // use default functionpointer if no cache hit
   if( __builtin_expect( (entry->uniqueid == methodid), 1))
      f = entry->functionpointer;
   else
      f = cls->functionpointer;

   return( (*f)( obj, methodid, parameter));
}


void  *const_call( void *obj,
                   void *parameter)
{
   return( call( obj, 0x18481848, parameter));
}

