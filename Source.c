#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>   // для функции ввода/вывода
#include <malloc.h>  // библиотека для использования функции выделения памяти
#include <windows.h> // для задания языка консоли
#include <string.h>  // для работы со строками

typedef struct {
	int data[3]; // год, месяц, день
	int timeH;   // часы
	int timeMin; // минуты
	char adress[50]; // адрес абонента
	char failures[150]; // характер поломки
	char status[50]; // состояние заявки
}user_data;

void init(user_data* point, int size, int n);
void put(user_data* point, int size);
int readfile(char* filename);
int find(user_data* point, char* adress, char* status, int size);
void sortdata(user_data* point, int size);
void writefile(user_data* point, char* filename, int size);
int add(user_data* point, char* filename, int size, int number);

int main() {
	system("chcp 1251");
	user_data* point = NULL; // объявление БД
	int size, number, n, action;
	char filename[120], adress[50], status[50]; // массивы для хранения названия файла, адреса абонента, состояния заявки

	printf("База данных - Техническая поддержка интернет-провайдера\n");

	while (1) {
		printf("\tМеню\n");
		printf("\nВыберите действие:\n");
		printf("1) Ввод данных.....\n");
		printf("2) Чтение данных из файла.....\n");
		printf("3) Вывод данных на экран.....\n");
		printf("4) Поиск данных.....\n");
		printf("5) Сортировка данных.....\n");
		printf("6) Запись в файл.....\n");
		printf("7) Дозапись в файл.....\n");
		printf("8) Выход из программы.....\n");


		scanf("%d", &action);

		switch (action) {
		case 0:
			return -1; // выход из программы
		case 1:
			system("cls"); // очистка консоли
			printf("Введите кол-во записей: ");
			scanf("%d", &size); // ввод
			point = (user_data*)malloc(size * sizeof(user_data)); // выделение памяти
			n = 0;
			init(point, size, n);
			break;
		case 2:
			system("cls");
			printf("Введите имя файла, который необходимо прочитать: ");
			scanf("%s", &filename);
			readfile(filename);
			break;
		case 3:
			if (point == NULL) {   // проверяется наличие БД
				printf("База данных не найдена.\n");
				break;
			}
			put(point, size);
			break;
		case 4:
			system("cls");
			if (point == NULL) {
				printf("База данных не найдена.\n");
				break;
			}
			else {
				printf("Пользователь не найден.\n");
				printf("***************************************************************\n");
			}
			break;

			printf("Укажите адреса и состояние заявки: ");
			scanf("%s%s", &adress, &status);

			printf("***************************************************************\n");

			int k = find(point, adress, status, size);
			if (k > 0)
				printf("Дата обращения: %d.%d.%d;\n", point[k].data[1], point[k].data[2], point[k].data[3]);
			printf("Время обращения: %d:%d;\n", point[k].timeH, point[k].timeMin);
			printf("Адрес: %s;\n", point[k].adress);
			printf("Характер неисправности: %s;\n", point[k].failures);
			printf("Состояние заявки: %s\n", point[k].status);

		case 5:
			if (point == NULL) {
				printf("База данных не найдена\n");
				break;
			}
			sortdata(point, size);
			break;
		case 6:
			system("cls");
			if (point == NULL) {
				printf("База данных не найдена\n");
				break;
			}
			printf("Введите имя файла для записи: ");
			scanf("%s", &filename);
			writefile(point, filename, size);
			break;
		case 7:
			if (point == NULL) {
				printf("База данных не найдена\n");
				break;
			}
			printf("Введите кол-во пользователей, которых необходимо добавить: ");
			scanf("%d", &number);
			n = size;
			size += number;
			point = (user_data*)realloc(point, size * sizeof(user_data)); //перераспределение памяти
		}
		printf("***************************************************************\n");

		printf("Добавить пользователя\n");
		printf("...в файл\n");
		printf("...в БД");
		scanf("%d", &action);

		printf("***************************************************************\n");
		if (action == 1) {
			printf("Введите имя файла для добавления абонента:");
			scanf("%s", &filename);
			add(point, filename, size, n);
		}
		else if (action == 2) {
			init(point, size, n);
		}
		break;
		printf("Выполнить невозможно.\n");
	}
	printf("***************************************************************\n");
}

//функция для заполнения БД
void init(user_data* point, int size, int n) {
	for (int i = n; i < size; i++) {
		printf("***************************************************************\n");
		printf("Введите дату обращения: ");
		scanf("%d.%d.%d", &point[i].data[0], &point[i].data[1], &point[i].data[2]);
		printf("Введите время обращения: ");
		scanf("%d:%d", &point[i].timeH, &point[i].timeMin);
		printf("Введите адрес абонента: ");
		scanf("%s", &point[i].adress);
		printf("введите характер поломки: ");
		scanf("%s", &point[i].failures);
		printf("Введите состояние заявки: ");
		scanf("%s", &point[i].status);
		printf("***************************************************************\n");
	}
	return point;
}
// функция печати
void put(user_data* point, int size) {
	for (int i = 0; i < size; i++) {
		printf("%d.%d.%d", point[i].data[0], point[i].data[1], point[i].data[2]); //дата обращения
		printf("%d:%d", point[i].timeH, point[i].timeMin);		   //время обращения
		printf("%s", point[i].adress); //адрес абонента
		printf("%s", point[i].failures); //характер поломки
		printf("%s", point[i].status); //статус заявки
	}
	printf("\n");
}

//функция чтения из файла
int readfile(char* filename) {
	FILE* fp; // объявляем переменную
	char file[120]; // массив для хранения строки из файла
	fp = fopen(filename, "r");
	if (fp != NULL) {
		printf("Файл успешно открыт.");
		while (!feof(fp)) {
			fgets(file, 120, fp);
			if (!feof(fp)) {
				puts(file);
			}
		}
		return 1;
	}
	else {
		printf("\nОткрыть файл не удалось.\n");
		return -1;
	}
	fclose(fp); // закрытие файла
}

int find(user_data* point, char* adress, char* status, int size) {

}

void sortdata(user_data* point, int size) {

}

// функция записи в файл
void writefile(user_data* point, char* filename, int size) {
	FILE* fp;
	if ((fp = fopen(filename, "wt")) == NULL) { //проверяем возможность открыть файл
		printf("Невозможно открыть файл для записи. \n");
		printf("***************************************************************\n");
	}
	else {
		printf("Файл успешно открыт.\n");
		for (int i = 0; i < size; i++) {
			printf("\n%d\n", i + 1);
			printf("%d.%d.%d", point[i].data[0], point[i].data[1], point[i].data[2]); //дата обращения
			printf("%d:%d", point[i].timeH, point[i].timeMin); //время обращения
			printf("%s", point[i].adress); //адрес абонента
			printf("%s", point[i].failures); //характер поломки
			printf("%s", point[i].status); //статус заявки
	}
		fclose(fp); //
		printf("\n Данные записаны в файл.\n");
		printf("***************************************************************\n");
	}
}

//функция добавления данных о новом абоненте
int add(user_data* point, char* filename, int size, int number) { 
	FILE* fp;
	if ((fp = fopen(filename, "a")) == NULL) { //проверка на возможность открыть файл для добавления данных о новом пользователе
		fprintf(stderr, "Невозможно открыть файл для записи.\n");
		return -1;
	}
	else {
		init(point, size, number);
		for (int i = number; i < size; i++) {
			//...добавление данных из БД в файл...
			fprintf("\n%d\n", i + 1);
			fprintf("%d.%d.%d", point[i].data[0], point[i].data[1], point[i].data[2]); //дата обращения
			fprintf("%d:%d", point[i].timeH, point[i].timeMin);		   //время обращения
			fprintf("%s", point[i].adress); //адрес абонента
			fprintf("%s", point[i].failures); //характер поломки
			fprintf("%s", point[i].status); //статус заявки
		}

	}
	fclose(fp);
	return 1;
}