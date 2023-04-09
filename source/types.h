#pragma once

typedef struct {
    int x: 26;
    int y: 12;
    int z: 26;
} coordinate_t;

typedef unsigned long encoded_coordinate_t;

typedef unsigned char uuid_t[16];