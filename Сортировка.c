#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <Windows.h>
#define ull unsigned long long
#pragma intrinsic(__rdtsc)

struct list
{
	int data;
	struct list* next;
};

struct list* insert(struct list* head, ull data)
{
	struct list* tmp = malloc(sizeof(struct list)), * list = head;
	tmp->data = data;
	tmp->next = NULL;
	if (head == NULL) return tmp;
	else
	{
		while (list->next != NULL) list = list->next;
		list->next = tmp;
	}
	return head;
}

void reinsert(struct list* head, ull data[], ull n)
{
	struct list* renew = head;
	for (int i = 0; i < n; i++)
	{
		renew->data = data[i];
		renew = renew->next;
	}
}

struct list* sort(struct list* head)
{
	struct list* new_head = NULL;

	while (head != NULL)
	{
		struct list* node = head;
		head = head->next;

		if (new_head == NULL || node->data < new_head->data)
		{
			node->next = new_head;
			new_head = node;
		}
		else
		{
			struct list* current = new_head;
			while (current->next != NULL && !(node->data < current->next->data))
				current = current->next;

			node->next = current->next;
			current->next = node;
		}
	}

	return new_head;
}

void massort(ull n, ull mass[])
{
	int newElement, location;

	for (int i = 1; i < n; i++)
	{
		newElement = mass[i];
		location = i - 1;
		while (location >= 0 && mass[location] > newElement)
		{
			mass[location + 1] = mass[location];
			location--;
		}
		mass[location + 1] = newElement;
	}
}

void rewrite(ull mas[], ull random[], ull n)
{
	for (ull i = 0; i < n; i++) mas[i] = random[i];
}

struct list* del(struct list* head)
{
	struct list* fordel = NULL;
	while (head)
	{
		fordel = head;
		head = head->next;
		free(fordel);
	}
	return head;
}

typedef struct _var
{
	int v, n;
} var;

var* cnt_moda(unsigned __int64* f, unsigned __int64* l, var* v)
{
	var* p, * n;
	for (n = v; f != l; ++f)
	{
		for (p = v; (p != n) && (p->v != *f); ++p);
		p->v = *f;
		p->n++;
		if (p >= n)
			++n;
	}
	return v + (n - v);
}

int max_moda(const var* f, const var* l)
{
	int m = f->n;
	while (f != l)
	{
		if (f->n > m)
			m = f->n;
		++f;
	}
	return m;
}

int main()
{
	setlocale(LC_ALL, "Rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	while (1)
	{
		ull/** mas, * sorted,*/ N;
		/*struct list* head = NULL;
		unsigned __int64 start = 0, end = 0, clock = 0, modalist[40], modamas[40];*/

		while (1)
		{
			printf("Количество чисел - ");
			scanf("%llu", &N);
			if (N == 0)
			{
				printf("Adios, amigos!\n");
				exit(0);
			}
			if (N > 1)
				break;
			else
				printf("???\n");
		}
		float averlist = 0, avermas = 0;
		for (int k = 0; k < 20; k++)
		{
			ull* mas, * sorted;
			mas = (ull*)malloc(N * sizeof(ull));
			struct list* head = NULL;
			unsigned __int64 start = 0, end = 0, clock = 0, modalist[40], modamas[40];

			srand(time(NULL));
			for (ull i = 0; i < N; i++) mas[i] = rand();
			for (ull i = 0; i < N; i++) head = insert(head, mas[i]);

			for (int i = 0; i < 40; i++)
			{
				start = __rdtsc();
				head = sort(head);
				end = __rdtsc();
				reinsert(head, mas, N);
				modalist[i] = end - start;
			}

			sorted = (ull*)malloc(N * sizeof(ull));
			for (ull i = 0; i < N; i++) sorted[i] = mas[i];

			clock = 0;
			for (int i = 0; i < 40; i++)
			{
				start = __rdtsc();
				massort(N, sorted);
				end = __rdtsc();
				rewrite(sorted, mas, N);
				modamas[i] = end - start;
			}

			int cnt, j = 0;
			float aver = 0;
			var vslist[40] = { 0 }, vsmas[40] = { 0 };
			var* it, * endmoda;

			endmoda = cnt_moda(modalist, modalist + sizeof(modalist) / sizeof(modalist[0]), vslist);
			cnt = max_moda(vslist, endmoda);

			for (it = vslist; it != endmoda; ++it)
			{
				if (it->n == cnt)
				{
					aver += it->v;
					j++;
				}
			}
			aver /= j;
			//printf("Время работы списка %.0f\n", aver);
			averlist += aver;

			cnt = 0; j = 0; aver = 0;

			endmoda = cnt_moda(modamas, modamas + sizeof(modamas) / sizeof(modamas[0]), vsmas);
			cnt = max_moda(vsmas, endmoda);

			for (it = vsmas; it != endmoda; ++it)
			{
				if (it->n == cnt)
				{
					aver += it->v;
					j++;
				}
			}
			aver /= j;
			//printf("Время работы массива %.0f\n", aver);
			avermas += aver;

			free(mas);
			free(sorted);
			del(head);
			/*system("pause");
			system("cls");*/
		}
		printf("%.0f %.0f\n", averlist / 20, avermas / 20);
		system("pause");
		system("cls");
	}

	return 0;
}