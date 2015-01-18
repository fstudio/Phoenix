/*
 *	Copyright (c) 2008 , 
 *		Cloud Wu . All rights reserved.
 *
 *		http://www.codingnow.com
 *
 *	Use, modification and distribution are subject to the "New BSD License"
 *	as listed at <url: http://www.opensource.org/licenses/bsd-license.php >.
 */

#ifndef MANUAL_GARBAGE_COLLECTOR_H
#define MANUAL_GARBAGE_COLLECTOR_H


#include <stddef.h>
#include <Runtime/rtdefs.h>

struct gc_weak_table;

PKGEXTERN void gc_init();
PKGEXTERN void gc_exit();

PKGEXTERN void gc_enter();
PKGEXTERN void gc_leave(void *p,...);

PKGEXTERN void* gc_malloc(size_t sz,void *parent,void (*finalizer)(void *));
PKGEXTERN void* gc_realloc(void *p,size_t sz,void *parent);
PKGEXTERN void gc_link(void *parent,void *prev,void *now);
PKGEXTERN void gc_collect();

PKGEXTERN void* gc_clone(void *from,size_t sz);

PKGEXTERN void gc_dryrun();

PKGEXTERN struct gc_weak_table* gc_weak_table(void *parent);
PKGEXTERN void* gc_weak_next(struct gc_weak_table *cont,int *iter);

#endif
