#include "event_queue.h"
#include <assert.h>
#include <stdio.h>

#define EVENT_COUNT 10

struct ENode {
	struct Event e;
	struct ENode *next;
};

struct EQueue {
	struct ENode *first;
	struct ENode *last;
};

static struct ENode nodes[EVENT_COUNT];
static struct EQueue queue;

void init_event_queue(void)
{
	struct ENode *tmpnode;
	for (tmpnode = nodes; tmpnode < nodes + EVENT_COUNT; tmpnode++) {
		tmpnode->e = NULL_EVENT;
		tmpnode->next = EMPTY;
	}
	queue.first = EMPTY;
	queue.last = EMPTY;
}

static void prv_release(struct ENode *node)
{
	node->e = NULL_EVENT;
	node->next = NULL;
}

static struct ENode *prv_get_next_free_node(void)
{
	struct ENode *tmpnode;
	for (tmpnode = nodes; tmpnode < nodes + EVENT_COUNT; tmpnode++) {
		if (tmpnode->e.id == MAX_ID)
			return tmpnode;
	}
	assert(0 && "Warn, pool size exceeded");
	return NULL;
}

void add_event(EID id, uint64_t data)
{
	struct ENode *node = prv_get_next_free_node();
	node->e = (struct Event) {id, data};
	node->next = NULL;
	if (queue.first == EMPTY) {
		queue.first = node;
	}
	else {
		queue.last->next = node;
	}
	queue.last = node;
}

struct Event process_next_event(void)
{
	if (queue.first == EMPTY) {
		return NULL_EVENT;
	}

	struct ENode *to_release = queue.first;
	struct Event ev = to_release->e;
	queue.first = to_release->next;
	if (to_release->next == EMPTY) {
		queue.first = EMPTY;
		queue.last = EMPTY;
	}
	prv_release(to_release);
	return ev;
}
