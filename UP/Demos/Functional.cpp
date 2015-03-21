#include <iostream>

using std::cout;
using std::endl;

void map(void* arr, int size, int count, void(*func)(void*)) {
	for (int i = 0; i < count; ++i)
	{
		func(((char*)arr) + i * size);
	}
}

double reduce(double* arr, int size, double start, 
	double(*func)(double, double)) 
{
	for (int i = 0; i < size; ++i) {
		start = func(start, arr[i]);
	}

	return start;
}

void generateSequance(void* n)
{
	static int i = 0;
	*(int*)n = i++;
}

double generateMembers(double n)
{
	return ((int)n % 2 ? -1 : 1) * 4.0 / (n * 2 + 1);
}

int inc(int num) 
{
	return ++num;
}

int square(int num) 
{
	return num * num;
}

void square(void* num)
{
	*(int*)num *= *(int*)num;
}

int ones(int num) 
{
	return 1;
}

int print(int num) 
{
	cout << num << ' ';
	return num;
}

void print(void* num)
{
	cout << *(int*)num << ' ';
}

double sum(double start, double next)
{
	return start + next;
}


double mult(double start, int next)
{
	return start * next;
}

int main()
{
	const int size = 20;
	int arr[size];

	map(arr, sizeof(int), size, generateSequance);
	map(arr, sizeof(int), size, square);
	map(arr, sizeof(int), size, print);

	system("pause");

	return 0;
}
