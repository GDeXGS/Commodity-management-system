#include <all.h>
#include <shopping_cart.h>

// 购物车界面
void shopping_cart( struct commodity_info *comm_head, struct commodity_info *shop_head, struct commodity_info *purc_head )
{
	int cmd;
	
	while(1)
	{
		shop_interface( &(shop_head->lh_node) );
		
		// 检测购物车商品在库存中是否充足
		check( &(comm_head->lh_node), &(shop_head->lh_node) );
		
		printf("请输入命令：");
		cmd = get_int_save();
		
		switch( cmd )
		{
			case 1:
					purchase( &(comm_head->lh_node), &(shop_head->lh_node), &(purc_head->lh_node) );
					break;
			case 2:
					shop_change_info( &(comm_head->lh_node), &(shop_head->lh_node) );
					break;
			default:
					goto exit;
		}
	}
	
exit:
	return;
}

// 界面
void shop_interface( struct list_head *shop_lh_head )
{
	system("clear");
	printf("\n\033[1;33m*********************************购物车界面*********************************\033[0m\n");
	traverse_and_display( shop_lh_head, 1 );
	printf("\n\033[1;34m功能菜单：\n");
	printf("1、直接购买\n");
	printf("2、更改购物车商品信息\n");
	printf("3、输入其他数字，退出\033[0m\n\n");
}

// 检测购物车商品在库存中是否充足
void check( struct list_head *comm_lh_head, struct list_head *shop_lh_head )
{
	int input;
	struct list_head *lh_pos,*lh_n;
	struct commodity_info *comm, *shop, *purc = NULL;
	
	list_for_each_safe( lh_pos, lh_n, shop_lh_head )
	{
		shop = list_entry( lh_pos, struct commodity_info, lh_node );
		comm = list_entry( find( comm_lh_head, shop->code ), struct commodity_info, lh_node );
		
		if( shop->numbers > comm->numbers )
		{
			while( 1 )
			{
				printf("%s库存不足，请重新购买！\n", comm->name);
				printf("库存剩余：%d\n", comm->numbers);
				printf("请输入商品数量：");
				input = get_int_save();
				
				if( input <= comm->numbers )
				{
					shop->numbers = input;
					printf("添加购物车成功\n");
					break;
				}

			}
			
			shop_interface( shop_lh_head );
		}
	}

}


// 购物车：直接购买
void purchase( struct list_head *comm_lh_head, struct list_head *shop_lh_head, struct list_head *purchased_lh_head )
{
	struct list_head *lh_pos,*lh_n;
	struct commodity_info *comm, *shop, *purc;
	
	list_for_each_safe( lh_pos, lh_n, shop_lh_head )
	{
		
		shop = list_entry( lh_pos, struct commodity_info, lh_node );
		
		// 根据code查找库存中的商品信息（一定能找到）
		comm = list_entry( find( comm_lh_head, shop->code ), struct commodity_info, lh_node );
		
		// 库存信息更改
		comm->numbers -= shop->numbers;
		if( comm->numbers <= 0 ) // 库存为零
			del( &(comm->lh_node) ); // 删除此商品
		
		while( 1 )
		{
			// 根据code查找已购链表中的商品信息
			purc = NULL;
			if( find( purchased_lh_head, shop->code ) != NULL )
				purc = list_entry( find( purchased_lh_head, shop->code ), struct commodity_info, lh_node );
			
			// 已购信息更改
			if( purc != NULL ) // 已购记录中有此商品
			{
				if( purc->price == shop->price ) // 价格相同,记录到已购链表，退出
				{
					purc->numbers += shop->numbers;
					del( lh_pos ); // 从购物车链表中删除此商品
					break;
				}
				else // 价格不同，更改编号，继续查找
				{
					shop->code += 1000;  // 按一定规律更改编号,然后再去已购链表中寻找（进入下一个循环）
				}
			}
			else // 已购记录中没有此商品,记录到已购链表，退出
			{
				list_del( lh_pos ); // 移出购物车链表
				insert( lh_pos, purchased_lh_head->prev ); // 插入已购链表
				printf("插入已购链表\n");
				break;
			}
		}
		
	}
}

// 购物车：更改购物信息
void shop_change_info( struct list_head *comm_lh_head, struct list_head *shop_lh_head )
{
	int code, num;
	struct commodity_info *comm, *shop;
	struct list_head *comm_lh_node, *shop_lh_node;
	
	while(1)
	{
		printf("请输入商品编号(输入0，返回购物车界面)：");
		code = get_int_save();
		if( code == 0 )
			break;
		
		// 查找库存中的对应商品
		comm_lh_node = find( comm_lh_head, code );
		comm = list_entry(comm_lh_node, struct commodity_info, lh_node);
		
		// 查找购物车中的对应商品
		shop_lh_node = find( shop_lh_head, code );
		
		if( shop_lh_node != NULL ) // 购物车中的有此商品
		{
			shop = list_entry( shop_lh_node, struct commodity_info, lh_node );
			
			printf("更改数量为（输入-1，返回）：");
			num = get_int_save();
			if( num == -1 )
				break;
			
			if( num <= 0 ) // 数量小于等于0
			{
				del( shop_lh_node ); // 删除此商品
				break;
			}
			else if( num > comm->numbers ) // 库存不足
			{
				printf("库存不足，请重新购买！\n");
			}
			else // 库存充足
			{
				shop->numbers = num; // 数量更改
				printf("购物车信息更改成功！\n"); // 显示更改成功，但不修改库存数量
				break;
			}
			
		}
		else // 购物车中无此商品
		{
			printf("没有此商品，请重新购买！\n");
		}
	}
	
	return;
}