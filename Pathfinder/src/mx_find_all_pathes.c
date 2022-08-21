#include "../inc/header.h"

int mx_find_all_pathes(int islands_count, int paths_array_size, char *paths_array[paths_array_size][islands_count + 3], int matrix[islands_count][islands_count], char *islands[], int begin_index, int end_point, int *paths_array_index) {
    int d[islands_count]; // min distance
    int v[islands_count]; // visited islands
    
    if (mx_pathes_initialize(islands_count, d, v, begin_index, matrix) != 0) {
        return 1;
    }

    bool path_dup = false;
    bool path_dup_reverse = false;
    bool path_full_dup = false;
    bool found_path = false;
    int failure_handle = 0;
    
    int line = 0; // line were we found path_dup
    
    // Repeat path build with these begin island and end island until h < islands_count
    for (int h = 0; h < islands_count * 2; h++) {
        line = 0;
        int dup_check = 0;
        path_dup = false;
        path_dup_reverse = false;
        // Check if there was such path with these begin island and end island
        for ( ; line < paths_array_size; line++) {
            if (paths_array[line][0] != NULL) {
                dup_check = mx_check_dup(islands_count, paths_array_size, paths_array, islands, line, begin_index, end_point);
                // If the path is A - B and we found A - B then dup_check will be 1 and this if will be true
                if (dup_check == 1) {
                    path_dup = true;
                    break;
                // dup_check = 2 means we found B - A path when were looking for A - B
                } else if (dup_check == 2) {
                    path_dup_reverse = true;
                    break;
                }
            }
        }

        path_full_dup = false;
        // Path generation
        int ver[islands_count]; // visited islands

        int temp_ver[islands_count][islands_count]; // used for error handling in first path creating attemp
        for (int i = 0; i < islands_count; i++) {
            for (int j = 0; j < islands_count; j++) {
                temp_ver[i][j] = 0;
            }
        }

        int end = end_point;
        ver[0] = end + 1;
        int k = 1; // latest visited island index
        int weight = d[end]; // end island weight

        // If it'sA-C,6 first try to build the path with these begin island and end island
        if (h == 0) {
            failure_handle = 0;
            int index = 0;
            if (path_dup || path_dup_reverse) {
                // Till we are not at our start island and also check wether is there a infinte loop
                while (end != begin_index && failure_handle < 30) {
                    // check all the islands
                    for (int i = 0; i < islands_count; i++) {
                        // if there is a bridge
                        if (matrix[i][end] != 0) {
                            // Check the weight from the previous island
                            int temp = weight - matrix[i][end];
                            // If weight is equal then from this island could be a short path
                            if (temp == d[i]) {
                                // if in previous path was the same island on this position we need to check oter island
                                if (paths_array[*paths_array_index - 1][0] != NULL && !mx_strcmp(islands[i], paths_array[*paths_array_index - 1][index + 2])) {
                                    continue;
                                } else {
                                    weight = temp;
                                    end = i;
                                    ver[k] = i + 1;
                                    k++;
                                    index++;
                                }
                            }
                        }
                    }
                    failure_handle++;
                }
            } else {
                // Till we are not at our start island and also check wether is there a infinte loop
                while (end != begin_index && failure_handle < 30) {
                    // check all the islands
                    for (int i = 0; i < islands_count; i++) {
                        // if there is a bridge
                        if (matrix[i][end] != 0) {
                            // Check the weight from the previous island
                            int temp = weight - matrix[i][end];
                            // If weight is equal then from this island could be a short path
                            if (temp == d[i]) {
                                weight = temp;
                                end = i;
                                ver[k] = i + 1;
                                k++;
                            }
                        }
                    }
                    failure_handle++;
                }
            }
            
            if (end == begin_index) {
                found_path = true;

                if (path_dup || path_dup_reverse) {
                    int coincidence = 0;
                    int i = 0;
                    int j = k - 1;

                    if (path_dup) {
                        for (int z = *paths_array_index - 1; z >= 0; z--) {
                            coincidence = 0;
                            j = k - 1;
                            for (i = 2; i < islands_count + 2 && j >= 0; i++) {
                                if (paths_array[z][0] != NULL && !mx_strcmp(islands[ver[j] - 1], paths_array[z][i])) {
                                    coincidence++;
                                }
                                j--;
                            }
                            if (coincidence >= k) {
                                path_full_dup = true;
                                break;
                            }
                        }
                    } else if (path_dup_reverse) {
                        for (int z = *paths_array_index - 1; z >= 0; z--) {
                            coincidence = 0;
                            j = k - 1;
                            for (i = k + 1; i >= 2 && j >= 0; i--) {
                                if (paths_array[z][0] != NULL && !mx_strcmp(islands[ver[j] - 1], paths_array[z][i])) {
                                    coincidence++;
                                }
                                j--;
                            }
                            if (coincidence >= k) {
                                path_full_dup = true;
                                break;
                            }
                        }
                    }

                    if (!path_full_dup) {
                        mx_save_found_path(islands_count, paths_array_size, paths_array, islands, ver, d, k, paths_array_index, begin_index, end_point);
                        found_path = false;
                        path_full_dup = false;
                    }
                } else {
                    mx_save_found_path(islands_count, paths_array_size, paths_array, islands, ver, d, k, paths_array_index, begin_index, end_point);
                    found_path = false;
                    path_full_dup = false;
                    continue;
                }
            }
        } else if (h < islands_count) {
            failure_handle = 0;
            int index = 0;
            // Till we are not at our start island and also check wether is there a infinte loop
            while (end != end_point && failure_handle < islands_count) {
                index = 0;
                k = 1;
                weight = 0;

                // check all the islands
                for (int i = 0; i < islands_count; i++) {
                    // if there is a bridge
                    if (matrix[i][end] != 0) {
                        // Check the weight from the previous island
                        int temp = weight + matrix[i][end];
                        // If weight is equal then from this island could be a short path
                        if (temp == d[i]) {
                            // if in previous path was the same island on this position we need to check oter island
                            if (i != end_point && mx_check_path_dup_islands(i, index, paths_array_index, islands_count, paths_array_size, paths_array, islands, begin_index, end_point) != 0) {
                                continue;
                            }
                            
                            weight = temp;
                            end = i;
                            ver[k] = i + 1;
                            k++;
                            index++;
                        }
                    }
                    if (end == end_point && weight == d[end_point]) {
                        break;
                    }
                }
                failure_handle++;

                if (end != end_point) {
                    for (int i = 0; i < islands_count; i++) {
                        // if there is a bridge
                        if (matrix[i][end] != 0) {
                            bool skip = false;
                            for (int j = failure_handle - 1; j >= 0; j--) {
                                if (i + 1 == temp_ver[j][k]) {
                                    skip = true;
                                    break;
                                }
                            }
                            if (skip) {
                                continue;
                            }

                            // Check the weight from the previous island
                            int temp = weight + matrix[i][end];
                            // If weight is equal then from this island could be a short path
                            if (temp == d[i]) {
                                // if in previous path was the same island on this position we need to check oter island
                                if (i != end_point && mx_check_path_dup_islands(i, index, paths_array_index, islands_count, paths_array_size, paths_array, islands, begin_index, end_point) != 0) {
                                    continue;
                                }
                                
                                weight = temp;
                                end = i;
                                ver[k] = i + 1;
                                temp_ver[failure_handle][k] = ver[k];
                                k++;
                                index++;
                            }
                        }
                        if (end == end_point && weight == d[end_point]) {
                            break;
                        }
                    }
                }
            }
            
            if (end == begin_index) {
                found_path = true;
                
                if (path_dup || path_dup_reverse) {
                    int coincidence = 0;
                    int i = 2;
                    int j = k - 1;
                    
                    if (path_dup) {
                        for (int z = *paths_array_index - 1; z >= 0; z--) {
                            coincidence = 0;
                            j = k - 1;
                            for (i = 2; i < islands_count + 2 && j >= 0; i++) {
                                if (paths_array[z][i] != NULL && !mx_strcmp(islands[ver[j] - 1], paths_array[z][i])) {
                                    coincidence++;
                                }
                                j--;
                            }
                            if (coincidence >= k) {
                                path_full_dup = true;
                                break;
                            }
                        }
                    } else if (path_dup_reverse) {
                        for (int z = *paths_array_index - 1; z >= 0; z--) {
                            coincidence = 0;
                            j = k - 1;
                            for (i = k + 1; i >= 2 && j >= 0; i--) {
                                if (paths_array[z][i] != NULL && !mx_strcmp(islands[ver[j] - 1], paths_array[z][i])) {
                                    coincidence++;
                                }
                                j--;
                            }
                            if (coincidence >= k) {
                                path_full_dup = true;
                                break;
                            }
                        }
                    }
                    if (!path_full_dup) {
                        mx_save_found_path(islands_count, paths_array_size, paths_array, islands, ver, d, k, paths_array_index, begin_index, end_point);
                        found_path = false;
                        path_full_dup = false;
                    }
                } else {
                    mx_save_found_path(islands_count, paths_array_size, paths_array, islands, ver, d, k, paths_array_index, begin_index, end_point);
                    found_path = false;
                    path_full_dup = false;
                }
            } else {
                continue;
            }
        } else {
            failure_handle = 0;
            int index = 0;
            if (end != begin_index) {
                for (int r = 0; r < islands_count; r++) {
                    ver[r] = 0;
                }
                end = end_point;
                ver[0] = end + 1;
                k = 1; // latest visited island index
                weight = d[end]; // end island weight
                while (end != begin_index && failure_handle < 10) {
                    index = 0;
                    weight = d[end];
                    for (int i = islands_count - 1; i >= 0; i--) {
                        // if there is a bridge
                        if (matrix[i][end] != 0) {
                            // Check the weight from the previous island
                            int temp = weight - matrix[i][end];
                            // If weight is equal then from this island could be a short path
                            if (temp == d[i]) {
                                

                                // if in previous path was the same island on this position we need to check oter island
                                if (mx_check_path_dup_islands(i, index, paths_array_index, islands_count, paths_array_size, paths_array, islands, begin_index, end_point) != 0) {
                                    if (k == 1 && ((h - islands_count) / 2) == 1) {
                                        weight = temp;
                                        end = i;
                                        ver[k] = i + 1;
                                        k++;
                                        index++;
                                    }
                                    
                                    continue;
                                }
                                
                                weight = temp;
                                end = i;
                                ver[k] = i + 1;
                                k++;
                                index++;
                            }
                        }
                    }
                    failure_handle++;
                }
            }
            
            if (end == begin_index) {
                found_path = true;
                
                if (path_dup || path_dup_reverse) {
                    int coincidence = 0;
                    int i = 2;
                    int j = k - 1;
                    
                    if (path_dup) {
                        for (int z = *paths_array_index - 1; z >= 0; z--) {
                            coincidence = 0;
                            j = k - 1;
                            for (i = 2; i < islands_count + 2 && j >= 0; i++) {
                                if (paths_array[z][i] != NULL && !mx_strcmp(islands[ver[j] - 1], paths_array[z][i])) {
                                    coincidence++;
                                }
                                j--;
                            }
                            if (coincidence >= k) {
                                path_full_dup = true;
                                break;
                            }
                        }
                    } else if (path_dup_reverse) {
                        for (int z = *paths_array_index - 1; z >= 0; z--) {
                            coincidence = 0;
                            j = k - 1;
                            for (i = k + 1; i >= 2 && j >= 0; i--) {
                                if (paths_array[z][i] != NULL && !mx_strcmp(islands[ver[j] - 1], paths_array[z][i])) {
                                    coincidence++;
                                }
                                j--;
                            }
                            if (coincidence >= k) {
                                path_full_dup = true;
                                break;
                            }
                        }
                    }
                    if (!path_full_dup) {
                        mx_save_found_path(islands_count, paths_array_size, paths_array, islands, ver, d, k, paths_array_index, begin_index, end_point);
                        found_path = false;
                        path_full_dup = false;
                    }
                } else {
                    mx_save_found_path(islands_count, paths_array_size, paths_array, islands, ver, d, k, paths_array_index, begin_index, end_point);
                    found_path = false;
                    path_full_dup = false;
                }
            } else {
                continue;
            }
        }
    }

    return 0;
}

