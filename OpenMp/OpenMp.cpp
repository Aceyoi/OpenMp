// Open#include <iostream>
#include <vector>
#include <omp.h>
#include <iostream>

using namespace std;

void random_array(vector<int>& a, size_t MAX, size_t MIN) {
    for (int i = 0; i < a.size(); i++) {
        a[i] = rand() % MAX + MIN;
    }
}

int alternatingSum(const vector<int>& arr) {
    int sum = 0.0;
    int n = arr.size();

    //Цикл параллелизуется директивой OpenMP.
    //Каждый поток считает часть суммы, а затем OpenMP объединяет их.
    //reduction(+:sum) означает, что все локальные переменные sum из потоков
    //будут автоматически объединены в одну итоговую переменную путем сложения.

#pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < n; ++i) {
        // Вычисляем знак: + если i чётный (т.е. a1, a3, ...), - если нечётный (a2, a4, ...)
        int sign = (i % 2 == 0) ? 1 : -1;

        // Добавляем элемент с нужным знаком
        sum += sign * arr[i];
    }

    return sum;
}

int main() {
    setlocale(LC_ALL, "Russian");
    int n;

    cout << "Задача: Даны натуральное число n, действительные числа a1,..., an. Вычислить: a1 - a2 + a3 - ... + (-1)^(n+1)*an;";
    // Ввод количества элементов
    cout << "Введите количество элементов n: ";
    cin >> n;

    vector<int> arr(n);
    srand(time(NULL));

    random_array(arr, 1000, 1);

    // Вычисляем результат
    int result = alternatingSum(arr);

    // Вывод результата
    cout << "Результат выражения: " << result << endl;

    return 0;
}

