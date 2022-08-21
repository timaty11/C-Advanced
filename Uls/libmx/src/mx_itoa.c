#include "../inc/libmx.h"

// char *mx_itoa(int number) {
// 	int temp = number;
// 	int i = 0;
// 	char *res;
// 	int neg = 0;

// 	if (number == -2147483648) {
// 		res = "-2147483648";
// 		return res;
// 	}
// 	if (number < 0) {
// 		number *= -1;
// 		temp *= -1;
// 		neg = 1;
// 		i++;
// 	}
// 	if (number == 0) {
// 		i = 1;
// 	}
// 	while (temp >= 1) {
// 		i++;
// 		temp /= 10;
// 	}

//     temp = number;
// 	res = mx_strnew(i);
// 	for (int y = 1; y <= i; y++) {
// 		res[i - y] = (temp % 10) + 48;
// 		temp /= 10;
// 	}
// 	if (neg == 1) {
// 		res[0] = '-';
// 	}

// 	return res;
// }

char *mx_itoa(int number) {
    int tmp = number;
    int count = 0;
    while (tmp)
    {
        tmp /= 10;
        count++;
    }
	char *str = mx_strnew(count);

	if (number == 0)
    {
		return mx_strcpy(str, "0");
    }
	else if (number == -2147483648)
    {
		return mx_strcpy(str, "-2147483648");
    }
    else if (number < 0)
    {
		str[count] = '-';
		number = -number;
	}
	for (int i = 0; i < count; i++)
    {
		str[i] = (number % 10) + '0';
		number /= 10;
	}
	mx_str_reverse(str);
	return str;
}

