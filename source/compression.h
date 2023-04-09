#pragma once

int is_compressed_packet(unsigned char* buffer);
int compress_packet(unsigned char* inbuf, int inlen, unsigned char* outbuf, int outlen);
int decompress_packet(unsigned char *input_buffer, int input_length, unsigned char *output_buffer);