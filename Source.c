#include "Header.h"

struct Note* init_note()
{
	struct Note* item = (struct Note*)malloc(sizeof(struct Note));
	item->status = 0;
	item->next = NULL;
	item->prev = NULL;
	return item;
}

int to_sec(struct Note* p)
{
	int sec = p->time.min + p->time.hour * 60;
	sec = sec + p->data.day * 24 * 60 + p->data.month * 30 * 24 * 60 + p->data.year * 365 * 24 * 60;
	return sec;
}

struct Note* input()
{
	struct Note* p = (struct Note*)malloc(sizeof(struct Note));
	printf("Введите дату:");
	int test = 1;
	if (test == 1)
	{
		p->data.month = rand() % 12;
		p->data.day = rand() % 30;
		p->data.year = rand() % 23 + 2000;
		p->time.hour = rand() % 24;
		p->time.min = rand() % 60;
		p->status = rand() % 3 + 1;
		p->adr[0] = 'A' + rand() % 20;
		p->adr[1] = '\0';
		p->comment[0] = 'A' + rand() % 20;
		p->comment[1] = '\0';
	}
	else
	{
		p->data.month = input_int(0, 11, "Месяц");
		if (p->data.month == -1)
			return NULL;

		p->data.day = input_int(0, 30, "День");
		if (p->data.day == -1)
			return NULL;

		p->data.year = input_int(2000, 2023, "Год");
		if (p->data.year == -1)
			return NULL;

		p->time.hour = input_int(0, 23, "Час");
		if (p->time.hour == -1)
			return NULL;

		p->time.min = input_int(0, 59, "Минуты");
		if (p->time.min == -1)
			return NULL;


		p->status = input_int(1, 3, "Статус (1 - успешно, 2 - в работе, 3 - ошибка)");
		if (p->status == -1)
			return NULL;

  //TODO
  }
}
