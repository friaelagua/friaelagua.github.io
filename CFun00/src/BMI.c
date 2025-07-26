#include <stdio.h>

int main(void) {

	float w,h;

	printf("Enter Weight (kg): ");
	scanf("%f",&w);

 	printf("Enter Height (cm): ");
	scanf("%f",&h);

	float bmi=w/h/h*10000;

	printf("BMI: %.2f ",bmi);

	if( bmi < 18.5 )
		printf("underweight");
	else if( bmi <= 24.9 )
		printf("normal");
	else if( bmi <= 29.9 )
		printf("overweight");
	else
		printf("obese");
	printf("\n");

	return 0;
}