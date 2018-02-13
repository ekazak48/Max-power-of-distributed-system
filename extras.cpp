#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;


int max(double *arr, int n, int in, vector<int> way) { // поиск максимального из выходящих потоков
	
	int addr = -1;
	int value = 0;
	
	for (int i = 0; i<n; i++){
			
		// блок, отвечающий за проверку наличия в векторе определённого значения
		bool isExist = false;
		
		for (int j = 0; j < way.size(); j++) {
			if (way.at(j) == i) {
				isExist = true;
			}
		}
		// конец блока ==========================================================//
			
		if (*(arr+in*n+i) > value && !isExist){
				value = *(arr+in*n+i);
				addr = i;
		}
		
	};
	return addr; //возвращаемое значение - номер максимального элемента. Если такого нет - возврат -1
}

void zeros(double *arr, int n, int a) { // заполнение нулями входных потоков в точку
	
	for (int j = 0; j < n; j++) {
		*(arr + j*n + a) = 0;
	}
}

void moutput(double *arr, int n) { // вывод матрицы
	cout << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << setw (3) << *(arr+i*n+j) << " ";
		}
		cout << endl;
	}
	cout << endl;
}
