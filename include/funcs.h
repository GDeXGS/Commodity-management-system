#ifndef _FUNCS_H_
#define _FUNCS_H_

#include <all.h>

/* funcs.c */
int get_int_save( void );
void del( struct list_head *pos );
void rm_list( struct list_head *head );
void empty_list( struct list_head *head );
struct commodity_info *new_commodity_info( void );
struct list_head *find( struct list_head *head, int code );
void traverse_and_display( struct list_head *head, int type );
void insert( struct list_head *new_node, struct list_head *pos );

#endif