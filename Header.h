#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <malloc.h>	// для выделения памяти
#include <stdio.h>	// для ввода/вывода информации в консоль
#include <conio.h>	// для работы с файлом
#include <stdlib.h>
#include <locale.h>	// для подключения русского языка в консоли
#include <wchar.h>	// для подключения русского ввода из консоли

struct Data {
	int day;
	int month;
	int year;
};

struct Time
{
	int hour;
	int min;
};

struct Note
{
	struct Data data;
	struct Time time;
	char adr[100];
	char comment[100];
	int status;
	struct Note* next;
	struct Note* prev;
};

struct List
{
	struct Note* first;
	struct Note* end;
	int count;
};

struct Note* init_note();
struct List* init_list();

struct Note* input();
void print(struct List* list);

struct List* find_adr(struct List* list, char* adr);
struct List* find_status(struct List* list, int status);
struct List* find_status_adr(struct List* list, int status, char* adr);

int to_sec(struct Note* p);
