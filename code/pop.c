int now = CLOCK_TO_MS(clock());

transition_t node_value = queue_value(queue->q->last, transition_t);
if((now - node_value.start) >= node_value.delay){
	*transition = node_value;

	queue_node_t *node = queue->q->last;
	queue->q->last = node->prev;

	if(node->prev != NULL)
		node->prev->next = NULL;

	queue->q->size--;

	if(queue->q->first == node)
		queue->q->first = NULL;

	free(node->value);
	free(node);
	
	queue_unlock();
	return true;
}