queue_node_t *node = NULL;
for(node = queue->q->last; node != NULL; node = node->prev){
	transition_t node_value = queue_value(node, transition_t);

	if(node_value.transition == tran_data.transition){
		queue_unlock();
		free(tran_node);
		free(tran);
		return;
	}
	
	if(
		(tran_data.start + tran_data.delay) <
		(node_value.start + node_value.delay) 
	){
		tran_node->prev = node;
		tran_node->next = node->next;

		if(node->next != NULL) 
			node->next->prev = tran_node;
		
		node->next = tran_node;
		
		if(queue->q->last == node)
			queue->q->last = tran_node;

		queue->q->size++;
		break;
	}
}

if(node == NULL){
	node = queue->q->first;
	queue->q->first = tran_node;
	tran_node->next = node;
	node->prev = tran_node;
}