#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>   // для функции ввода/вывода
#include <malloc.h>  // библиотека для использования функции выделения памяти
#include <windows.h> // для задания языка консоли
#include <string.h>  // для работы со строками
#include <stdlib.h>  // для работы со стандартной библиотекой

typedef struct {
	int data[3]; // день, месяц, год
	int timeH;   // часы
	int timeMin; // минуты
	char adress[50]; // адрес абонента
	char failures[150]; // характер поломки
	char status[50]; // состояние заявки
}user_data;

//список функций
void init(user_data* point, int size, int n);
user_data* read_file(char* filename, int* size);
void put(user_data* point, int size);
void write_file(user_data* point, char* filename, int size);
int add(user_data* point, char* filename, int size, int n);
int searchByAddress(user_data* point, char* address, int size);
int searchByStatus(user_data* point, char* status, int size);
//компараторы для работы сортировок
int dateComparator(const user_data* userA, const user_data* userB);
int timeComparator(const user_data* userA, const user_data* userB);
void sort_(user_data* point, int size, int(*comparator)(const void*, const void*));
//сортировки
void sortByDate(user_data* point, int size);
void sortByTime(user_data* point, int size);

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
		printf("4) Поиск по адресу.....\n");
		printf("5) Поиск по статусу заявки.....\n");
		printf("6) Сортировать по дате.....\n");
		printf("7) Сортировать по времени.....\n");
		printf("8) Запись в файл.....\n");
		printf("9) Дозапись в файл.....\n");
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
			point = read_file(filename, &size);
			printf("Считано %d строк.\n", size);
			put(point, size);
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
			printf("Укажите адрес абонента: ");
			scanf("%s", &adress);
			printf("***************************************************************\n");
			int a = searchByAddress(point, adress, size);
			if (a >= 0) printf("Дата обращения - %d.%d.%d\t Время обращения - %d:%d\t Адрес абонента - %s\t Характер поломки - %s\t Статус заявки - %s");
			else {
				printf("Абонент не найден.\n");
			}
			break;
		case 5:
			system("cls");
			if (point == NULL) {   // проверяется наличие БД
				printf("База данных не найдена.\n");
				break;
			}
			printf("Укажите состояние заявки: ");
			scanf("%s", &status);
			printf("***************************************************************\n");
			int b = searchByStatus(point, status, size);
			if (b >= 0) printf("Дата обращения - %d.%d.%d\t Время обращения - %d:%d\t Адрес абонента - %s\t Характер поломки - %s\t Статус заявки - %s");
			else {
				printf("Абонент не найден.\n");
			}
			break;
		case 6:
			if (point == NULL) {
				printf("База данных не найдена.\n");
				break;
			}
			sortByDate(point, size);
			break;
		case 7:
			if (point == NULL) {
				printf("База данных не найдена.\n");
				break;
			}
			sortByTime(point, size);
			break;
		case 8:
			system("cls");
			if (point == NULL) {
				printf("База данных не найдена\n");
				break;
			}
			printf("Введите имя файла для записи: ");
			scanf("%s", &filename);
			write_file(point, filename, size);
			break;
		case 9:
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
		printf("Введите характер поломки: ");
		scanf("%s", &point[i].failures);
		printf("Введите состояние заявки: ");
		scanf("%s", &point[i].status);
		printf("***************************************************************\n");
	}
	return point;
}

//функция чтения из файла
user_data* read_file(char* filename, int* size) {
	FILE* f; // объявляем переменную
	int number_field = 0;	// номер поля за записи
	int ind = 0;		// номер строки
	user_data* list = (user_data*)malloc(1000 * sizeof(user_data*));
	char file[200]; // массив для хранения строки из файла
	f = fopen(filename, "r");
	if (f != NULL) {
		printf("\nФайл открыт.\n");
		while (!feof(f)) {
			fgets(file, 200, f);
			if (file[0] == '\n')
				continue;
			sscanf(file, "%d.%d.%d %d:%d %s %s %s",
				&list[ind].data[0],
				&list[ind].data[1],
				&list[ind].data[2],
				&list[ind].timeH,
				&list[ind].timeMin,
				list[ind].adress,
				list[ind].failures,
				list[ind].status);
			ind++;
		}
		*size = ind;	// возвращаем число записей
		return list;
	}
	else {
		printf("\nОткрыть файл не удалось.\n");
		return NULL;
	}
	fclose(f); // закрытие файла

	return NULL;
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
			fprintf(f, "%d.%d.%d ", point[i].data[0], point[i].data[1], point[i].data[2]); //дата обращения
			fprintf(f, "%d:%d ", point[i].timeH, point[i].timeMin); //время обращения
			fprintf(f, "%s ", point[i].adress); //адрес абонента
			fprintf(f, "%s ", point[i].failures); //характер поломки
			fprintf(f, "%s", point[i].status); //статус заявки
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

// возвращает индекс первого найденного с начала абонента из массива
// point размером size адрес которого равен address
int searchByAddress(user_data* point, char* address, int size) {
	int number = -1;
	for (int i = 0; i < size; i++) {
		if (strcmp(address, point[i].adress) == 0) { // проверяем строки на соответствие введенным данным
			return i; //возвращаем номер
		}
	}
	return number;
}

// возвращает индекс первого найденного с начала абонента из массива
// point размером size статус которого равен status
int searchByStatus(user_data* point, char* status, int size) {
	int number = -1;
	for (int i = 0; i < size; i++) {
		if (strcmp(status, point[i].status) == 0) { // проверяем строки на соответствие введенным данным
			return i; //возвращаем номер
		}
	}
	return number;
}

// возвращает число > 0 если дата регистрации userA позже userB,
// 0 если даты регистрации равны
// число < 0 если дата регистрации userA раньше userB
int dateComparator(const user_data* userA, const user_data* userB) {
	if (userA->data[0] != userB->data[0])
		return userA->data[0] - userB->data[0];
	if (userA->data[1] != userB->data[1])
		return userA->data[1] - userB->data[1];
	return userA->data[2] - userB->data[2];
}

// возвращает число > 0 если время регистрации userA позже userB,
// 0 если даты регистрации равны
// число < 0 если время регистрации userA раньше userB
int timeComparator(const user_data* userA, const user_data* userB) {
	if (userA->timeH != userB->timeH)
		return userA->timeH - userB->timeH;
	return userA->timeMin - userB->timeMin;
}

// сортирует массив пользователей point размером size в соответствии со сравнивающей
// функцией comparator
void sort_(user_data* point, int size, int(*comparator)(const void*, const void*)) {
	qsort(point, size, sizeof(point[0]), comparator);
}

// сортирует массив пользователей point размером size по дате регистрации
void sortByDate(user_data* point, int size) {
	sort_(point, size, dateComparator);
}

// сортирует массив пользователей point размером size по времени регистрации
void sortByTime(user_data* point, int size) {
	sort_(point, size, timeComparator);
}
