#include <stdint.h>
#include <stddef.h>
#include <limits.h>


//This is the event queue for holding a series of processes or events for the sm

typedef uint8_t EID;

struct Event {
	EID id;
	uint64_t data;
};

#define MAX_ID 255
#define NULL_EVENT (struct Event) {MAX_ID, 0}
#define EMPTY NULL

void init_event_queue(void);

// Raises or otherwise adds a new event to the queue
void add_event(EID id, uint64_t data);

struct Event process_next_event(void);
