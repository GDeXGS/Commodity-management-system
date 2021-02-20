#include <all.h>
#include <main.h>

int main(void)
{
	int cmd;
	
	// 定义三条链表头指针
	struct commodity_info *comm_head, *shop_head, *purc_head;
	comm_head = new_commodity_info( );
	shop_head = new_commodity_info( );
	purc_head = new_commodity_info( );
	if( comm_head == NULL || shop_head == NULL || purc_head == NULL )
	{
		printf("申请内存出错！\n");
		return -1;
	}
	
	while(1)
	{
		system("clear");
		printf("\n\033[1;33m***********************************主界面***********************************\033[0m\n");
		traverse_and_display( &(comm_head->lh_node), 0 );
		printf("\n\033[1;34m功能菜单：\n");
		printf("1、添加商品到购物车\n");
		printf("2、按价格从小到大排序\n");
		printf("3、进入购物车界面\n");
		printf("4、进入管理员界面\n");
		printf("5、按编号从小到大排序\n");
		printf("6、输入其他数字，退出\033[0m\n\n");
		printf("请输入命令：");
		cmd = get_int_save();
		
		switch( cmd )
		{
			case 1:
					add_shopping_cart( &(comm_head->lh_node), &(shop_head->lh_node) );
					break;
			case 2:
					price_bubble_sort( &(comm_head->lh_node) );
					break;
			//case 2:
			//		price_quickSort( comm_head->lh_node.next, comm_head->lh_node.prev );
			//		break;
			case 3:
					shopping_cart( comm_head, shop_head, purc_head );
					break;
			case 4:
					administrator( comm_head, shop_head, purc_head );
					break;
			//case 5:
			//		code_quickSort( comm_head->lh_node.next, comm_head->lh_node.prev );
			//		break;
			case 5:
					code_bubble_sort( &(comm_head->lh_node) );
					break;
			default:
					goto exit;
		}
	}
	
exit:
	rm_list( &(comm_head->lh_node) );
	rm_list( &(shop_head->lh_node) );
	rm_list( &(purc_head->lh_node) );
	return 0;
}














