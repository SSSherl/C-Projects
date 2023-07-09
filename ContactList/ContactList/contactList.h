#pragma once
#include <string.h>
#include<stdio.h>
#define MAX 1000
#define MAX_NAME 20
#define MAX_SEX 6
#define MAX_TELE 12
#define MAX_ADDR 30
enum Option
{
	EXIT,
	ADD,
	DEL,
	SEARCH,
	MODIFY,
	SHOW,
	SORT
};
struct PeoInf
{
	char name[MAX_NAME];
	int age;
	char sex[MAX_SEX];
	char tele[MAX_TELE];
	char addr[MAX_ADDR];
};
struct ContactList
{
	struct PeoInf data[MAX];//存放单位信息
	int size;
};

//声明函数
void initList(struct ContactList* ps);
void addList(struct ContactList* ps);
void showList(const struct ContactList* ps);
void delList(struct ContactList* ps);
void searList(const struct ContactList* ps);
void modList(struct ContactList* ps);
void sortList(struct ContactList* ps);