#include <iostream>
#include <ctime>
#include <cmath>
using namespace std;
const int m = 55; // Кол-во элементов
const int n = 4; // Размерность
const int t = m * 1.5 + 1; // Размер таблицы

int hash_func(int x) {
	int hash = 0;
	while (x > 0) {
		hash += x % 10;
		x /= 10;
	}
	return hash % t;
}

int main() {
	setlocale(LC_ALL, "Russian");
	int arr[t];
	for (int i = 0; i < t; i++) {
		arr[i] = -1; // Начальное значение
	}

	srand(time(0));
	int start = pow(10, n-1);
	int end = pow(10, n) - 1;
	int sum_count = 0;
	cout << "Сгенерированные ключи:\n";
	cout << '[';
	for (int i = 0; i < m; i++) {
		int x = rand() % (end - start + 1) + start;
		if (i == m - 1) { printf("%d]\n", x); }
		else { printf("%d, ", x); }
		int hash = hash_func(x);

		int count = 1;
		if (arr[hash] == -1) {
			arr[hash] = x;
		}
		else {
			int a = hash;
			int b = 1;
			while (count < t) { // Квадратичное опробывание
				count += 1;
				a = static_cast<int> (a + pow(b, 2)) % t;
				if (arr[a] == -1) {
					arr[a] = x;
					break;
				}
				b += 1;
			}
			if (count == t) { // Линейное опробывание
				a = hash;
				while (true) {
					count += 1;
					a = (a + 1) % t;
					if (arr[a] == -1) {
						arr[a] = x;
						break;
					}
				}
			}
		}

		sum_count += count;
	}

	cout << "Хеш-таблица:\n";
	cout << '[';
	for (int i = 0; i < t; i++) {
		if (i == t - 1) { printf("%d]\n", arr[i]); }
		else { printf("%d, ", arr[i]); }
	}

	int k = 0;
	for (int i = 0; i < t; i++) {
		if (arr[i] != -1) k += 1;
	}
	float alpha = static_cast<float>(k) / t;
	printf("Коэффициент заполнения таблицы: %f\n", alpha);
	float average_steps = static_cast<float>(sum_count) / m;
	printf("Среднее число шагов для размещения: %f\n", average_steps);
	return 0;
}