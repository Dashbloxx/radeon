#include <stdlib.h>

#include "types.h"

encoded_coordinate_t encode_coordinates(coordinate_t *coordinates) {
    return ((encoded_coordinate_t)(coordinates->x & 0x3FFFFFF) << 38) | ((encoded_coordinate_t)(coordinates->z & 0x3FFFFFF) << 12) | ((encoded_coordinate_t)(coordinates->y & 0xFFF));
}

/* Return decoded coordinates... */
coordinate_t decode_coordinates(encoded_coordinate_t encoded_coordinates) {
    coordinate_t coordinates;
    coordinates.x = (int)(encoded_coordinates >> 38) & 0x3FFFFFF;
    coordinates.z = (int)(encoded_coordinates >> 12) & 0x3FFFFFF;
    coordinates.y = (int)encoded_coordinates & 0xFFF;
    return coordinates;
}

unsigned int readvarint(unsigned char *data, int *offset) {
    int numRead = 0;
    unsigned int result = 0;
    unsigned char read;
    do
    {
        read = data[*offset + numRead];
        result |= (read & 0x7F) << (7 * numRead);
        numRead++;
    } while ((read & 0x80) != 0);

    *offset += numRead;
    return result;
}
