#include "Header.h"
int main()
{
	setlocale(LC_ALL, "Rus");
	system("chcp 1251 > nul");
	struct List* list = init_list();
	struct List* find_list = init_list();
	struct Note* note;
	char* select = (char*)malloc(10 * sizeof(char));
	char adr[100];
	int status = 0;
	int id = 0;
	while (1)
	{
		printf("\nМеню\n");
		printf("1 - Добавить запись\n");
		printf("2 - Поиск по адресу\n");
		printf("3 - Поиск по статусу\n");
		printf("4 - Поиcк по статусу и адресу\n");
		printf("5 - Печать в консоль\n");
		printf("6 - Изменить данные по номеру элемента\n");
		printf("7 - Чтение из файла\n");
		printf("8 - Запись в файл с перезаписью\n");
		printf("9 - Запись в файл с дозаписью в конец\n");
		printf("a - Сортировка по адресу\n");
		printf("b - Сортировка по статусу\n");
		printf("c - Сортировка по дате\n");
		printf("d - Сортировка по комментарию\n");
		scanf("%s", select);
		switch (select[0])
		{
		case '1':
			//TODO
		case '2':
			printf("\nАдрес: ");
			scanf("%s", adr);
			find_list = find_adr(list, adr);
			print(find_list);
			break;
		case '3':
			printf("\nСтатус: ");
			scanf("%d", &status);
			find_list = find_status(list, status);
			print(find_list);
			break;
		case '4':
			printf("\nСтатус: ");
			scanf("%d", &status);
			printf("\nАдрес: ");
			scanf("%s", adr);
			find_list = find_status_adr(list, status, adr);
			print(find_list);
			break;
		case '5':
			print(list);
			break;
		// TODO
		
		}
	}
}
