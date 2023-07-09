#define _CRT_SECURE_NO_WARNINGS
#include "contactList.h"
//排序功能待实现
//存放1000个好友的信息
//包含名字、电话、性别、住址、年龄
/*功能：增加好友信息
	   删除好友信息
	   查找好友信息
	   修改好友信息
	   打印好友信息
	   排序
	   */
void initList(struct ContactList* ps)
{
	memset(ps->data, 0, sizeof(ps->data));
	ps->size = 0;//设置通讯录最初为0个信息
}
static int findName(char aimName[MAX_NAME], const struct ContactList* ps)
{
	int i = 0;
	for (i = 0; i < ps->size; i++)
	{
		if (strcmp(ps->data[i].name, aimName) == 0)
		{

			return i;
		}
	}
	return -1;
		
}
void addList(struct ContactList* ps)
{
	if (ps->size == MAX)
	{
		printf("通讯录已满。");
	}
	else
	{
		printf("请输入名字：");
		scanf("%s", ps->data[ps->size].name);
		printf("请输入年龄：");
		scanf("%d", &(ps->data[ps->size].age));
		printf("请输入性别：");
		scanf("%s", ps->data[ps->size].sex);
		printf("请输入地址：");
		scanf("%s", ps->data[ps->size].addr);
		printf("请输入电话：");
		scanf("%s", ps->data[ps->size].tele);
		ps->size++;
		printf("添加成功！\n");
	}
}
void showList(const struct ContactList* ps)
{
	if (ps->size == 0)
	{
		printf("通讯录为空。\n");

	}
	else
	{
		printf("%-10s\t%-4s\t%-5s\t%-12s\t%-20s\n", "名字", "年龄", "性别", "电话", "地址");
		for (int i = 0; i < ps->size; i++)
		{
			printf("%-10s\t%-4d\t%-5s\t%-12s\t%-20s\n", ps->data[i].name, ps->data[i].age, ps->data[i].sex, ps->data[i].tele, ps->data[i].addr);
		}
	}
}
void delList(struct ContactList* ps)
{
	if (ps->size == 0)
	{
		printf("通讯录为空！\n");

	}
	else
	{

		char delName[MAX_NAME];
		printf("请输入要删除的联系人姓名：");
		scanf("%s", delName);
		int pos = findName(delName, ps);
		if (pos == -1)
		{
			printf("无该联系人。\n");
		}
		else
		{
			for (int j = pos; j < ps->size - 1; j++)
			{
				ps->data[j] = ps->data[j + 1];
			}
			ps->size--;
			printf("删除成功！\n");
		}
	}
}
void searList(const struct ContactList* ps)
{
	if (ps->size == 0)
	{
		printf("通讯录为空！\n");

	}
	else
	{
		char searName[MAX_NAME];
		printf("请输入要查找的联系人姓名：");
		scanf("%s", searName);
		int pos = findName(searName, ps);
		if (pos == -1)
		{
			printf("无该联系人。\n");
		}
		else
		{
			printf("%-10s\t%-4s\t%-5s\t%-12s\t%-20s\n", "名字", "年龄", "性别", "电话", "地址");
			printf("%-10s\t%-4d\t%-5s\t%-12s\t%-20s\n", ps->data[pos].name, ps->data[pos].age, ps->data[pos].sex, ps->data[pos].tele, ps->data[pos].addr);
		}
	}
}
void modList(struct ContactList* ps)
{
	if (ps->size == 0)
	{
		printf("通讯录为空！\n");

	}
	else
	{
		char modName[MAX_NAME];
		printf("请输入要修改的联系人姓名：");
		scanf("%s", modName);
		int pos = findName(modName, ps);
		if (pos == -1)
		{
			printf("无该联系人。\n");
		}
		int p;
		printf("请输入要修改的项目：\n1.姓名	2.性别	3.年龄	4.地址	5.电话\n");
		scanf("%d", &p);
		switch (p)
		{
		case 1:
			printf("请输入新名字：");
			scanf("%s", ps->data[pos].name);
			break;
		case 2:
			printf("请输入新性别：");
			scanf("%s", ps->data[pos].sex);
			break;
		case 3:
			printf("请输入新年龄：");
			scanf("%d", &(ps->data[pos].age));
			break;
		case 4:
			printf("请输入新地址：");
			scanf("%s", ps->data[pos].addr);
			break;
		case 5:
			printf("请输入新电话：");
			scanf("%s", ps->data[pos].tele);
			break;
		default:
			printf("输入无效。\n");
			break;

		}
		printf("修改成功！\n");

	}
}
void sortList(struct ContactList* ps)
{
	if (ps->size <= 1)
	{
		printf("不可排序！\n");

	}
	else
	{
		int rule;
		printf("请输入排序规则（均为升序）：\n1.姓名	2.性别	3.年龄	4.地址	5.电话\n");
		scanf("%d", &rule);
		switch (rule)
		{
		case 1:
			char tempName[MAX_NAME];
			for (int i = 0; i < ps->size - 1; i++)
			{
				for (int j = 0; j < ps->size - 1 - i; j++)
				{
					if (strcmp(ps->data[i].name, ps->data[i + 1].name) > 0)
					{
						strcpy(tempName, ps->data[i].name);
						strcpy(ps->data[i].name, ps->data[i + 1].name);
						strcpy(ps->data[i + 1].name, tempName);
					}
				}
			}
			break;
		/*case 2:
			printf("请输入新性别：");
			scanf("%s", ps->data[pos].sex);
			break;
		case 3:
			printf("请输入新年龄：");
			scanf("%d", &(ps->data[pos].age));
			break;
		case 4:
			printf("请输入新地址：");
			scanf("%s", ps->data[pos].addr);
			break;
		case 5:
			printf("请输入新电话：");
			scanf("%s", ps->data[pos].tele);
			break;
		default:
			printf("输入无效。\n");
			break;*/

		}
		printf("排序成功！\n");

	}
}