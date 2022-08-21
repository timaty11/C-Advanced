#include "../inc/libmx.h"

char *mx_itoa(int number) {
	int temp = number;
	int i = 0;
	char *res;
	int neg = 0;

	if (number == -2147483648) {
		res = "-2147483648";
		return res;
	}
	if (number < 0) {
		number *= -1;
		temp *= -1;
		neg = 1;
		i++;
	}
	if (number == 0) {
		i = 1;
	}
	while (temp >= 1) {
		i++;
		temp /= 10;
	}

    temp = number;
	res = mx_strnew(i);
	for (int y = 1; y <= i; y++) {
		res[i - y] = (temp % 10) + 48;
		temp /= 10;
	}
	if (neg == 1) {
		res[0] = '-';
	}

	return res;
}
