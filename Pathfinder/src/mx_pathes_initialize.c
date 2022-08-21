#include "../inc/header.h"

int mx_pathes_initialize(int islands_count, int d[islands_count], int v[islands_count], int begin_index, int matrix[islands_count][islands_count]) {
    int temp, minindex, min;

    //Инициализация вершин и расстояний
    for (int i = 0; i < islands_count; i++) {
        d[i] = 2147483647;
        v[i] = 1;
    }
    d[begin_index] = 0;
    // Шаг алгоритма
    do {
        minindex = 2147483647;
        min = 2147483647;
        for (int i = 0; i < islands_count; i++) { // Если вершину ещё не обошли и вес меньше min
            if ((v[i] == 1) && (d[i]<min)) { // Переприсваиваем значения
                min = d[i];
                minindex = i;
            }
        }
        // Добавляем найденный минимальный вес
        // к текущему весу вершины
        // и сравниваем с текущим минимальным весом вершины
        if (minindex != 2147483647) {
            for (int i = 0; i < islands_count; i++) {
                if (matrix[minindex][i] > 0) {
                    if (min + matrix[minindex][i] < 0) {
                        mx_printerr("error: sum of bridges lengths is too big\n");
                        return 1;
                    }
                    temp = min + matrix[minindex][i];
                    if (temp < d[i]) {
                        d[i] = temp;
                    }
                }
            }
            v[minindex] = 0;
        }
    } while (minindex < 2147483647);

    return 0;
}

