#include "../inc/header.h"

void mx_sort_all_pathes(int islands_count, char *paths_array[islands_count * islands_count][islands_count + 3], char *islands[]) {
    // Выбираем строчку для рассмотрения
    for (int line_to_check = 0; line_to_check < islands_count * islands_count; line_to_check++) {
        // Проходимся по всему массиву по новой и ищем совпадения
        for (int j = 0; j < islands_count * islands_count; j++) {
            if (line_to_check == j) {
                continue;
            }
            
            if (paths_array[j][0] != NULL) {
                if ((!mx_strcmp(paths_array[j][0], paths_array[line_to_check][1]) && !mx_strcmp(paths_array[j][1], paths_array[line_to_check][0])) ||
                    (mx_get_island_index(paths_array[j][0], islands) > mx_get_island_index(paths_array[j][1], islands))) {

                    // Меняем местами начальную точку и конечную (первые два элемента)
                    char *temp = mx_strdup(paths_array[j][0]);
                    paths_array[j][0] = mx_strdup(paths_array[j][1]);
                    paths_array[j][1] = mx_strdup(temp);

                    // Вычислим количество вершин в пути
                    int len = 0;
                    for (int i = 2; paths_array[j][i] != NULL && i < islands_count + 2; i++) {
                        len++;
                    }

                    // Отзеркаливаем остальные элементы кроме последнего
                    int left = 2, right = len + 1;
                    while (left < right) {
                        char *temp = mx_strdup(paths_array[j][right]);
                        paths_array[j][right] = mx_strdup(paths_array[j][left]);
                        paths_array[j][left] = mx_strdup(temp);
                        left++;
                        right--;
                    }
                    break;
                }
            }
        }
    }

    //// ВСЕ ПУТИ РАССТАВЛЕНЫ В ПРОАВИЛЬНОМ ПОРЯДКЕ (ПО ИДЕЕ) ТЕПЕРЬ ЕБАШИМ СОРТИРОВКУ

    // First, check if there is no full duplicate path
    for (int line_to_check = 0; line_to_check < islands_count * islands_count; line_to_check++) {
        for (int j = 0; j < islands_count * islands_count; j++) {
            if (line_to_check == j) {
                continue;
            }

            if (paths_array[j][0] != NULL) {
                if ((!mx_strcmp(paths_array[j][0], paths_array[line_to_check][0]) && !mx_strcmp(paths_array[j][1], paths_array[line_to_check][1])) ||
                    (!mx_strcmp(paths_array[j][0], paths_array[line_to_check][1]) && !mx_strcmp(paths_array[j][1], paths_array[line_to_check][0]))) {
                        int coincidence = 0;
                        int len = 0;
                        for (int i = 2; i < islands_count + 2; i++) {
                            
                            if (paths_array[j][i] != NULL || paths_array[line_to_check][i] != NULL) {
                                len++;
                                if (!mx_strcmp(paths_array[j][i], paths_array[line_to_check][i])) {
                                    coincidence++;
                                }
                            }
                        }
                        if (coincidence >= len) {
                            for (int i = 0; i <= islands_count + 2; i++) {
                                paths_array[j][i] = NULL;
                            }
                        }
                }
            }
        }
    }

    // Firtsly put all the pathes in groupes like A-B put near latest A-B
    for (int line_to_check = 0; line_to_check < islands_count * islands_count; line_to_check++) {        
        if (paths_array[line_to_check][0] != NULL && line_to_check - 1 >= 0 && (mx_strcmp(paths_array[line_to_check][0], paths_array[line_to_check - 1][0]) != 0 || mx_strcmp(paths_array[line_to_check][1], paths_array[line_to_check - 1][1]) != 0)) {
            for (int j = line_to_check; j >= 0; j--) {
                if (line_to_check == j) {
                    continue;
                }

                if (paths_array[j][0] != NULL && !mx_strcmp(paths_array[line_to_check][0], paths_array[j][0]) && !mx_strcmp(paths_array[line_to_check][1], paths_array[j][1])) {
                    mx_move_paths_arr(islands_count, paths_array, islands, line_to_check, j + 1);
                    break;
                }
            }
        }
    }

    // Do sort by looking at elements indexes
    for (int line_to_check = 0; line_to_check < islands_count * islands_count; line_to_check++) {
        if (paths_array[line_to_check][0] == NULL) {
            continue;
        }
        for (int j = line_to_check; j >= 0; j--) {
            if (line_to_check == j) {
                continue;
            }

            if (paths_array[j][0] != NULL) {
                if (mx_get_island_index(paths_array[line_to_check][0], islands) < mx_get_island_index(paths_array[j][0], islands)) {
                    mx_move_paths_arr(islands_count, paths_array, islands, line_to_check, j);
                } else if (mx_get_island_index(paths_array[line_to_check][0], islands) == mx_get_island_index(paths_array[j][0], islands)) {
                    if (mx_get_island_index(paths_array[line_to_check][1], islands) < mx_get_island_index(paths_array[j][1], islands)) {
                        mx_move_paths_arr(islands_count, paths_array, islands, line_to_check, j);
                    } else if (mx_get_island_index(paths_array[line_to_check][1], islands) == mx_get_island_index(paths_array[j][1], islands)) {
                        for (int i = 2; i < islands_count + 2; i++) {
                            if (paths_array[line_to_check][i] != NULL && paths_array[j][i] != NULL) {
                                if (mx_get_island_index(paths_array[line_to_check][i], islands) < mx_get_island_index(paths_array[j][i], islands)) {
                                    mx_move_paths_arr(islands_count, paths_array, islands, line_to_check, j);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

