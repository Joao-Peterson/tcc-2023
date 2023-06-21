// run for every input given
for(size_t input = 0; input < pnet->num_inputs; input++){
    // check for pos edges
    if(pnet->inputs_last->m[0][input] == 0 && inputs->m[0][input] == 1){
        edges->m[0][input] = pnet_event_pos_edge;
    }
    // check for neg edges
    else if(pnet->inputs_last->m[0][input] == 1 && inputs->m[0][input] == 0){
        edges->m[0][input] = pnet_event_neg_edge;
    }
}

// store last inputs
pnet_matrix_copy(pnet->inputs_last, inputs);