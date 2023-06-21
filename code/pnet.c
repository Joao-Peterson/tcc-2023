struct pnet_t{
    // size
    size_t num_places;
    size_t num_transitions;
    size_t num_inputs;
    size_t num_outputs;

    // maps
    pnet_matrix_t *neg_arcs_map;
    pnet_matrix_t *pos_arcs_map;
    pnet_matrix_t *inhibit_arcs_map;
    pnet_matrix_t *reset_arcs_map;
    pnet_matrix_t *places_init;
    pnet_matrix_t *transitions_delay;
    pnet_matrix_t *inputs_map;
    pnet_matrix_t *outputs_map;

    // validation
    bool valid;

    // net state
    pnet_matrix_t *places;
    pnet_matrix_t *sensitive_transitions;

    // input edges state
    pnet_matrix_t *inputs_last;

    // output values
    pnet_matrix_t *outputs;

    // async
    pnet_callback_t function;
    void *user_data;
    pthread_t thread;
    pthread_mutex_t lock;
    transition_queue_t *transition_to_fire;
};