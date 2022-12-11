#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>   // для функции ввода/вывода
#include <malloc.h>  // библиотека для использования функции выделения памяти
#include <windows.h> // для задания языка консоли
#include <string.h>  // для работы со строками
#include <stdlib.h>

typedef struct {
	int data[3]; // год, месяц, день
	int timeH;   // часы
	int timeMin; // минуты
	char adress[50]; // адрес абонента
	char failures[150]; // характер поломки
	char status[50]; // состояние заявки
}user_data;

//список функций
void init(user_data* point, int size, int n);
int read_file(char* filename);
void put(user_data* point, int size);
void write_file(user_data* point, char* filename, int size);
int add(user_data* point, char* filename, int size, int n);
int search(user_data* point, char* adress, char* status, int size);
void sort(user_data* point, int size);

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
		printf("4) Поиск данных.....\n"); //и тут еще не сработало
		printf("5) Сортировка данных.....\n"); // всё еще не сработало
		printf("6) Запись в файл.....\n");
		printf("7) Дозапись в файл.....\n");
		printf("0) Выход из программы.....\n");

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
			printf("Введите имя файла, который необходимо прочитать: ");
			scanf("%s", &filename);
			read_file(filename);
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
			if (point == NULL) {   // проверяется наличие БД
				printf("База данных не найдена.\n");
				break;
			}
			printf("Укажите адрес абонента и состояние заявки: ");
			scanf("%s %s", &adress, &status);
			printf("***************************************************************\n");
			int a = search(point, adress, status, size);
			if (a >= 0) printf("Дата обращения - %d.%d.%d\t Время обращения - %d:%d\t Адрес абонента - %s\t Характер поломки - %s\t Статус заявки - %s");
			else {
				printf("Абонент не найден.\n");
			}
			break;
		case 5:
			if (point == NULL) {
				printf("База данных не найдена.\n");
				break;
			}
			sort(point, size);
			break;
		case 6:
			system("cls");
			if (point == NULL) {
				printf("База данных не найдена\n");
				break;
			}
			printf("Введите имя файла для записи: ");
			scanf("%s", &filename);
			write_file(point, filename, size);
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

			printf("***************************************************************\n");

			printf("Добавить пользователя\n");
			printf("...в файл\n");
			printf("...в БД\n");
			scanf("%d", &action);

			printf("***************************************************************\n");
			if (action == 1) { // добавление в файл
				printf("Введите имя файла для добавления абонента:");
				scanf("%s", &filename);
				add(point, filename, size, n);
			}
			else if (action == 2) { //добавление в базу данных
				init(point, size, n);
			}
			break;
		default:
			printf("Выполнить невозможно.\n");
			printf("***************************************************************\n");
		}
	}
	return 0;
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

//функция чтения из файла
int read_file(char* filename) {
	FILE* f; // объявляем переменную
	char file[200]; // массив для хранения строки из файла
	f = fopen(filename, "r");
	if (f != NULL) {
		printf("\nФайл открыт.\n");
		while (!feof(f)) {
			fgets(file, 200, f);
				puts(file);
		}
		return 1;
	}
	else {
		printf("\nОткрыть файл не удалось.\n");
		return -1;
	}
	fclose(f); // закрытие файла
	return 0;
}

// функция вывода на экран
void put(user_data* point, int size) {
	printf("\tДата обращения\t\tВремя обращения\t\tАдрес абонента\t\tХарактер поломки\t\tСтатус заявки");
	for (int i = 0; i < size; i++) {
		printf("\n\n%d. ", i + 1);
		printf("\n\t%d.%d.%d\t", point[i].data[0], point[i].data[1], point[i].data[2]); //дата обращения
		printf("\t%d:%d\t", point[i].timeH, point[i].timeMin);		   //время обращения
		printf("\t\t%s\t", point[i].adress); //адрес абонента
		printf("\t%s\t", point[i].failures); //характер поломки
		printf("\t%s\t", point[i].status); //статус заявки
		printf("\n");
	}
	printf("\t");
}

// функция записи в файл
void write_file(user_data* point, char* filename, int size) {
	FILE* f;
	if ((f = fopen(filename, "w")) == NULL) { //проверяем возможность открыть файл
		printf("Невозможно открыть файл для записи. \n");
		printf("***************************************************************\n");
		system("pause");
	}
	else {
		printf("Файл успешно открыт.\n");
		for (int i = 0; i < size; i++) {
			fprintf(f, "\n");
			fprintf(f,"%d.%d.%d ", point[i].data[0], point[i].data[1], point[i].data[2]); //дата обращения
			fprintf(f,"%d:%d ", point[i].timeH, point[i].timeMin); //время обращения
			fprintf(f,"%s ", point[i].adress); //адрес абонента
			fprintf(f,"%s ", point[i].failures); //характер поломки
			fprintf(f,"%s", point[i].status); //статус заявки
			system("pause");
		}
		fclose(f); // закрытие файла
		printf("\n Данные записаны в файл.\n");
		printf("***************************************************************\n");
		system("pause");
	}
	return 0;
}

// функция дозаписи
int add(user_data* point, char* filename, int size, int n) {
	FILE* f;
	if ((f = fopen(filename, "a")) == NULL) {
		fprintf(stderr, "Невозможно открыть файл для записи. \n");
		return -1; //выход, если ошибка
	}
	else {
		init(point, size, n);
		for (int i = n; i < size; i++) {
			fprintf(f, "%d)\n", i + 1);
			fprintf(f, "%d.%d.%d ", point[i].data[0], point[i].data[1], point[i].data[2]); //дата обращения
			fprintf(f, "%d:%d ", point[i].timeH, point[i].timeMin); //время обращения
			fprintf(f, "%s ", point[i].adress); //адрес абонента
			fprintf(f, "%s ", point[i].failures); //характер поломки
			fprintf(f, "%s ", point[i].status); //статус заявки
		}
	}
	fclose(f); // закрытие файла
	return 1;
}

// функция поиска абонента
int search(user_data* point, char* adress, char* status, int size) {
	int number = -1;
	for (int i = 0; i < size; i++) {
		if ((strcmp(adress, point[i].adress) == 0) && (strcmp(status, point[i].status) == 0)) { // проверяем строки на соответствие введенным данным
			number = i; //запоминаем номер
		}
	}
	return number;
}

// функция сортировки по времени и дате
void sort(user_data* point, int size) {
	user_data keep;
	//сортировка по дате
	for (int i = 0; i < size; i++) {
		for (int j = i + 1; j < size; i++) {
			if (point[i].data[2] + point[i].data[1] + point[i].data[0] > point[j].data[2] + point[j].data[1] + point[j].data[0]) {
				keep = point[j];
				point[j] = point[i];
				point[i] = keep;
			}
		}
	}
	//сортировка по времени, есди дата совпадает
	for (int i = 0; i < size - 1; i++) {
		if ((point[i].data[2] == point[i + 1].data[2]) && (point[i].data[1] == point[i + 1].data[1]) && (point[i].data[0] == point[i + 1].data[0])) {
			if (point[i].timeH == point[i + 1].timeH) {
				if (point[i].timeMin == point[i + 1].timeMin) {
					keep = point[i + 1];
					point[i + 1] = point[i];
					point[i] = keep;
				}
			}
			else if (point[i].timeH > point[i + 1].timeH) {
				keep = point[i + 1];
				point[i + 1] = point[i];
				point[i] = keep;
			}
		}
	}
	printf("Данные отсортированы.");
	printf("***************************************************************\n");
}
