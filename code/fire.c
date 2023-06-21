// transitions that are sensibilized and got the event 
pnet_matrix_t *transitions_able_to_fire = pnet_matrix_and(input_event_transitions, pnet->sensitive_transitions);

// fire transitions
for(size_t transition = 0; transition < pnet->num_transitions; transition++){
    if(transitions_able_to_fire->m[0][transition] == 1){                        // firable transition
        if(
            (pnet->transitions_delay == NULL) ||                                // not timed
            (
                (pnet->transitions_delay != NULL) &&                            // timed 
                (pnet->transitions_delay->m[0][transition] == 0)                // but instant
            )
        ){
            // move and callback
            pnet_move(pnet, transition);        
            if(pnet->function != NULL) pnet->function(pnet, transition, pnet->user_data);
            break;                                                              // only one instant transitions
        }
        else{
            // add to queue
            transition_queue_push(pnet->transition_to_fire, transition, pnet->transitions_delay->m[0][transition]);
        }

    }
}