#pragma pack(push,1)
typedef struct{
    char magic[4]; 
    uint16_t version;
    uint8_t valid;
    uint8_t matrix_size;
    uint32_t size;
    uint32_t crc32;
    uint32_t num_places;
    uint32_t num_transitions;
    uint32_t num_inputs;
    uint32_t num_outputs;

    uint32_t neg_arcs_map_size;
    uint8_t neg_arcs_map_first_byte;
    /**
     * ...
     * neg_arcs_map
     * pos_arcs_map
     * inhibit_arcs_map
     * reset_arcs_map
     * places_init
     * transitions_delay
     * inputs_map
     * outputs_map
     * places
     * sensitive_transitions
     * outputs
     * inputs_last
    */
}pnet_file_header_t;
#pragma pack(pop)
