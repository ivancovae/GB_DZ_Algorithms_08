#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <math.h>

void solution00();
void solution01();
void solution02();
void menu();

// Задание выполнил Иванцов Александр Евгеньевич
int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Rus");
	int select = 0;

	do
	{
		menu();
		scanf("%i", &select);
		switch (select)
		{
		case 1:
			solution00();
			break;
		case 2:
			solution01();
			break;
		case 3:
			solution02();
			break;		
		case 0:
			printf("Программа закончила свое выполнение.\n");
			break;
		default:
			printf("Некорректный символ, введите значения из списка меню.\n");
		}
	} while (select != 0);
	system("pause");
	return 0;
}

void menu()
{
	printf("Меню выбора решения задания:\n\n");

	printf("1. Решение задачи 1\n");
	printf("2. Решение задачи 2\n");
	printf("3. Решение задачи 3\n");
	printf("0. Завершение выполнения программы\n");
}

void descriptionTask(char *task)
{
	printf("\n##########################################\n");
	printf("\nУсловие задачи:\n");
	printf(task);
}

void endTask()
{
	printf("\n##########################################\n\n");
}
void swap(int * p, int * q)
{
	int buf;
	buf = *p;
	*p = *q;
	*q = buf;
}

// Пирамидальная сортировка
int heapSort(int * a, int n)
{
	int i, j, mid, t = n - 1, k;
	mid = n / 2; // середина массива
	for (i = mid; i >= 1; i--)
	{
		if (a[i - 1] < a[2 * i - 1]) // условие сравнения, которое соответствует пирам.	сортировке
			swap(&a[i - 1], &a[2 * i - 1]);
		if (2 * i < n && a[i - 1] < a[2 * i]) // если n-нечетное
			swap(&a[i - 1], &a[2 * i]);
	}
	k = 2 * mid;
	swap(&a[0], &a[t]);
	t--;
	while (t > 0)
	{
		mid = t / 2; // теперь на последнем месте стоит максимальный элемент, его больше не трогаем
			// и проходимся по коротким ветвям
			for (i = mid; i >= 1; i--)
			{ 
				if (a[i - 1] < a[2 * i - 1])
					swap(&a[i - 1], &a[2 * i - 1]);
				if (2 * i < n && a[i - 1] < a[2 * i])
					swap(&a[i - 1], &a[2 * i]);
			}
		k += 2 * mid;
		swap(&a[0], &a[t]);
		t--;
	}
	if (n > 0 && a[0] > a[1]) // самое последнее сравнение: нулевого с первым элементом
		swap(&a[0], &a[1]);
	k++;
	return k;
}

// Сортировка подсчетом
void countingSort(int *array, unsigned int n, int minValue, int maxValue)
{
	int k = maxValue - minValue + 1;
	int *countArr = (int *)malloc(k * sizeof(int));
	int i, j;
	for (i = 0; i < k; i++)
		countArr[i] = 0;

	for (i = 0; i < n; i++)
		countArr[array[i] - minValue]++;
	
	int b = 0;
	for (j = 0; j < k; j++)
	{
		int countRep = countArr[j];
		if (countRep > 0)
		{
			for (i = 0; i < countRep; i++)
			{
				array[b++] = j + minValue;
			}
		}
	}

	free(countArr);
}

// Быстрая сортировка
void quickSort(int *array, int first, int last, int *k)
{
	int i = first, j = last, x = array[(first + last) / 2];
	do
	{
		while (array[i] < x)
		{
			i++;
			*k = *k + 1;
		}
		while (array[j] > x)
		{
			j--;
			*k = *k + 1;
		}
		*k = *k + 1;
		if (i <= j)
		{
			*k = *k + 1;
			if (array[i] > array[j])
				swap(&array[i], &array[j]);
			i++;
			j--;
		}
		*k = *k + 1;
	} while (i <= j);
	*k = *k + 1;
	if (i < last)
		quickSort(array, i, last, k);
	*k = *k + 1;
	if (first < j)
		quickSort(array, first, j, k);
}

void mergeSort(int *array)
{

}

void pigeonholeSort(int *array)
{

}

const int MAX = 1024;

void showArray(FILE *fout, char* message, int *array, int N)
{
	fprintf(fout, "%s\n[", message);
	for (int i = 0; i < N; i++)
		fprintf(fout, ((i == 0) ? "%d" : ", %d"), array[i]);
	fprintf(fout, "]\n");
}

void showAnalitics(FILE *fout, int N, int k)
{
	fprintf(fout, "\nКоличество элементов: %d\nКоличество сравнений: %d\n", N, k);
	fprintf(fout, "n^2 = %lf\nn*log(n) = %lf\n\n", pow(N, 2), (N * log(N) / log(exp(1))));
}

int *getArrayFromFile(char *filename, int *N)
{
	FILE *fin = fopen(filename, "r");
	int count = 0;
	int *arr = (int *)malloc(MAX * sizeof(int)); // выделяем память
	while (fscanf(fin, "%d", &arr[count]) == 1)
		count++;
	fclose(fin);
	*N = count;
	return arr;
}

// Задание 1: Реализовать сортировку подсчетом.
void solution00()
{
	descriptionTask("Реализовать сортировку подсчетом.\n");
	// Ввод данных
	char filename[SHRT_MAX];
	printf("\nВведите файл, из которого будут считаны данные: ");
	scanf("%s", filename);

	FILE *fout = fopen("output.txt", "w");
	int N = 0;
	int *arr = getArrayFromFile(filename, &N);
	showArray(fout, "Исходный массив:", arr, N);
	countingSort(arr, N, -10, 10);
	showAnalitics(fout, N, 0);
	showArray(fout, "Отсортированный массив:", arr, N);
	fclose(fout);

	free(arr);
	endTask();
}

// Задание 2: Реализовать быструю сортировку.
void solution01()
{
	descriptionTask("Реализовать быструю сортировку.\n");
	// Ввод данных
	char filename[SHRT_MAX];
	printf("\nВведите файл, из которого будут считаны данные: ");
	scanf("%s", filename);

	int N = 0;
	int *arr = getArrayFromFile(filename, &N);

	FILE *fout = fopen("output.txt", "w");
	showArray(fout, "Исходный массив:", arr, N);
	int k = 0;
	quickSort(arr, 0, N - 1, &k);
	showAnalitics(fout, N, k);
	showArray(fout, "Отсортированный массив:", arr, N);
	fclose(fout);

	free(arr);
	endTask();
}

// Задание 3: *Реализовать сортировку слиянием.
void solution02()
{
	descriptionTask("*Реализовать сортировку слиянием.\n");
	// Ввод данных
	char filename[SHRT_MAX];

	printf("\nВведите файл, из которого будут считаны данные: ");
	scanf("%s", filename);

	endTask();
}

// Задание 4: **Реализовать алгоритм сортировки со списком.
void solution03()
{
	descriptionTask("**Реализовать алгоритм сортировки со списком.\n");
	// Ввод данных
	char filename[SHRT_MAX];

	printf("\nВведите файл, из которого будут считаны данные: ");
	scanf("%s", filename);

	endTask();
}