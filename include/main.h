#ifndef _MAIN_H_
#define _MAIN_H_

#include <all.h>

/* mainfunc.c */
extern void code_bubble_sort( struct list_head *comm_lh_head );
extern void price_bubble_sort( struct list_head *comm_lh_head );
extern void data_assignment( struct list_head *pos1, struct list_head *pos2 );
extern void code_quickSort( struct list_head *pos_l, struct list_head *pos_r );
extern void price_quickSort( struct list_head *pos_l, struct list_head *pos_r );
extern void add_shopping_cart( struct list_head *comm_lh_head, struct list_head *shop_lh_head );

/* administrator.c */
void administrator( struct commodity_info *comm_head, struct commodity_info *shop_head, struct commodity_info *purc_head );

/* shopping_cart.c */
void shopping_cart( struct commodity_info *comm_head, struct commodity_info *shop_head, struct commodity_info *purc_head );

#endif