#include <all.h>
#include <mainfunc.h>

// 本文件自己用的函数：数据赋值,将pos2的数据赋值给pos1
void data_assignment( struct list_head *pos1, struct list_head *pos2 )
{
	struct commodity_info *comm_pos1 = list_entry( pos1, struct commodity_info, lh_node );
	struct commodity_info *comm_pos2 = list_entry( pos2, struct commodity_info, lh_node );
	
	comm_pos1->code = comm_pos2->code;
	comm_pos1->price = comm_pos2->price;
	comm_pos1->numbers = comm_pos2->numbers;
	stpcpy( comm_pos1->name, comm_pos2->name );
	
}

// 主界面：添加商品到购物车
void add_shopping_cart( struct list_head *comm_lh_head, struct list_head *shop_lh_head )
{
	int code, num;
	struct commodity_info *comm, *shop;
	struct list_head *comm_lh_node, *shop_lh_node;
	
	
	while(1)
	{
		printf("请输入商品编号(输入0，返回主界面)：");
		code = get_int_save();
			if( code == 0 )
				break;
		
		
		
		// 查看库存是否充足
		comm_lh_node = find( comm_lh_head, code ); 
		shop_lh_node = find( shop_lh_head, code );
		
		if( comm_lh_node != NULL ) // 库存中的有此商品
		{
			printf("请输入购买数量：");
			num = get_int_save();
		
			comm = list_entry(comm_lh_node, struct commodity_info, lh_node);
			
			if( shop_lh_node != NULL ) // 购物车中有此商品
			{
				shop = list_entry(comm_lh_node, struct commodity_info, lh_node);
				
				if( shop->numbers + num > comm->numbers ) // 判断库存是否充足
					printf("库存不足，请重新购买！\n");
				else
				{
					shop->numbers += num; // 数量更改
					printf("添加购物车成功！\n"); // 显示添加成功，但不修改库存数量
					break;
				}
			}
			else // 购物车中无此商品
			{
				if( num > comm->numbers ) // 判断库存是否充足
					printf("库存不足，请重新购买！\n");
				else
				{
					struct commodity_info *info = new_commodity_info( ); // 新建商品信息节点
					if( info == NULL )
					{
						printf("申请内存出错！\n");
						return;
					}
					
					data_assignment( &(info->lh_node), &(comm->lh_node) ); // 录入数据
					info->numbers = num; // 数量更改
					
					insert( &(info->lh_node), shop_lh_head->prev ); // 插入购物车链表
					printf("添加购物车成功！\n"); // 显示添加成功，但不修改库存数量
					break;
				}
			}
				
		}
		else // 库存中的没有此商品
		{
			printf("没有此商品，请重新购买！\n");
		}
	}
	
	return;

}

// 主界面：价格排序,冒泡
void price_bubble_sort( struct list_head *comm_lh_head )
{
	struct list_head *pos_head = comm_lh_head;
	struct list_head *pos_i = comm_lh_head->next; // 首个数据节点
	struct list_head *pos_j = comm_lh_head->next;
	
	struct commodity_info *comm_pos_j, *comm_pos_j_next;
	struct commodity_info *tmp = new_commodity_info( );
	if( tmp == NULL )
	{
		printf("申请内存出错！\n");
		return;
	}
	
	while( pos_i != comm_lh_head )
	{
		pos_j = comm_lh_head->next; // j总是从首个数据节点开始
		
		while( pos_j != pos_head->prev )
		{
			comm_pos_j = list_entry( pos_j, struct commodity_info, lh_node );
			comm_pos_j_next = list_entry( pos_j->next, struct commodity_info, lh_node );
			
			if( comm_pos_j->price > comm_pos_j_next->price )
			{
				// 交换数据
				data_assignment( &(tmp->lh_node), pos_j );
				data_assignment( pos_j, pos_j->next );
				data_assignment( pos_j->next, &(tmp->lh_node) );
			}
		
			pos_j = pos_j->next;
		}
		
		pos_i = pos_i->next;  // 想当于i，外循环的总次数
		pos_head = pos_head->prev; // 确定好一个最大的数，往前移一位

	}
	
	free( tmp );
}

// 主界面：编码排序,冒泡
void code_bubble_sort( struct list_head *comm_lh_head )
{
	struct list_head *pos_head = comm_lh_head;
	struct list_head *pos_i = comm_lh_head->next; // 首个数据节点
	struct list_head *pos_j = comm_lh_head->next;
	
	struct commodity_info *comm_pos_j, *comm_pos_j_next;
	struct commodity_info *tmp = new_commodity_info( );
	if( tmp == NULL )
	{
		printf("申请内存出错！\n");
		return;
	}
	
	while( pos_i != comm_lh_head )
	{
		pos_j = comm_lh_head->next; // j总是从首个数据节点开始
		
		while( pos_j != pos_head->prev )
		{
			comm_pos_j = list_entry( pos_j, struct commodity_info, lh_node );
			comm_pos_j_next = list_entry( pos_j->next, struct commodity_info, lh_node );
			
			if( comm_pos_j->code > comm_pos_j_next->code )
			{
				data_assignment( &(tmp->lh_node), pos_j );
				data_assignment( pos_j, pos_j->next );
				data_assignment( pos_j->next, &(tmp->lh_node) );
			}
		
			pos_j = pos_j->next;
		}
		
		pos_i = pos_i->next; // 想当于i，外循环的总次数
		pos_head = pos_head->prev; // 确定好一个最大的数，往前移移位
		
	}
	
	free( tmp );
}


// 主界面：价格排序，快速
void price_quickSort( struct list_head *pos_l, struct list_head *pos_r )
{
	if( pos_l == pos_r || pos_l->prev == pos_r )
		return;
	
	// 获取key值
	struct commodity_info *comm_pos_l = list_entry( pos_l, struct commodity_info, lh_node );
	int key = comm_pos_l->price;
	
	// 临时存储comm_pos_l的数据，用完tmp需释放掉
	struct commodity_info *tmp = new_commodity_info( );
	if( tmp == NULL )
	{
		printf("申请内存出错！\n");
		return;
	}
	data_assignment( &(tmp->lh_node), &(comm_pos_l->lh_node) );
	
	// 位置指针
	struct list_head *pos_i = pos_l;
	struct list_head *pos_j = pos_r;
	struct commodity_info *comm_pos_i = list_entry( pos_i, struct commodity_info, lh_node );
	struct commodity_info *comm_pos_j = list_entry( pos_j, struct commodity_info, lh_node );
	
	
	while( pos_i != pos_j )
	{
		// 从右往左找到比key值小的
		while( pos_i != pos_j && comm_pos_j->price >= key )
		{
			pos_j = pos_j->prev;
			comm_pos_j = list_entry( pos_j, struct commodity_info, lh_node );
		}
		
		// 数据交换
		if( pos_i != pos_j )
		{
			data_assignment( pos_i, pos_j );
			//pos_i = pos_i->next; // 会出现跃过一个节点的情况，为何呢?
		}
		
		// 从左往右找到比key值大的
		while( pos_i != pos_j && comm_pos_i->price < key )
		{
			pos_i = pos_i->next;
			comm_pos_i = list_entry( pos_i, struct commodity_info, lh_node );
		}
			
		// 数据交换
		if( pos_i != pos_j )
		{
			data_assignment( pos_j, pos_i );
			//pos_j = pos_j->prev;
		}
	}
	
	// 找到key值对应数据最合适的位置，填入数据
	data_assignment( pos_i, &(tmp->lh_node) );
	free( tmp ); // 释放

	price_quickSort( pos_l, pos_i->prev );
	price_quickSort( pos_i->next, pos_r );
	
}

// 主界面：编号排序，快速
void code_quickSort( struct list_head *pos_l, struct list_head *pos_r )
{
	if( pos_l == pos_r || pos_l->prev == pos_r )
		return;
	
	struct commodity_info *comm_pos_l = list_entry( pos_l, struct commodity_info, lh_node );
	int key = comm_pos_l->code;
	
	// 临时存储comm_pos_l的数据
	struct commodity_info *tmp = new_commodity_info( );
	if( tmp == NULL )
	{
		printf("申请内存出错！\n");
		return;
	}
	data_assignment( &(tmp->lh_node), &(comm_pos_l->lh_node) );
	
	struct list_head *pos_i = pos_l;
	struct list_head *pos_j = pos_r;
	struct commodity_info *comm_pos_i = list_entry( pos_i, struct commodity_info, lh_node );
	struct commodity_info *comm_pos_j = list_entry( pos_j, struct commodity_info, lh_node );
	
	
	while( pos_i != pos_j )
	{
		while( pos_i != pos_j && comm_pos_j->code >= key )
		{
			pos_j = pos_j->prev;
			comm_pos_j = list_entry( pos_j, struct commodity_info, lh_node );
		}
		
		if( pos_i != pos_j )
		{
			data_assignment( pos_i, pos_j );
			//pos_i = pos_i->next;
		}
		
		while( pos_i != pos_j && comm_pos_i->code < key )
		{
			pos_i = pos_i->next;
			comm_pos_i = list_entry( pos_i, struct commodity_info, lh_node );
		}
			
		if( pos_i != pos_j )
		{
			data_assignment( pos_j, pos_i );
			//pos_j = pos_j->prev;
		}
	}
	
	data_assignment( pos_i, &(tmp->lh_node) );
	free( tmp ); // 释放
	
	code_quickSort( pos_l, pos_i->prev );
	code_quickSort( pos_i->next, pos_r );
	
}

























