#include <time.h>

#define CLOCK_TO_MS(x) ((int)((x) * 1000 / CLOCKS_PER_SEC))

int now = CLOCK_TO_MS(clock());

if((now - CLOCK_TO_MS(clock())) >= 1000){
	printf("1 second passed");
}
