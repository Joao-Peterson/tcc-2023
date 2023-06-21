for(size_t transition = 0; transition < pnet->num_transitions; transition++){
    transitions->m[0][transition] = 0;
    
    // if input map is null all transitions can occurr
    if(pnet->inputs_map == NULL){
        transitions->m[0][transition] = 1;
        continue;
    }
    
    for(size_t input = 0; input < pnet->num_inputs; input++){


        // if event type is none mark as firable, run until the end of inputs
        if(pnet->inputs_map->m[input][transition] == pnet_event_none){
            transitions->m[0][transition] = 1;
        }
        // if the transitions has an event. When a single event is found then this event must be satisfied, 
        // otherwise the transition stay desensibilized, so we exit the loop when we reach it
        else{
            // using the & operator to check edge type, see pnet_event_t for why
            if(pnet->inputs_map->m[input][transition] & edges->m[0][input]){
                transitions->m[0][transition] = 1;
            }
            else{
                transitions->m[0][transition] = 0;
            }

            break;
        }
    }
}