#define _CRT_SECURE_NO_WARNINGS
#include "contactList.h"

void menu()
{
	printf("1.add		2.del\n");
	printf("3.search	4.modify\n");
	printf("5.show		6.sort\n");
	printf("0.exit\n");

}
int main()
{
	//����ͨѶ¼
	struct ContactList con;//����1000����λ����Ϣ��size
	initList(&con);
	int input = 0;
	do
	{
		menu();
		printf("��ѡ��");
		scanf("%d", &input);
		switch (input)
		{
		case ADD:
			addList(&con);
			break;
		case DEL:
			delList(&con);
			break;
		case SEARCH:
			searList(&con);
			break;
		case MODIFY:
			modList(&con);
			break;
		case SHOW:
			showList(&con);
			break;
		case SORT:
			sortList(&con);
			break;
		case EXIT:
			printf("�˳�ͨѶ¼��\n");
			break;	
		default:
			printf("ѡ�����\n");
				break;
		}
	} while (1);
}