typedef struct{
    uint32_t x;
    uint32_t y;
    uint8_t first_byte;
}pnet_matrix_header_t;

uint32_t data[] = {
    4, 4,
    0x80000000, 3, 1,
    0x80000001, 0, 64, 3, 1,
    0x80000003, 2, 0x7FFFFFFF, 3, 16
};

pnet_matrix_header_t *header = (pnet_matrix_header_t*)data;
