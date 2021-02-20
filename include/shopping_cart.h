#ifndef _SHOPPING_CART_H_
#define _SHOPPING_CART_H_

#include <all.h>

/* shopping_cart.c */
void shop_interface( struct list_head *shop_lh_head );
void check( struct list_head *comm_lh_head, struct list_head *shop_lh_head );
void shop_change_info( struct list_head *comm_lh_head, struct list_head *shop_lh_head );
void purchase( struct list_head *comm_lh_head, struct list_head *shop_lh_head, struct list_head *purchased_lh_head );
void shopping_cart( struct commodity_info *comm_head, struct commodity_info *shop_head, struct commodity_info *purc_head );

#endif