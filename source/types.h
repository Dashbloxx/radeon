#pragma once

typedef struct {
    int x: 26;
    int y: 12;
    int z: 26;
} coordinate_t;

typedef unsigned long encoded_coordinate_t;

typedef unsigned char uuid_t[16];

encoded_coordinate_t encode_coordinates(coordinate_t *coordinates);
coordinate_t decode_coordinates(encoded_coordinate_t encoded_coordinates);
unsigned int readvarint(unsigned char *data, int *offset);