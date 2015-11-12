#ifndef BMP_H
#define BMP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "msg.h"

// basic data type definitions
#if defined(__unix__)
// for unix like
typedef unsigned short word_t;
typedef unsigned int dword_t;
typedef unsigned int uint32_t;
typedef unsigned int long32_t;
typedef long32_t long_t;
#elif defined(__WIN32)
// for windows
typedef unsigned short word_t;
typedef unsigned int dword_t;
typedef unsigned int uint32_t;
typedef unsigned int long32_t;
#endif

typedef struct bitmap_file_header_t
{
	word_t _type;
	dword_t _size;
	word_t _reserved1;
	word_t _reserved2;
	dword_t _offbit;
} bitmap_file_header_t;

#define BITMAP_FILE_HEADER_SIZE (3*sizeof(word_t)+2*sizeof(dword_t))

typedef struct bitmap_info_header_t
{
	dword_t _size;
	long_t _width;
	long_t _height;
	word_t _planes;
	word_t _bit_count;
	dword_t _compression;
	dword_t _size_image;
	long_t _xpels_per_meter;
	long_t _ypels_per_meter;
	dword_t _color_used;
	dword_t _color_important;
} bitmap_info_header_t;

#define BITMAP_INFO_HEADER_SIZE \
		(2*sizeof(word_t)+4*sizeof(long32_t)+5*sizeof(dword_t))

typedef struct bitmap_t
{
	bitmap_file_header_t _file_header;
	bitmap_info_header_t _info_header;
	void* data;
} bitmap_t, bitmap;

typedef enum
{
	BITMAP_BIT_COUNT0    =   0,
	BITMAP_BIT_COUNT1    =   1,
	BITMAP_BIT_COUNT4    =   4,
	BITMAP_BIT_COUNT8    =   8,
	BITMAP_BIT_COUNT16   =   16,
	BITMAP_BIT_COUNT24   =   24,
	BITMAP_BIT_COUNT32   =   32
} bit_count_t;

// TODO
// there should be more compression type
typedef enum
{
	BITMAP_COMPRESSION_RGB         =   0,
	BITMAP_COMPRESSION_RLE8        =   0,
	BITMAP_COMPRESSION_RLE4        =   0,
	BITMAP_COMPRESSION_BITFILEDS   =   0,
	BITMAP_COMPRESSION_JPG         =   0,
	BITMAP_COMPRESSION_PNG         =   0
} compression_t;

void _bmp_read_file_header(void* content, bitmap_file_header_t* fh);
void _bmp_write_file_header(bitmap_file_header_t* fh, FILE* file);
void _bmp_print_file_header(bitmap_file_header_t* header);
void _bmp_read_info_header(void* content, bitmap_info_header_t* ih);
void _bmp_write_info_header(bitmap_info_header_t* ih, FILE* file);
void _bmp_print_info_header(bitmap_info_header_t* header);
void _bmp_read_data(void* content, void* dst, size_t size);
void _bmp_print_data(void* dst, size_t size);
long_t _bmp_get_data_size(bitmap_file_header_t* ih);

long_t bmp_get_image_size(bitmap_t* bmp);
long_t bmp_get_image_overhead(bitmap_t* bmp);
long_t bmp_get_image_width(bitmap_t* bmp);
long_t bmp_get_image_height(bitmap_t* bmp);

long_t _bmp_get_image_bit_count(bitmap_t* bmp);
long_t _bmp_get_image_x_pixels_per_meter(bitmap_t* bmp);
long_t _bmp_get_image_y_pixels_per_meter(bitmap_t* bmp);

void bmp_get_image_file_header(bitmap_t* bmp, bitmap_file_header_t* fh);
void bmp_get_image_info_header(bitmap_t* bmp, bitmap_info_header_t* ih);
void bmp_get_image_data(bitmap_t* bmp, void* data, size_t data_size);

bitmap_t* bmp_read(const char* bmp_name);
void bmp_write(bitmap_t* bmp, const char* bmp_name);

#endif /* end of include guard: BMP_H */
