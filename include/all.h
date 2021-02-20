#ifndef _ALL_H_
#define _ALL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <list.h>

struct commodity_info
{
	int code;
	float price;
	int numbers;
	char name[16];
	struct list_head lh_node;
};

/* funcs.c */
extern int get_int_save( void );
extern void del( struct list_head *pos );
extern void rm_list( struct list_head *head );
extern void empty_list( struct list_head *head );
extern struct commodity_info *new_commodity_info( void );
extern struct list_head *find( struct list_head *head, int code );
extern void traverse_and_display( struct list_head *head, int type );
extern void insert( struct list_head *new_node, struct list_head *pos );


#endif