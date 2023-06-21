// for weighted arcs, only if at least one of them is not null
if(pnet->pos_arcs_map != NULL || pnet->neg_arcs_map != NULL){
    
    pnet_matrix_t *weighted_matrix = NULL;
    pnet_matrix_t *pos_weighted_matrix = NULL;
    pnet_matrix_t *neg_weighted_matrix = NULL;

    // extract the values from the arcs for the transition 
    if(pnet->pos_arcs_map != NULL)
        pos_weighted_matrix = pnet_matrix_extract_col(pnet->pos_arcs_map, transition);
    if(pnet->neg_arcs_map != NULL)
        neg_weighted_matrix = pnet_matrix_extract_col(pnet->neg_arcs_map, transition);

    // sum the pos and neg values or returning only the non null maps  
    if(pos_weighted_matrix != NULL && neg_weighted_matrix != NULL){
        weighted_matrix = pnet_matrix_add(pos_weighted_matrix, neg_weighted_matrix);
        pnet_matrix_delete(pos_weighted_matrix);
        pnet_matrix_delete(neg_weighted_matrix);
    }
    else if(neg_weighted_matrix != NULL)
        weighted_matrix = neg_weighted_matrix;
    else
        weighted_matrix = pos_weighted_matrix;
        
    // finnaly adding the difference in tokens for the places, effectly moving the tokens
    pnet_matrix_t *buffer = pnet_matrix_add(places_res, weighted_matrix);
    pnet_matrix_copy(places_res, buffer);
    pnet_matrix_delete(weighted_matrix);
    pnet_matrix_delete(buffer);
}

// for reset arcs
if(pnet->reset_arcs_map != NULL){
    // get places to reset for a given transition        
    pnet_matrix_t *places_reset = pnet_matrix_extract_col(pnet->reset_arcs_map, transition);

    // negate so its a 0 for a place to be reset, that way we can then multiply it with the places element by element, zeroing out the places where needed
    pnet_matrix_t *places_reset_neg = pnet_matrix_neg(places_reset);
    pnet_matrix_delete(places_reset);

    pnet_matrix_t *buffer = pnet_matrix_mul_by_element(places_res, places_reset_neg);
    pnet_matrix_copy(places_res, buffer);

    pnet_matrix_delete(places_reset_neg);
    pnet_matrix_delete(buffer);
}