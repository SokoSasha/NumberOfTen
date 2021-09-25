#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <Windows.h>

int max=0;
int fl=0, fl1=0;

enum { female, male } sex;


struct students
{
	char firstName[80];
	char secondName[80];
	enum sex gender;
	union
	{
		char maiden[80];
		int age_army;
	};
	char group[15];
	int age;
	float sr_performance;
	bool status;
};

void Add(struct students* student)
{
	system("cls");
	int count = max;
	printf("Фамилия: ");
	scanf("%s", student[max -1].secondName);
	printf("Имя: ");
	scanf("%s", &student[max -1].firstName);
	printf("Возраст: ");
	scanf("%d", &student[max -1].age);
	while (1)
	{
		printf("Введите пол (0-female | 1-male): ");
		scanf("%d", &student[max - 1].gender);
		if (student[max-1].gender == female)
		{
			printf("Введeте девичью фамилию: ");
			scanf("%s", &student[max -1].maiden);
			break;
		}
		else if (student[max -1].gender == male)
		{
			printf("Введите год призыва в армию: ");
			scanf("%d", &student[max - 1].age_army);
			break;
		}
		else printf("Введeно некорректное значение.\n");
	}
	printf("Номер группы: ");
	scanf("%s", &student[max - 1].group);
	printf("Средняя успеваемость: ");
	scanf("%f", &student[max - 1].sr_performance);
	while (1)
	{
		printf("Введите статус студенда (0- отчислен | 1 - обучается): ");
		scanf("%d", &student[max - 1].status);
		if (student[max - 1].status == true) break;
		else if (student[max - 1].status == false) break;
		else printf("Введeно некорректное значение.\n");
	}
}

void Save(struct students* student)
{
	system("cls");
	FILE* file;
	int c;
	printf("1 : Переписать базу\n2: Добавить элемент(ы)\n>");
	scanf("%d", &c);
	if (c == 1) file = fopen("students.txt", "w");
	else file = fopen("students.txt", "a");
	for (int count =0; count < max; count++)
	{
		fprintf(file, "%s %s %d %d %s %f %d ", student[count].secondName, student[count].firstName, student[count].age, student[count].gender, student[count].group, student[count].sr_performance, student[count].status);
		if (student[count].gender == male) fprintf(file, "%d\n", student[count].age_army);
		else if (student[count].gender == female) fprintf(file, "%s\n", student[count].maiden);
	}
	printf("Сохранено в файл students.txt\n");
	fclose(file);
	system("pause");
}

void Pr(int count, struct students* student)
{
	printf("%d. %s %s\nГруппа: %s\nВозраст: %d\nУспеваемость: %.1f\n", count + 1, student[count].secondName, student[count].firstName, student[count].group, student[count].age, student[count].sr_performance);
	if (student[count].gender == male) printf("Пол: мужской\nГод призыва в армию: %d\n", student[count].age_army);
	else if (student[count].gender == female) printf("Пол: женский\nДевичья фамилия: %s\n", student[count].maiden);
	if (student[count].status == true) printf("Обучается\n\n");
	else if (student[count].status == false) printf("Отчислен\n\n");
}

void Print(struct students* student)
{
	system("cls");
	if (max ==0)
	{
		printf("База пуста. Выводить нечего :(\n");
		system("pause");
	}
	else
	{
		int c, count;
		printf("1 : Один элемент\n2 : Все\n0: Выход\n>");
		scanf("%d", &c);
		if (c ==0) return;
		else if (c == 1)
		{
			while (1)
			{
				printf("Введите номер выводимого элемента:");
				scanf("%d", &count);
				system("cls");
				if (count <=0) printf("Номера элементов начинаются с 1!\n");
				else if (count > max) printf("Такого элемента нет!\nВсего %d элементa(ов)\n", max);
				else break;
			}
			system("cls");
			Pr(count - 1, student);
			system("pause");
		}
		else if (c == 2)
		{
			system("cls");
			for (count =0; count < max; count++) Pr(count, student);
			system("pause");
		}
	}
}

void Del(struct students* student)
{
	system("cls");
	if (max ==0)
	{
		printf("База пуста. Удалять нечего :(\n");
		system("pause");
	}
	else
	{
		int count;
		while (1)
		{
			printf("Введите номер удаляемого элемента:");
			scanf("%d", &count);
			if (count <=0) printf("Номера элементов начинаются с 1!\n");
			else if (count > max) printf("Такого элемента нет!\nВсего %d элементa(ов)\n", max);
			else break;
		}
		count--;
		for (count; count < (max - 1); count++)
			student[count] = student[count + 1];
		max--;
	}
}

int Menu(void)
{
	system("cls");
	int c =0;
	printf("1 : Добавить элемент\n"
		"2 : Сохранить\n"
		"3 : Загрузить из файла\n"
		"4 : Вывод элементов\n"
		"5 : Удалить\n"
		"0: Выход\n"
		">");
	scanf("%d", &c);
	return c;
}

int main()
{
	setlocale(LC_ALL, "Rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	struct students* student = (struct students*)malloc(sizeof(struct students));
	int Selection;
	while ((Selection = Menu()) !=0)
		switch (Selection)
		{
		case 1:
			max++;
			student = (struct students*)realloc(student, sizeof(struct students) * max);
			Add(student);
			break;
		case 2:
			Save(student);
			break;
		case 3:
			if (fl == 1) break;
			FILE* file;
			file = fopen("students.txt", "r");

			while (!feof(file))
			{
				max++;
				student = (struct students*)realloc(student, sizeof(struct students) * max);
				fscanf(file, "%s %s %d %d %s %f %d ", &student[max - 1].secondName, &student[max - 1].firstName, &student[max - 1].age, &student[max - 1].gender, &student[max - 1].group, &student[max - 1].sr_performance, &student[max - 1].status);
				if (student[max - 1].gender == male) fscanf(file, "%d\n", &student[max - 1].age_army);
				else if (student[max - 1].gender == female) fscanf(file, "%s\n", &student[max - 1].maiden);
			}
			fclose(file);
			system("cls");
			printf("Успешно\n");
			system("pause");
			fl = 1;
			break;
		case 4:
			Print(student);
			break;
		case 5:
			Del(student);
			student = (struct students*)realloc(student, sizeof(struct students) * max);
			break;
		}
	free(student);
	return 0;
}