#include <stdio.h>
#include "sm/event_queue.h"

struct Event e = NULL_EVENT;

int main()
{
	int i;
	init_event_queue();

	for (i = 0; i < 10; i++) {
		add_event((EID) i, (uint64_t) i);
		if (i == 5 || i == 7) {
			e = process_next_event();
			printf("Event %d, data: %lu\n", e.id, e.data);
		}
	}

	for (i = 0; i < 10; i++) {
		e = process_next_event();
		if (e.id != MAX_ID) {
			printf("Event %d, data: %lu\n", e.id, e.data);
		}
		else {
			printf("Empty Queue\n");
			break;
		}
	}
}