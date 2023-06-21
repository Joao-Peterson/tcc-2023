while(1){
    pthread_testcancel();

    transition_t transition;
    if(transition_queue_pop(pnet->transition_to_fire, &transition)){
        pnet_sense(pnet);
        if(pnet->sensitive_transitions->m[0][transition.transition] == 1){      // re check sensibility
            pnet_move(pnet, transition.transition);                             // FIRE!! move tokens and call callback
            if(pnet->function != NULL) 
                pnet->function(pnet, transition.transition, pnet->user_data);
        }
    }
}
