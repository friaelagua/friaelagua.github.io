#include <stdio.h>
#include <time.h>

int main() {
    time_t rawtime;
    struct tm *info;
	int hour;
	char buf[256];

    // Get the current time
    time(&rawtime);

    // Convert to local time structure
    info = localtime(&rawtime);

	hour=info->tm_hour;

	if (	(hour >= 21 && hour <= 23) ||
		(hour >= 0 && hour <= 4)
	) {
		printf("Good Night!");
	} else if (hour >= 5 && hour < 12) {
        printf("Good Morning!");
    } else if (hour >= 12 && hour < 17) {
        printf("Good Afternoon!");
    } else if (hour >= 17 && hour < 21) {
        printf("Good Evening!");
    } else {
    	printf("Invalid Hour!");
    }
    printf("\n");

	strftime(buf, sizeof(buf), "%l:%M %p", info);

	printf("The time is %s.\n",buf);

    return 0;
}
