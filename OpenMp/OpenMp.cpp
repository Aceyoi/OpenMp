// Open#include <iostream>
#include <vector>
#include <omp.h>
#include <iostream>
#include <chrono>        

using namespace std;
using namespace chrono;

// Создание случайного массива
void random_array(vector<int>& a, size_t MAX, size_t MIN) {
    for (int i = 0; i < a.size(); i++) {
        a[i] = rand() % MAX + MIN;
    }
}

// Функция вычисления суммирования с OpenMP
int alternatingSum(const vector<int>& arr) {
    int sum = 0;
    int n = arr.size();

    //Цикл параллелизуется директивой OpenMP.
    //Каждый поток считает часть суммы, а затем OpenMP объединяет их.

#pragma omp parallel for reduction(+:sum) 
    // reduction(+:sum) cоздаёт локалбную переменую sum чтобы не вызвать гонку данных
    // А затем слаживает sum


    for (int i = 0; i < n; ++i) {

        // Вычисляем знак: + если i чётный (т.е. a1, a3, ...), - если нечётный (a2, a4, ...)
        int sign = (i % 2 == 0) ? 1 : -1;

        // Добавляем элемент с нужным знаком
        sum += sign * arr[i];

    }
    
    return sum;
}

// Функция вычисления суммирования с OpenMP
int Sum(const vector<int>& arr) {
    int sum = 0;
    int n = arr.size();

    for (int i = 0; i < n; ++i) {
        if (i % 2 == 0)
            sum += arr[i]; // если индекс четный (нумерация с 0), то прибавляем
        else
            sum -= arr[i]; // если индекс нечетный, то вычитаем
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

    vector<int> arr2(n);
    arr2 = arr;

    // Вычисляем результат c помощью OpenMP
    auto start = high_resolution_clock::now();
    int result = alternatingSum(arr);
    auto end = high_resolution_clock::now();
    auto duration_ms = duration_cast<milliseconds>(end - start).count();

    // Вычисляем результат
    auto start1 = high_resolution_clock::now();
    int result1 = alternatingSum(arr2);
    auto end1 = high_resolution_clock::now();
    auto duration_ms1 = duration_cast<milliseconds>(end1 - start1).count();

    // Вывод результата
    cout << "Результат выражения: " << result << endl;
    cout << "Время выполнения OpenMP: " << duration_ms << " мс" << endl;
    cout << "Время выполнения: " << duration_ms1 << " мс" << endl;

    return 0;
}