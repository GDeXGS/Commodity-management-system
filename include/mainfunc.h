#ifndef _MAINFUNC_H_
#define _MAINFUNC_H_

#include <all.h>

/* mainfunc.c */
void code_bubble_sort( struct list_head *comm_lh_head );
void price_bubble_sort( struct list_head *comm_lh_head );
void data_assignment( struct list_head *pos1, struct list_head *pos2 );
void code_quickSort( struct list_head *pos_l, struct list_head *pos_r );
void price_quickSort( struct list_head *pos_l, struct list_head *pos_r );
void add_shopping_cart( struct list_head *comm_lh_head, struct list_head *shop_lh_head );

#endif