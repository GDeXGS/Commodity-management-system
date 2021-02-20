#include <all.h>
#include <administrator.h>

// 管理员界面
void administrator( struct commodity_info *comm_head, struct commodity_info *shop_head, struct commodity_info *purc_head )
{
	int cmd;
	
	while(1)
	{
		system("clear");
		printf("\n\033[1;33m*********************************管理员界面*********************************\033[0m\n");
		traverse_and_display( &(comm_head->lh_node), 0 );
		printf("\n\033[1;34m功能菜单：\n");
		printf("1、录入商品信息\n");
		printf("2、查看购买记录\n");
		printf("3、更改商品信息\n");
		printf("4、输入其他数字，退出\033[0m\n\n");
		printf("请输入命令：");
		cmd = get_int_save();
		
		switch( cmd )
		{
			case 1:
					input_commodity_info( &(comm_head->lh_node), &(shop_head->lh_node) );
					break;
			case 2:
					show_purchased( &(purc_head->lh_node) );
					break;
			case 3:
					change_commodity_info( &(comm_head->lh_node), &(shop_head->lh_node) );
					break;
			default:
					goto exit;
		}
		
	}

exit:
	return;
}

// 管理员：录入商品信息
void input_commodity_info( struct list_head *comm_lh_head, struct list_head *shop_lh_head )
{
	// 临时创建商品信息节点，用不上时需释放
	struct commodity_info *info = new_commodity_info( );
	if( info == NULL )
	{
		printf("申请内存出错！\n");
		return;
	}
	
	printf("请输入商品编号(输入0，返回)：");
	info->code = get_int_save();
	if( info->code == 0 )
		return;
	
	/* 查找并判断库存中是否已有此商品 */
	struct list_head *comm_lh_node = find( comm_lh_head, info->code );
	
	if( comm_lh_node != NULL ) // 已有此商品
	{
		printf("已有此商品\n");
		free( info ); // 已有此商品，释放临时节点
		
		admi_change_info( comm_lh_node, comm_lh_head, shop_lh_head ); // 更改商品信息

	}
	else// 没有此商品
	{
		/* 这里的名字输入没做保护，也没做退出接口 */
		printf("请输入商品名字：");
		scanf("%s", info->name);
		printf("请输入商品数量：");
		info->numbers = get_int_save();
		printf("请输入商品价格：");
		scanf("%f", &info->price);
		
		if( info->numbers > 0 )
			list_add_tail( &(info->lh_node), comm_lh_head ); // 插入到head前面，即链表尾
		else
			free( info ); // 释放
		
		printf("录入成功\n");
	}
	
	return;
	
}

// 管理员：更改商品信息
void change_commodity_info( struct list_head *comm_lh_head, struct list_head *shop_lh_head )
{
	int cmd;
	
	printf("请输入商品编号(输入0，返回)：");
	cmd = get_int_save();
	if( cmd == 0 )
		return;
	
	/* 查找并判断库存是否已有此商品 */
	struct list_head *comm_lh_node = find( comm_lh_head, cmd );
	
	if( comm_lh_node != NULL ) // 有此商品
	{
		admi_change_info( comm_lh_node, comm_lh_head, shop_lh_head );  // 更改商品信息
	}
	else// 没有此商品
	{
		printf("没有此商品!\n");
	}
	
	return;
	
}

// 更改信息函数
void admi_change_info( struct list_head *comm_lh_node, struct list_head *comm_lh_head, struct list_head *shop_lh_head )
{
	int cmd, input;
	float f_input;
	char newname[16];
	
	struct commodity_info *comm = list_entry( comm_lh_node, struct commodity_info, lh_node );
	
	printf("\n\033[1;34m请选择需要更改的信息：\n");
	printf("1、商品编号\n");
	printf("2、商品名字\n");
	printf("3、商品价格\n");
	printf("4、商品库存\n");
	printf("5、输入其他数字，退出\033[0m\n\n");
	printf("请输入命令：");
	cmd = get_int_save();
	
		
	switch( cmd )
	{
		case 1: // 更改编号
				{
					printf("将编号更改为(输入0，返回)：");
					struct list_head *tmp_find;
					
					while( 1 )
					{
						input = get_int_save();
						if( input == 0 )
							break;
						
						/* 查找并判断库存是否已有此编号 */ 
						tmp_find = find( comm_lh_head, input );
						
						if( tmp_find != NULL ) // 有此编号
							printf("已有此编号,请重新输入：");
						else // 没有此编号
						{	
							/* 查找并判断购物车是否有“原编号” */
							struct list_head *shop_lh_node = find( shop_lh_head, comm->code );
							if( shop_lh_node != NULL ) // 有此编号
							{
								struct commodity_info *shop = list_entry( shop_lh_node, struct commodity_info, lh_node );
								shop->code = input; // 修改购物车中编号
							}
							
							comm->code = input; // 修改库存编号
							
							break;
						}
					}
					
					break;
				}
		case 2: // 更改名字
				{
					printf("将名字更改为(输入-1，返回)：");
					scanf("%s", newname);
					if( strcmp( newname, "-1" ) == 0 )
						break;
					
					stpcpy( comm->name, newname );
					
					break;
				}
		case 3: // 更改价格
				{
					printf("将价格更改为(输入-1，返回)：");
					scanf("%f", &f_input);
					if( f_input == -1 )
						break;
						
					comm->price = f_input; // 修改库存中的商品价格
					
					/* 查找并判断购物车是否有此商品 */
					struct list_head *shop_lh_node = find( shop_lh_head, comm->code );
					if( shop_lh_node != NULL ) // 有此商品
					{
						struct commodity_info *shop = list_entry( shop_lh_node, struct commodity_info, lh_node );
						shop->price = f_input; // 修改购物车中的商品价格
					}
					
					break;
				}
		case 4: // 更改库存
				{
					printf("将库存更改为(输入-1，返回)：");
					input = get_int_save();
					if( input == -1 )
						break;
						
					if( input <= 0 )
						del( &(comm->lh_node) );
					else
						comm->numbers = input;

					break;
				}
		default:
				break;
	}
}

// 已购记录
void show_purchased( struct list_head *purc_lh_head )
{
	int cmd;
	
	system("clear");
	printf("\n\033[1;33m**********************************已购记录**********************************\033[0m\n");
	traverse_and_display( purc_lh_head, 1 );
	
	printf("\n\033[1;34m功能菜单：\n");
	printf("1、清空已购记录\n");
	printf("2、输入其他数字，退出\033[0m\n\n");
	printf("请输入输入命令：");
	cmd = get_int_save();

	if( cmd == 1 )
		empty_list( purc_lh_head );
	
}















