#define _CRT_SECURE_NO_WARNINGS
#include "contactList.h"
//�����ܴ�ʵ��
//���1000�����ѵ���Ϣ
//�������֡��绰���Ա�סַ������
/*���ܣ����Ӻ�����Ϣ
	   ɾ��������Ϣ
	   ���Һ�����Ϣ
	   �޸ĺ�����Ϣ
	   ��ӡ������Ϣ
	   ����
	   */
void initList(struct ContactList* ps)
{
	memset(ps->data, 0, sizeof(ps->data));
	ps->size = 0;//����ͨѶ¼���Ϊ0����Ϣ
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
		printf("ͨѶ¼������");
	}
	else
	{
		printf("���������֣�");
		scanf("%s", ps->data[ps->size].name);
		printf("���������䣺");
		scanf("%d", &(ps->data[ps->size].age));
		printf("�������Ա�");
		scanf("%s", ps->data[ps->size].sex);
		printf("�������ַ��");
		scanf("%s", ps->data[ps->size].addr);
		printf("������绰��");
		scanf("%s", ps->data[ps->size].tele);
		ps->size++;
		printf("��ӳɹ���\n");
	}
}
void showList(const struct ContactList* ps)
{
	if (ps->size == 0)
	{
		printf("ͨѶ¼Ϊ�ա�\n");

	}
	else
	{
		printf("%-10s\t%-4s\t%-5s\t%-12s\t%-20s\n", "����", "����", "�Ա�", "�绰", "��ַ");
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
		printf("ͨѶ¼Ϊ�գ�\n");

	}
	else
	{

		char delName[MAX_NAME];
		printf("������Ҫɾ������ϵ��������");
		scanf("%s", delName);
		int pos = findName(delName, ps);
		if (pos == -1)
		{
			printf("�޸���ϵ�ˡ�\n");
		}
		else
		{
			for (int j = pos; j < ps->size - 1; j++)
			{
				ps->data[j] = ps->data[j + 1];
			}
			ps->size--;
			printf("ɾ���ɹ���\n");
		}
	}
}
void searList(const struct ContactList* ps)
{
	if (ps->size == 0)
	{
		printf("ͨѶ¼Ϊ�գ�\n");

	}
	else
	{
		char searName[MAX_NAME];
		printf("������Ҫ���ҵ���ϵ��������");
		scanf("%s", searName);
		int pos = findName(searName, ps);
		if (pos == -1)
		{
			printf("�޸���ϵ�ˡ�\n");
		}
		else
		{
			printf("%-10s\t%-4s\t%-5s\t%-12s\t%-20s\n", "����", "����", "�Ա�", "�绰", "��ַ");
			printf("%-10s\t%-4d\t%-5s\t%-12s\t%-20s\n", ps->data[pos].name, ps->data[pos].age, ps->data[pos].sex, ps->data[pos].tele, ps->data[pos].addr);
		}
	}
}
void modList(struct ContactList* ps)
{
	if (ps->size == 0)
	{
		printf("ͨѶ¼Ϊ�գ�\n");

	}
	else
	{
		char modName[MAX_NAME];
		printf("������Ҫ�޸ĵ���ϵ��������");
		scanf("%s", modName);
		int pos = findName(modName, ps);
		if (pos == -1)
		{
			printf("�޸���ϵ�ˡ�\n");
		}
		int p;
		printf("������Ҫ�޸ĵ���Ŀ��\n1.����	2.�Ա�	3.����	4.��ַ	5.�绰\n");
		scanf("%d", &p);
		switch (p)
		{
		case 1:
			printf("�����������֣�");
			scanf("%s", ps->data[pos].name);
			break;
		case 2:
			printf("���������Ա�");
			scanf("%s", ps->data[pos].sex);
			break;
		case 3:
			printf("�����������䣺");
			scanf("%d", &(ps->data[pos].age));
			break;
		case 4:
			printf("�������µ�ַ��");
			scanf("%s", ps->data[pos].addr);
			break;
		case 5:
			printf("�������µ绰��");
			scanf("%s", ps->data[pos].tele);
			break;
		default:
			printf("������Ч��\n");
			break;

		}
		printf("�޸ĳɹ���\n");

	}
}
void sortList(struct ContactList* ps)
{
	if (ps->size <= 1)
	{
		printf("��������\n");

	}
	else
	{
		int rule;
		printf("������������򣨾�Ϊ���򣩣�\n1.����	2.�Ա�	3.����	4.��ַ	5.�绰\n");
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
			printf("���������Ա�");
			scanf("%s", ps->data[pos].sex);
			break;
		case 3:
			printf("�����������䣺");
			scanf("%d", &(ps->data[pos].age));
			break;
		case 4:
			printf("�������µ�ַ��");
			scanf("%s", ps->data[pos].addr);
			break;
		case 5:
			printf("�������µ绰��");
			scanf("%s", ps->data[pos].tele);
			break;
		default:
			printf("������Ч��\n");
			break;*/

		}
		printf("����ɹ���\n");

	}
}