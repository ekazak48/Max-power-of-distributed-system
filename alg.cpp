#include <vector>
#include <iostream>
#include "extras.cpp"

using namespace std;

float pow(double *arr, int n, int inWay, int outWay) {
	//объявление необходимых изначально переменных
	double power = 0;
	double free[n][n];
	double freem[n][n];
	
	//Передача матрицы доступных потоков в массив структур
	//создаём две матрицы. Одна будет основной для обработки алгоритмом, вторая будет использоваться в качестве остаточной матрицы
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			free[i][j] = *(arr + i*n + j);
			freem[i][j] = *(arr + i*n + j);
		}
	}
	cout << "Матрица, по которой будут проведены вычисления: \n";
	moutput(&free[0][0], n);
	bool allWaysFounded = false;
	//может быть это место для начала цикла, но это не точно
	do{
		vector<int> way; // вектор для хранения текущего маршрута
		double bmpow = 0; //минимальный поток в итерации
		int in = inWay;
		cout << "Маршрут: ";
		way.insert(way.begin(), in); // инициализация входной точки маршрута
		cout << in+1 ; // вывод первой точки маршрута
		int out;
		
		do { // цикл - вычисление одного из увеличивающих путей маршрута
			
			out = max(&free[0][0], n, in, way); // нахождение выходного потока из текущей точки
			
			
			if (out == -1){ //обработка события, когда все выходные потоки имеют нулевое значение
				
				if (in == inWay){ // если очищаются входы в начальную точку, то все пути найдены
					allWaysFounded = true;
					cout << "\nМаршрутов, позволяющих увеличить пропускную систему, не осталось.";
				}				
				
				else{
					cout << "Из точки " << in+1 << "нет положительных выходных потоков";
					zeros(&free[0][0], n, out);
					//TODO: SMTH
					way.clear();
				}
			}
			
			else if (out > -1){ // если значение номера выходного потока валидное
				
				cout << " -> " << out+1 ; 
				
				way.insert(way.end(), out); //добавление в конец маршрута
					
				if (free[in][out] > 0){
					
					if (bmpow == 0){
						bmpow = free[in][out];
					}
					
					else 
						if (bmpow > free[in][out]){
							bmpow = free[in][out];
						}
				}
				in = out;
			}
			
		} while (out != outWay && !allWaysFounded ); //конец цикла поиска увеличивающего пути
		
		if (!allWaysFounded){
			cout << " = " << bmpow << endl;
			power += bmpow;
			
			for (int i = 0; i < way.size() - 1; i++){
				
				free[way[i]][way[i+1]] -= bmpow;
				freem[way[i]][way[i+1]] -= bmpow;
			}
		}
	} while (!allWaysFounded);
	
	cout << "\nМатрица остаточных потоков:\n";
	moutput(&freem[0][0], n);
	return power;
}
