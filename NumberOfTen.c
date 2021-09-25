#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <Windows.h>
#include <locale.h>
#include <math.h>
#pragma intrinsic(__rdtsc)
#define ull unsigned long long
#define uc unsigned char

struct tree
{
	ull value, count;
	struct tree* parent, * left, * right;
};

struct tree* newNode(ull x)
{
	struct tree* node = (struct tree*)malloc(sizeof(struct tree));
	node->value = x;
	node->left = node->right = NULL;
	node->count = 0;
	return (node);
}

struct tree* rightRotate(struct tree* x)
{
	struct tree* y = x->left;
	x->left = y->right;
	y->right = x;
	return y;
}

struct tree* leftRotate(struct tree* x)
{
	struct tree* y = x->right;
	x->right = y->left;
	y->left = x;
	return y;
}

struct tree* splay(struct tree* root, ull x)
{
	if (root == NULL || root->value == x) return root;
	if (root->value > x)
	{
		if (root->left == NULL) return root;
		if (root->left->value > x)
		{
			root->left->left = splay(root->left->left, x);
			root = rightRotate(root);
		}
		else if (root->left->value < x)
		{
			root->left->right = splay(root->left->right, x);
			if (root->left->right != NULL) root->left = leftRotate(root->left);
		}
		return (root->left == NULL) ? root : rightRotate(root);
	}
	else
	{
		if (root->right == NULL) return root;
		if (root->right->value > x)
		{
			root->right->left = splay(root->right->left, x);
			if (root->right->left != NULL) root->right = rightRotate(root->right);
		}
		else if (root->right->value < x)
		{
			root->right->right = splay(root->right->right, x);
			root = leftRotate(root);
		}
		return (root->right == NULL) ? root : leftRotate(root);
	}
}

struct tree* insert(struct tree* root, ull x)
{
	if (root == NULL)
	{
		struct tree* newnode = newNode(x);
		newnode->count++;
		return newnode;
	}
	root = splay(root, x);
	if (root->value == x)
	{
		root->count++;
		return root;
	}
	struct tree* newnode = newNode(x);
	if (root->value > x)
	{
		newnode->right = root;
		newnode->left = root->left;
		newnode->count++;
		root->left = NULL;
	}
	else
	{
		newnode->left = root;
		newnode->right = root->right;
		newnode->count++;
		root->right = NULL;
	}
	return newnode;
}

void display(struct tree* root)
{
	if (root != NULL)
	{
		printf(" %llu : %llu шт.\n", root->value, root->count);
		display(root->left);
		display(root->right);
	}
}

int ten(char x)
{
	if (x == '0') return 0;
	int tenth = x - '0';
	return tenth;
}

boolean check(uc a)
{
	if (a == NULL) return 1;
	return ((a < 65) || (a > 90 && a < 97) || (a > 122 && a < 128) || (a > 175 && a < 224) || a > 241);
}

boolean incheck(uc pr, uc a)
{
	return (pr == '0' && (a > '0' && a <= '9' || a == 'x' || a == 'b'));
}

#define n 20

int main()
{
	setlocale(LC_ALL, "Rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	uc namefile[20], a[n + 1], ch, prev = NULL;
	FILE* file;
	int i = 0;
	unsigned __int64 start, end;
	struct tree* root = NULL;

	printf("Название файла: ");
	scanf("%s", &namefile);
	if (namefile[strlen(namefile) - 2] != '.')
		strcat(namefile, ".c");
	file = fopen(namefile, "r");

	start = __rdtsc();
	while (!feof(file))
	{
		ch = fgetc(file);
		if (prev == 'n' || prev == 't')
		{
			fseek(file, -3, SEEK_CUR);
			//char tr = fgetc(file);
			if (fgetc(file) == '\\')
			{
				fseek(file, 2, SEEK_CUR);
				goto tag;
			}
			fseek(file, 2, SEEK_CUR);
		}
		if (check(prev))
		{
			tag:
			while (ch >= '0' && ch <= '9')
			{
				a[i] = ch;
				uc inprev = ch;
				i++;
				ch = fgetc(file);
				if (ch == '.' || ch == 'f' || incheck(inprev, ch))
				{
					while (i)
					{
						i--;
						a[i] = NULL;
					}
					do
					{
						ch = fgetc(file);
					} while (ch >= '0' && ch <= '9');
					break;
				}
			}
			int m = 10, fl = 0;
			ull number = 0;
			for (int j = 0; j < i; j++)
			{
				a[j] = ten(a[j]);
				number += a[j] * pow(m, i - j - 1);
				if (number == 0) fl = 1;
			}
			if (number != 0 || fl == 1)
				root = insert(root, number);
			while (i != 0)
			{
				i--;
				a[i] = NULL;
			}
		}
		prev = ch;
	}
	fclose(file);
	end = __rdtsc();

	printf("Число элементов\n");
	display(root);
	printf("\nВремя %llu\n", end - start);
	return 0;
}