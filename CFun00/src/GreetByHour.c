#include <stdio.h>

int main(void) {
	char name[20];
	int hour;
	printf("What is your name? ");
	scanf("%19s",name);
	printf("What is the hour (0..23)? ");
	scanf("%d",&hour);


	if (hour >= 5 && hour < 12) {
        printf("Good Morning, %s!\n",name);
    } else if (hour >= 12 && hour < 17) {
        printf("Good Afternoon %s!\n",name);
    } else if (	(hour >= 17 && hour <= 23) ||
				(hour >=  0 && hour <=  4)
    ) {
        printf("Good Evening, %s!\n",name);
    } else {
    	printf("Invalid Hour!\n");
    }

	return 0;
}
