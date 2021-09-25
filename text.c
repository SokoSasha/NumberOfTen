#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<math.h>
#include <Windows.h>
#define ull unsigned long long

unsigned long long m = 4294967296; //2^32
unsigned long long a = 42949677;
unsigned long long c = 123;

ull lkg(ull x) // Расчет следующего псевдослучайного числа
{
	x = (a * x + c) % m;
	return x;
}

ull power() // Мощность
{
	ull b = a - 1, s = 2;
	while (1)
	{
		b *= (a - 1);
		if (b % m == 0) return s;
		s++;
	}
}

ull period() // Период
{
	ull x = 1;
	ull i = 0;
	while (1)
	{
		i++;
		x = lkg(x);
		if (x == 1)
			return i;
		if (x == lkg(x))
		{
			printf("Зацикливается на %llu\n", x);
			return 1;
		}
	}
}

#define number 1000000 // должно быть кратно 16

long double Vn(ull x) // Формула Хи^2
{
	long double y = x;
	y = pow(y - (number / 16), 2) / (number / 16);
	return y;
}

void chi() // Рассчеты Хи^2
{
	ull pr[17] = { 0 }, x, j, b[2] = { 0 };

	for (int i = 0; i <= 16; i++)
		pr[i] = i * (m / 16);

	for (int i = 0; i < 100; i++)
	{
		ull y[16] = { 0 };
		x = rand();
		j = 0;
		while (j < number)
		{
			x = lkg(x);
			for (int k = 0; k < 16; k++)
			{
				if (x >= pr[k] && x < pr[k + 1])
				{
					y[k]++;
					break;
				}
			}
			j++;
		}

		long double Vall = 0;

		for (int f = 0; f < 16; f++)
			Vall += Vn(y[f]);

		if (Vall >= 7.261 && Vall < 25) b[1]++;
		else b[0]++;
	}

	printf("Удовлетворительных результатов : %llu/100\n", b[1]);
	printf("Неудовлетворительных результатов : %llu/100\n", b[0]);

}

#define q 30 //НЕ менять, т.к. привязано к таблице
#define t 40

void b_sort(long double num[]) // Сортировка пузырьком
{
	for (int i = 0; i < q - 1; i++)
	{
		for (int j = q - 1; j > i; j--)
		{
			if (num[j - 1] > num[j])
			{
				long double temp = num[j - 1];
				num[j - 1] = num[j];
				num[j] = temp;
			}
		}
	}
}

void max_t() // Критерий "максимум-t"
{
	ull pl = 0, min = 0;
	for (int l = 0; l < 100; l++)
	{

		long double  y[q * t], max[q] = { 0 }, m_ = m, x;

		x = rand();

		for (int i = 0; i < q * t; i++)
		{
			x = lkg(x);
			y[i] = x / m_;
		}


		for (int i = 0; i < q; i++)
		{
			for (int g = 0; g < t; g++)
			{
				if (y[t * i + g] >= max[i])
					max[i] = y[t * i + g];
			};
		}

		b_sort(max);

		long double Kplus = 0, Kminus = 0;

		for (int i = 1; i <= q; i++)
		{
			long double y = i;
			long double plus = sqrt(q) * ((y / q) - pow(max[i - 1], t));
			long double minus = sqrt(q) * (pow(max[i - 1], t) - ((y - 1) / q));
			if (plus >= Kplus && plus >= 0)
				Kplus = plus;
			if (minus >= Kminus && minus >= 0)
				Kminus = minus;
		}

		long double rez;
		if (Kplus > Kminus) rez = Kplus;
		else rez = Kminus;

		if (rez >= 0.1351 && rez < 1.4801) pl++;
		else min++;
	}

	printf("Удовлетворительных результатов : %llu/100\n", pl);
	printf("Неудовлетворительных результатов : %llu/100\n", min);

}

int mainmenu() // Панелька меню
{
	int w;
	printf("1 : Посмотреть параметры\n"
		"2 : Посчиать период\n"
		"3 : Посчитать разброс\n"
		"4 : Посчитать мощность\n"
		"5 : Критерий \"максимум-t\"\n"
		"0 : Выход из программы\n"
		">");
	scanf("%d", &w);
	system("cls");
	return w;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int menu;
	ull per;
	while (menu = mainmenu())
	{
		switch (menu)
		{
		case 1:
			printf("Параметры:\n"
				"Модуль m - %llu\n"
				"Множитель a - %llu\n"
				"Приращение c - %llu\n\n", m, a, c);
			break;

		case 2:
			per = period();
			if (per != 1)
				printf("Период - %llu\n\n", per);
			break;

		case 3:
			printf("Критерий \"Хи-квадрат\":\n");
			chi();
			printf("\n");
			break;

		case 4:
			printf("Мощность - %llu\n\n", power(a));
			break;

		case 5:
			printf("Критерий \"максимум-t\":\n");
			max_t();
			printf("\n");
			break;

		}
	}

	printf("Пока\n");
	return 0;
}