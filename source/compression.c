#include <string.h>
#include <zlib.h>
#include <stdlib.h>
#include <stdio.h>

#include "logging.h"
#include "compression.h"

/* Limit of a 21-bit unsigned integer... */
#define MAX_PACKET_SIZE 2097152

/* Check if a Minecraft packet is compressed or not... */
int is_compressed_packet(unsigned char* buffer) {
    if (buffer[0] <= 0 || buffer[1] != 0) {
        /* Packet is not compressed if the packet length is 0 or the packet ID is not 0 */
        return 0;
    }
    
    unsigned char compression_flag = buffer[2];
    
    /* Check if the compression flag is set */
    return compression_flag == 0x01;
}

/* Compress a Minecraft packet... */
int compress_packet(unsigned char* inbuf, int inlen, unsigned char* outbuf, int outlen) {
    z_stream stream;
    int ret;

    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;

    ret = deflateInit(&stream, Z_DEFAULT_COMPRESSION);
    if (ret != Z_OK) {
        sendf(LOG_ERROR, "The function `deflateInit` from zlib failed: %d\n", ret);
        return -1;
    }

    stream.next_in = inbuf;
    stream.avail_in = inlen;
    stream.next_out = outbuf;
    stream.avail_out = outlen;

    ret = deflate(&stream, Z_FINISH);
    if (ret != Z_STREAM_END) {
        sendf(LOG_ERROR, "The function `deflate` from zlib failed: %d\n", ret);
        deflateEnd(&stream);
        return -1;
    }

    deflateEnd(&stream);
    return stream.total_out;
}

/* Decompress a Minecraft packet... */
int decompress_packet(unsigned char *input_buffer, int input_length, unsigned char *output_buffer) {
    z_stream zstream;
    int result;

    // Initialize zlib stream
    zstream.zalloc = Z_NULL;
    zstream.zfree = Z_NULL;
    zstream.opaque = Z_NULL;
    zstream.avail_in = input_length;
    zstream.next_in = input_buffer;
    zstream.avail_out = MAX_PACKET_SIZE;
    zstream.next_out = output_buffer;

    // Initialize inflate
    result = inflateInit(&zstream);
    if (result != Z_OK) {
        sendf(LOG_ERROR, "The `inflateInit` function from zlib failed...\n");
        return -1;
    }

    // Decompress the data
    result = inflate(&zstream, Z_FINISH);
    if (result != Z_STREAM_END) {
        sendf(LOG_ERROR, "The `inflate` function from zlib failed...\n");
        inflateEnd(&zstream);
        return -1;
    }

    // Clean up
    result = inflateEnd(&zstream);
    if (result != Z_OK) {
        sendf(LOG_ERROR, "The `inflateEnd` function from zlib failed: %s\n", zstream.msg);
        return -1;
    }

    return zstream.total_out;
}