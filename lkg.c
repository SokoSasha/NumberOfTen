#include <stdio.h>


typedef struct _var {
	int v, n;
} var;


// функция подсчёта повторений
var* cnt_moda(const int* f, const int* l, var* v) {
	var* p, * n;
	for (n = v; f != l; ++f) {
		for (p = v; (p != n) && (p->v != *f); ++p);
		p->v = *f;
		p->n++;
		if (p >= n)
			++n;
	}
	return v + (n - v);
}

// функция возвращает максимум повторений
int max_moda(const var* f, const var* l) {
	int m = f->n;
	while (f != l) {
		if (f->n > m)
			m = f->n;
		++f;
	}
	return m;
}



int main(void)
{
	int mas[] = { 8872, 10044, 7590, 6068, 6086, 5840, 5768, 5738, 5826, 5654, 5376, 5698, 5726, 5630, 5618, 5668, 5444, 5686, 5670, 5434, 5478, 5514, 5442, 5676, 5664, 5592, 5708, 5700, 5660, 5500, 5746, 5416, 5676, 5726, 5578, 5654, 5608, 5662, 5720, 9180 };
	int cnt, i = 0;
	float aver = 0;
	var vs[40] = { 0 };
	var* it, * end;

	end = cnt_moda(mas, mas + sizeof(mas) / sizeof(mas[0]), vs);
	cnt = max_moda(vs, end);

	for (it = vs; it != end; ++it) {
		if (it->n == cnt)
		{
			printf("moda: %d\n", it->v);
			aver += it->v;
			i++;
		}
	}
	aver /= i;
	printf("%f", aver);
		return 0;
}