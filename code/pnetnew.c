pnet_t *pnet = pnet_new(
    pnet_arcs_map_new(1,2,
        -1,
            0
    ),
    pnet_arcs_map_new(1,2,
            0,
            1
    ),
    NULL,
    NULL,
    pnet_places_init_new(2,
        1, 0
    ),
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
);