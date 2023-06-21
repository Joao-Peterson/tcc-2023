for(size_t transition = 0; transition < pnet->num_transitions; transition++){
    // set transition to sensibilized
    pnet->sensitive_transitions->m[0][transition] = 1;                                          
    for(size_t place = 0; place < pnet->num_places; place++){

        // check desensibilization
        if(                                                                                     
            // negative arcs
            (
                // when there are negative arcs
                (pnet->neg_arcs_map != NULL) &&                                                 
                // when there is a neg arc for this transition/place
                (pnet->neg_arcs_map->m[place][transition] != 0) &&                              
                // and there is not enough tokens
                ((pnet->neg_arcs_map->m[place][transition] + pnet->places->m[0][place]) < 0)    
            ) ||
            // inhibit arcs          
            (
                // when there are inhibit arcs
                (pnet->inhibit_arcs_map != NULL) &&                                             
                // if there is a inhibit arc
                (pnet->inhibit_arcs_map->m[place][transition] == 1) &&                          
                // and place has token, then do not trigger, otherwise trigger
                (pnet->places->m[0][place] != 0)                                                
            )
        ){
            // desensibilize
            pnet->sensitive_transitions->m[0][transition] = 0;                                  
            break;
        }                                                                        
    }
}