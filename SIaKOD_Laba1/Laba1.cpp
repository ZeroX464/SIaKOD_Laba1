#include <iostream>
#include <ctime>
#include <cmath>
using namespace std;
const int m = 55; // ���-�� ���������
const int n = 4; // �����������
const int t = m * 1.5 + 1; // ������ �������

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
		arr[i] = -1; // ��������� ��������
	}

	srand(time(0));
	int start = pow(10, n-1);
	int end = pow(10, n) - 1;
	int sum_count = 0;
	cout << "��������������� �����:\n";
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
			while (count < t) { // ������������ �����������
				count += 1;
				a = static_cast<int> (a + pow(b, 2)) % t;
				if (arr[a] == -1) {
					arr[a] = x;
					break;
				}
				b += 1;
			}
			if (count == t) { // �������� �����������
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

	cout << "���-�������:\n";
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
	printf("����������� ���������� �������: %f\n", alpha);
	float average_steps = static_cast<float>(sum_count) / m;
	printf("������� ����� ����� ��� ����������: %f\n", average_steps);
	return 0;
}