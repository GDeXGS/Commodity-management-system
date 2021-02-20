#include <all.h>
#include <funcs.h>

int get_int_save( void )
{
	int input, ret;
	
	while(1)		
	{
		ret = scanf("%d", &input); 

		if(ret != 1)	
		{
			printf("输入出错！\n");			// 提示
			while( getchar() != '\n' );		// 清空缓冲区
			printf("请重新输入：");			// 提示
			continue;						// scanf重新获取
		}

		break;	// 获取成功，退出死循环
	}
	
	return input;
}


// 新建商品信息结点
struct commodity_info *new_commodity_info( void )
{
	struct commodity_info *new = malloc( sizeof(struct commodity_info) );
	
	if( new != NULL )
	{
		INIT_LIST_HEAD( &(new->lh_node) );
		return new;
	}
	else
	{
		printf("申请内存出错\n");
		return NULL;
	}
}

// 插入到某结点后
void insert( struct list_head *new_node, struct list_head *pos )
{
	list_add( new_node, pos ); // 插入到某结点后
}

// 遍历并打印信息
void traverse_and_display( struct list_head *head, int type )
{
	if( head == NULL )
		goto traverse_and_display_error;

	if( head->next == head )
		return;
	
	printf("\033[1;32m");
	if( type )
	{
		printf("\n购物车/已购：\n");
		printf("商品编号\t商品名字\t商品价格\t购买数量\t购买单位总价\n");
	}
	else
	{
		printf("\n商品库存：\n");
		printf("商品编号\t商品名字\t商品价格\t商品库存\n");
	}
	
	double sum=0;
	struct list_head *lh_pos,*lh_n;
	
	list_for_each_safe( lh_pos, lh_n, head )
	{
		struct commodity_info *pos = list_entry( lh_pos, struct commodity_info, lh_node );
		
		if( type )
		{
			printf("   %d\t\t  %s\t\t%f\t   %d\t\t  %f\n", pos->code, pos->name, pos->price, pos->numbers, pos->price*pos->numbers);
			sum += pos->price*pos->numbers;
		}
		else
		{
			printf("   %d\t\t  %s\t\t%f\t   %d\n", pos->code, pos->name, pos->price, pos->numbers);
		}
	}
	
	if( type )
		printf("\n\t\t\t\t\t\t\t商品总价：%lf\n", sum);
	
	return;
	
traverse_and_display_error:
	printf("无效输入\n");
	return;
}

// 根据code查找商品信息
struct list_head *find( struct list_head *head, int code )
{
	if( head == NULL )
		goto find_error;
	
	struct list_head *lh_pos,*lh_n;
	
	list_for_each_safe( lh_pos, lh_n, head )
	{
		if( list_entry( lh_pos, struct commodity_info, lh_node )->code == code )
		{
			return lh_pos;
		}
	}
	
	return NULL;
	
find_error:
	printf("无效输入\n");
}

// 删除商品信息节点
void del( struct list_head *pos )
{
	if( list_empty(pos) == 1 )
		free( list_entry( pos, struct commodity_info, lh_node ) ); 
	else
	{
		list_del( pos ); // 移出链表
		free( list_entry( pos, struct commodity_info, lh_node ) ); // 释放
	}
	printf("删除结点成功\n");
}

// 清空链表
void empty_list( struct list_head *head )
{
	if( head == NULL )
		goto empty_list_error;
	
	struct list_head *lh_pos,*lh_n;
	struct commodity_info *comm_pos;

	list_for_each_safe( lh_pos, lh_n, head )
	{
		comm_pos = list_entry( lh_pos, struct commodity_info, lh_node );
		list_del( &(comm_pos->lh_node) ); // 删除
		free( comm_pos ); // 释放
	} 
	
	printf("链表已清空\n");
	return;
	
empty_list_error:
	printf("无效输入\n");
}

// 摧毁链表
void rm_list( struct list_head *head )
{
	
	if( head == NULL )
		goto rm_list_error;
	
	struct list_head *lh_pos,*lh_n;
	struct commodity_info *comm_pos;

	list_for_each_safe( lh_pos, lh_n, head )
	{
		comm_pos = list_entry( lh_pos, struct commodity_info, lh_node );
		list_del( &(comm_pos->lh_node) ); // 删除
		free( comm_pos ); // 释放
	} 
	
	comm_pos = list_entry( head, struct commodity_info, lh_node );
	free( comm_pos );
	
	printf("链表已摧毁\n");
	return;
	
rm_list_error:
	printf("无效输入\n");
}

