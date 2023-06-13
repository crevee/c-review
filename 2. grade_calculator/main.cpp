#include <stdio.h>
#include<stdlib.h>
#include<time.h>

int main() {

	int student[10][5], max_index = 0;

	srand(time(NULL));

	for (int i = 0; i < 10; i++) {
		student[i][0] = rand() % 101;
		student[i][1] = rand() % 85;
		student[i][2] = rand() % 70;

		student[i][3] = student[i][0] + student[i][1] + student[i][2];
		student[i][4] = student[i][3] / 3;

		if (student[max_index][4] < student[i][4]) {
			max_index = i;
		}
	}

	for (int i = 0; i < 10; i++) {
		printf("%d]	%d	%d	%d	%d	%d \n", 
		i, student[i][0],student[i][1],
		student[i][2], student[i][3], student[i][4]);
	}

	printf("\nMax index : %d \n", max_index);
}
