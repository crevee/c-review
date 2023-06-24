#include <stdio.h>

int main() {
	int a, b;

	printf("input 2 data :");
	scanf_s("%d %d", &a, &b);

	printf("%d + %d = %d \n", a, b, a + b);
	printf("%d - %d = %d \n", a, b, a - b);
	printf("%d * %d = %d \n", a, b, a * b);
	
	float f = (float)a / b;

	printf("%d / %d = %.2f \n", a, b, f);
	
	if (a > b) {
		printf("max : %d", a);
	}
	else {
		printf("max : %d", b);
	}
}
