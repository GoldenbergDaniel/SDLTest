#include "base/base_common.h"
#include "base/base_os.h"

#include "event.h"

void push_event(EventQueue *queue, EventType type, EventDescriptor desc)
{
  Event *new_back = os_alloc(sizeof (Event));
  new_back->type = type;
  new_back->descripter = desc;

  if (queue->front == NULL)
  {
    queue->front = new_back;
  }
  else
  {
    queue->back->next = new_back;
  }

  new_back->next = NULL;
  queue->back = new_back;
  queue->count++;
}

void pop_event(EventQueue *queue)
{
  ASSERT(queue->count > 0);

  Event *next = queue->front->next;
  os_free(queue->front, sizeof (Event));
  
  if (queue->count == 2)
  {
    queue->back = next;
  }

  queue->front = next;
  queue->count--;
}

Event peek_event(EventQueue *queue)
{
  return *queue->front;
}

void clear_event_queue(EventQueue *queue)
{
  Event *curr = queue->front;
  while (curr != NULL)
  {
    Event *next = curr->next;
    os_free(curr, sizeof (Event));
    curr = next;
  }

  queue = (EventQueue *) {0};
}