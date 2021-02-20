#ifndef _ADMINISTRATOR_H_
#define _ADMINISTRATOR_H_

#include <all.h>

/* administrator.c */
void show_purchased( struct list_head *purc_lh_head );
void input_commodity_info( struct list_head *comm_lh_head, struct list_head *shop_lh_head );
void change_commodity_info( struct list_head *comm_lh_head, struct list_head *shop_lh_head );
void admi_change_info( struct list_head *comm_lh_node, struct list_head *comm_lh_head, struct list_head *shop_lh_head );
void administrator( struct commodity_info *comm_head, struct commodity_info *shop_head, struct commodity_info *purc_head );

#endif