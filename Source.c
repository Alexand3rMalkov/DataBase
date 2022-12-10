#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>   // ��� ������� �����/������
#include <malloc.h>  // ���������� ��� ������������� ������� ��������� ������
#include <windows.h> // ��� ������� ����� �������
#include <string.h>  // ��� ������ �� ��������

typedef struct {
	int data[3]; // ���, �����, ����
	int timeH;   // ����
	int timeMin; // ������
	char adress[50]; // ����� ��������
	char failures[150]; // �������� �������
	char status[50]; // ��������� ������
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
	user_data* point = NULL; // ���������� ��
	int size, number, n, action;
	char filename[120], adress[50], status[50]; // ������� ��� �������� �������� �����, ������ ��������, ��������� ������

	printf("���� ������ - ����������� ��������� ��������-����������\n");

	while (1) {
		printf("\t����\n");
		printf("\n�������� ��������:\n");
		printf("1) ���� ������.....\n");
		printf("2) ������ ������ �� �����.....\n");
		printf("3) ����� ������ �� �����.....\n");
		printf("4) ����� ������.....\n");
		printf("5) ���������� ������.....\n");
		printf("6) ������ � ����.....\n");
		printf("7) �������� � ����.....\n");
		printf("8) ����� �� ���������.....\n");


		scanf("%d", &action);

		switch (action) {
		case 0:
			return -1; // ����� �� ���������
		case 1:
			system("cls"); // ������� �������
			printf("������� ���-�� �������: ");
			scanf("%d", &size); // ����
			point = (user_data*)malloc(size * sizeof(user_data)); // ��������� ������
			n = 0;
			init(point, size, n);
			break;
		case 2:
			system("cls");
			printf("������� ��� �����, ������� ���������� ���������: ");
			scanf("%s", &filename);
			readfile(filename);
			break;
		case 3:
			if (point == NULL) {   // ����������� ������� ��
				printf("���� ������ �� �������.\n");
				break;
			}
			put(point, size);
			break;
		case 4:
			system("cls");
			if (point == NULL) {
				printf("���� ������ �� �������.\n");
				break;
			}
			else {
				printf("������������ �� ������.\n");
				printf("***************************************************************\n");
			}
			break;

			printf("������� ������ � ��������� ������: ");
			scanf("%s%s", &adress, &status);

			printf("***************************************************************\n");

			int k = find(point, adress, status, size);
			if (k > 0)
				printf("���� ���������: %d.%d.%d;\n", point[k].data[1], point[k].data[2], point[k].data[3]);
			printf("����� ���������: %d:%d;\n", point[k].timeH, point[k].timeMin);
			printf("�����: %s;\n", point[k].adress);
			printf("�������� �������������: %s;\n", point[k].failures);
			printf("��������� ������: %s\n", point[k].status);

		case 5:
			if (point == NULL) {
				printf("���� ������ �� �������\n");
				break;
			}
			sortdata(point, size);
			break;
		case 6:
			system("cls");
			if (point == NULL) {
				printf("���� ������ �� �������\n");
				break;
			}
			printf("������� ��� ����� ��� ������: ");
			scanf("%s", &filename);
			writefile(point, filename, size);
			break;
		case 7:
			if (point == NULL) {
				printf("���� ������ �� �������\n");
				break;
			}
			printf("������� ���-�� �������������, ������� ���������� ��������: ");
			scanf("%d", &number);
			n = size;
			size += number;
			point = (user_data*)realloc(point, size * sizeof(user_data)); //����������������� ������
		}
		printf("***************************************************************\n");

		printf("�������� ������������\n");
		printf("...� ����\n");
		printf("...� ��");
		scanf("%d", &action);

		printf("***************************************************************\n");
		if (action == 1) {
			printf("������� ��� ����� ��� ���������� ��������:");
			scanf("%s", &filename);
			add(point, filename, size, n);
		}
		else if (action == 2) {
			init(point, size, n);
		}
		break;
		printf("��������� ����������.\n");
	}
	printf("***************************************************************\n");
}

//������� ��� ���������� ��
void init(user_data* point, int size, int n) {
	for (int i = n; i < size; i++) {
		printf("***************************************************************\n");
		printf("������� ���� ���������: ");
		scanf("%d.%d.%d", &point[i].data[0], &point[i].data[1], &point[i].data[2]);
		printf("������� ����� ���������: ");
		scanf("%d:%d", &point[i].timeH, &point[i].timeMin);
		printf("������� ����� ��������: ");
		scanf("%s", &point[i].adress);
		printf("������� �������� �������: ");
		scanf("%s", &point[i].failures);
		printf("������� ��������� ������: ");
		scanf("%s", &point[i].status);
		printf("***************************************************************\n");
	}
	return point;
}
// ������� ������
void put(user_data* point, int size) {
	for (int i = 0; i < size; i++) {
		printf("%d.%d.%d", point[i].data[0], point[i].data[1], point[i].data[2]); //���� ���������
		printf("%d:%d", point[i].timeH, point[i].timeMin);		   //����� ���������
		printf("%s", point[i].adress); //����� ��������
		printf("%s", point[i].failures); //�������� �������
		printf("%s", point[i].status); //������ ������
	}
	printf("\n");
}

//������� ������ �� �����
int readfile(char* filename) {
	FILE* fp; // ��������� ����������
	char file[120]; // ������ ��� �������� ������ �� �����
	fp = fopen(filename, "r");
	if (fp != NULL) {
		printf("���� ������� ������.");
		while (!feof(fp)) {
			fgets(file, 120, fp);
			if (!feof(fp)) {
				puts(file);
			}
		}
		return 1;
	}
	else {
		printf("\n������� ���� �� �������.\n");
		return -1;
	}
	fclose(fp); // �������� �����
}

int find(user_data* point, char* adress, char* status, int size) {

}

void sortdata(user_data* point, int size) {

}

// ������� ������ � ����
void writefile(user_data* point, char* filename, int size) {
	FILE* fp;
	if ((fp = fopen(filename, "wt")) == NULL) { //��������� ����������� ������� ����
		printf("���������� ������� ���� ��� ������. \n");
		printf("***************************************************************\n");
	}
	else {
		printf("���� ������� ������.\n");
		for (int i = 0; i < size; i++) {
			printf("\n%d\n", i + 1);
			printf("%d.%d.%d", point[i].data[0], point[i].data[1], point[i].data[2]); //���� ���������
			printf("%d:%d", point[i].timeH, point[i].timeMin); //����� ���������
			printf("%s", point[i].adress); //����� ��������
			printf("%s", point[i].failures); //�������� �������
			printf("%s", point[i].status); //������ ������
	}
		fclose(fp); //
		printf("\n ������ �������� � ����.\n");
		printf("***************************************************************\n");
	}
}

//������� ���������� ������ � ����� ��������
int add(user_data* point, char* filename, int size, int number) { 
	FILE* fp;
	if ((fp = fopen(filename, "a")) == NULL) { //�������� �� ����������� ������� ���� ��� ���������� ������ � ����� ������������
		fprintf(stderr, "���������� ������� ���� ��� ������.\n");
		return -1;
	}
	else {
		init(point, size, number);
		for (int i = number; i < size; i++) {
			//...���������� ������ �� �� � ����...
			fprintf("\n%d\n", i + 1);
			fprintf("%d.%d.%d", point[i].data[0], point[i].data[1], point[i].data[2]); //���� ���������
			fprintf("%d:%d", point[i].timeH, point[i].timeMin);		   //����� ���������
			fprintf("%s", point[i].adress); //����� ��������
			fprintf("%s", point[i].failures); //�������� �������
			fprintf("%s", point[i].status); //������ ������
		}

	}
	fclose(fp);
	return 1;
}