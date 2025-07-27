#include <stdio.h>
#include <time.h>

int main() {
    time_t rawtime;
    struct tm *info;
	int hour,minute;

    // Get the current time
    time(&rawtime);

    // Convert to local time structure
    info = localtime(&rawtime);

	hour=info->tm_hour;
	minute=info->tm_min;

	if (hour >= 5 && hour < 12) {
        printf("Good Morning!");
    } else if (hour >= 12 && hour < 17) {
        printf("Good Afternoon!");
    } else if (
    	(hour >= 17 && hour <=23) ||
    	(hour >=  0 && hour <= 4)
    ) {
        printf("Good Evening!");
    }
    printf("\n");

	// Adjust hour for 12-hour format if needed
    if (hour == 0) {
        hour = 12; // 00:MM is 12 AM
    } else if (hour > 12) {
        hour -= 12; // Convert to 12-hour format
    }

    if (minute == 0) {
        printf("It is %d o'clock.\n", hour);
    } else if (minute == 15) {
        printf("It is quarter past %d.\n", hour);
    } else if (minute == 30) {
        printf("It is half past %d.\n", hour);
    } else if (minute == 45) {
     // For 'quarter to', the hour should be the next hour
		printf("It is quarter to %d.\n", (hour % 12) + 1);
    } else if (minute < 30) {
        printf("It is %d minutes past %d.\n", minute, hour);
    } else { // minute > 30
        printf("It is %d minutes to %d.\n", 60 - minute, (hour % 12) + 1);
    }




    return 0;
}
