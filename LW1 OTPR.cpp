// LW1 OTPR.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <ctime>
#include <locale.h>
#include <cstdlib>
using namespace std;
//================================ Prototypes ==================================

void fillUpRandom1 (int* matrix, int task, int proc, int t1, int t2);

int* selectSortUp(int* matrix, int task, int proc);
int* selectSortDown(int* matrix, int task, int proc);
int Zmax(int* matrix, int proc);
int ZmaxInd(int* matrix, int proc);
void printMatrix(int** matrix, int task, int proc);
void printMatrix(int* matrix2, int proc);


void CPUs(int *matrix, int *matrix2, int task, int proc);
//================================ Main program ================================
int main()
{
	// ========================== Variables ====================================
	int task, t1, t2;
	int z; //количество массивов
	int zrandmax = 0, zupmax = 0, zdownmax = 0;
	double zrandav = 0, zupav = 0, zdownav = 0;
	int zrandind = 0, zupind = 0, zdownind = 0;
	double zrandindav = 0, zupindav = 0, zdownindav = 0;
	int proc = 0;
	//int **matrix; //исходный массив
	int *matrix;
	int *matrix2{};
	int *matrixdown; // массив, отсортированный по убыванию
	int *matrixup; // массив, отсортированный по возрастанию
	int *matrixupproc; // массив с процессорами для массива, отсортированного по возрастанию
	int *matrixdownproc; // массив с процессорами для массива, отсортированного по убыванию

						 // ==========================Program code===================================
	setlocale(LC_ALL, "rus");
	srand(time(0));
	cout << "-----------------------------------------------------------" << endl;
	cout << "|                                                          |" << endl;
	cout << "|                   Добро пожаловать!                      |" << endl;
	cout << "|                                                          |" << endl;
	cout << "------------------------------------------------------------" << endl;
	cout << "Введите количество массивов: " << endl;
	cin >> z;
	cout << "Введите количество заданий: " << endl;
	cin >> task;
	cout << "Введите количество процессоров: " << endl;
	cin >> proc;
	cout << "Введите t1: " << endl;
	cin >> t1;
	cout << "Введите t2: " << endl;
	cin >> t2;

	cout << endl;
	for (int i = 0; i < z; i++){
		// динамическое создание одномерного массива
		cout << "----------*--*--*------------" << endl;
		cout << "Z = " << i+1 << ": " << endl;
		matrix = new int[task];
		for (int i = 0; i < task; i++) {
			matrix[i] = 0;
		}

		// инициализация массивов с процессами
		matrix2 = new int[proc];
		for (int i = 0; i < proc; i++) {
			matrix2[i] = 0;
		}
		matrixupproc = new int[proc];
		for (int i = 0; i < proc; i++) {
			matrixupproc[i] = 0;
		}
		matrixdownproc = new int[proc];
		for (int i = 0; i < proc; i++) {
			matrixdownproc[i] = 0;
		}

		// распределение нагрузок
		cout << "Массив в случайном порядке: ";
		fillUpRandom1(matrix, task, proc, t1, t2);
		printMatrix(matrix, task);
		cout << "Распределение нагрузки на процессоры (случайный порядок): ";
		CPUs(matrix, matrix2, task, proc);
		printMatrix(matrix2, proc);
		zrandmax = zrandmax + Zmax(matrix2, proc);
		zrandind = zrandind + ZmaxInd(matrix2, proc);
		cout << endl;

		cout << "Отсортированный массив по возрастанию: ";
		matrixup = selectSortUp(matrix, task, proc);
		printMatrix(matrixup, task);
		cout << "Распределение нагрузки на процессоры (по возрастанию): ";
		CPUs(matrixup, matrixupproc, task, proc);
		printMatrix(matrixupproc, proc);
		zupmax = zupmax + Zmax(matrixupproc, proc);
		zupind = zupind + ZmaxInd(matrixupproc, proc);
		cout << endl;

		cout << "Отсортированный массив по убыванию: ";
		matrixdown = selectSortDown(matrix, task, proc);
		printMatrix(matrixdown, task);
		cout << "Распределение нагрузки на процессоры (по убыванию): ";		
		CPUs(matrixdown, matrixdownproc, task, proc);
		printMatrix(matrixdownproc, proc);
		zdownmax = zdownmax + Zmax(matrixdownproc, proc);
		zdownind = zdownind + ZmaxInd(matrixdownproc, proc);
		cout << endl;


		
		delete[] matrix;
		//delete[] matrixdown;
		//delete[] matrixup;
	}
	cout << "Zrandmax: " << zrandmax << endl;
	cout << "Zupmax: " << zupmax << endl;
	cout << "Zdownmax: " << zdownmax << endl;
	zrandav = double (zrandmax) / double(z);
	zupav = double(zupmax) / double(z);
	zdownav = double(zdownmax) / double(z);
	cout << "Среднее Zrandmax: " << zrandav << endl;
	cout << "Среднее Zupmax: " << zupav << endl;
	cout << "Среднее Zdownmax: " << zdownav << endl;

	zrandindav = double(zrandind) / double(z);
	cout << "Zrandmax average index: " << zrandindav <<endl;
	zupindav = double(zupind) / double(z);
	cout << "Zupmax average index: " << zupindav << endl;
	zdownindav = double(zdownind) / double(z);
	cout << "Zdownmax average index: " << zdownindav << endl;
	
	system("pause");
	return 0;
}

//============================= Functions =====================================

//*** заполнение случайными числами одномерного массива ***
void fillUpRandom1(int* matrix, int task, int proc, int t1, int t2) {
	int temp;
	for (int i = 0; i < task; i++) {
		temp = rand() % (t2 - t1 + 1) + t1;
			matrix[i] = temp;
	}

}
//*** максимальный элемент массива ***
int Zmax(int* matrix, int proc) {
	int max = 0;
	for (int i = 0; i < proc; ++i) {
		if (matrix[i] > max) {
			max = matrix[i];
		}
	}
	return max;
}
int ZmaxInd(int* matrix, int proc) {
	int max = 0;
	int indmax = 0;
	for (int i = 0; i < proc; ++i) {
		if (matrix[i] > max) {
			max = matrix[i];
			indmax = i;
		}
	}
	return indmax+1;
	
}
//*** сортировка методом выбора по возрастанию***
int* selectSortUp(int* matrix, int task, int proc) {
	for (int i = 1; i < task; ++i)
	{
		for (int r = 0; r < task - i; r++)
		{
			if (matrix[r] > matrix[r + 1])
			{
				// Обмен местами
				int temp = matrix[r];
				matrix[r] = matrix[r + 1];
				matrix[r + 1] = temp;
			}
		}
	}
	return matrix;
}

//*** сортировка методом выбора по убыванию***
int* selectSortDown(int* matrix, int task, int proc) {
	for (int i = 1; i < task; ++i)
	{
		for (int r = 0; r < task - i; r++)
		{
			if (matrix[r] < matrix[r + 1])
			{
				// Обмен местами
				int temp = matrix[r];
				matrix[r] = matrix[r + 1];
				matrix[r + 1] = temp;
			}
		}
	}
	return matrix;
}

//*** печать матрицы на экран***
void printMatrix(int** matrix, int task, int proc) {
	for (int i = 0; i < task; i++) {
		for (int j = 0; j < proc; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

void printMatrix(int* matrix2, int proc) {
	for (int i = 0; i < proc; i++) {

		cout << matrix2[i] << " ";

	}
	cout << endl;
}
//*** распределение на процессоры ***

void CPUs(int *matrix, int *matrix2, int task, int proc) {
	int min = matrix2[0];;
	int indexmin = 0;

	for (int i = 0; i < task; i++) {

		for (int k = 0; k < proc; k++) {
			if (matrix2[k] < min) {
				min = matrix2[k];
				indexmin = k;
			}
		}
		/*cout << "Минимальный элемент:" << min << endl;
		cout << "Индекс минимального элемента:" << indexmin << endl;*/
		matrix2[indexmin] += matrix[i];
		min += matrix[i];
	}
}
