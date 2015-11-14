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

#define BITMAP_TYPE 19778

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
	size_t data_size;
	long_t width;
	long_t height;
} bitmap_t, bitmap;

/***
 *  BIT_COUNT meaning
 *
 *	reference:
 *	https://msdn.microsoft.com/en-us/library/windows/desktop/dd183376(v=vs.85).aspx
 *
 *	for different values:
 *
 *	0:	The number of bits-per-pixel is specified or
 *		is implied by the JPEG or PNG format.
 *
 *	1:	The bitmap is monochrome, and the bmiColors
 *		member of BITMAPINFO contains two entries.
 *		Each bit in the bitmap array represents a pixel.
 *		If the bit is clear, the pixel is displayed
 *		with the color of the first entry in the bmiColors
 *		table; if the bit is set, the pixel has the
 *		color of the second entry in the table.
 *
 *	4:	The bitmap has a maximum of 16 colors,
 *		and the bmiColors member of BITMAPINFO
 *		contains up to 16 entries. Each pixel in the
 *		bitmap is represented by a 4-bit index
 *		into the color table. For example, if the
 *		first byte in the bitmap is 0x1F, the byte
 *		represents two pixels. The first pixel
 *		contains the color in the second table entry,
 *		and the second pixel contains the color
 *		in the sixteenth table entry.
 *
 *  8:	The bitmap has a maximum of 256 colors,
 *		and the bmiColors member of BITMAPINFO
 *		contains up to 256 entries. In this case,
 *		each byte in the array represents a single pixel.
 *
 * 16:	The bitmap has a maximum of 2^16 colors.
 *		If the biCompression member of the
 *		BITMAPINFOHEADER is BI_RGB, the bmiColors
 *		member of BITMAPINFO is NULL. Each WORD
 *		in the bitmap array represents a single
 *		pixel. The relative intensities of red, green,
 *		and blue are represented with five bits for
 *		each color component. The value for blue is
 *		in the least significant five bits, followed
 *		by five bits each for green and red.
 *		The most significant bit is not used.
 *		The bmiColors color table is used for
 *		optimizing colors used on palette-based devices,
 *		and must contain the number of entries
 *		specified by the biClrUsed member of the
 *		BITMAPINFOHEADER.
 *		If the biCompression member of the
 *		BITMAPINFOHEADER is BI_BITFIELDS, the
 *		bmiColors member contains three DWORD color
 *		masks that specify the red, green, and blue
 *		components, respectively, of each pixel.
 *		Each WORD in the bitmap array represents a
 *		single pixel.
 *		When the biCompression member is BI_BITFIELDS,
 *		bits set in each DWORD mask must be contiguous
 *		and should not overlap the bits of another mask.
 *		All the bits in the pixel do not have to be used.
 *
 * 24:	The bitmap has a maximum of 2^24 colors,
 *		and the bmiColors member of BITMAPINFO is NULL.
 *		Each 3-byte triplet in the bitmap array
 *		represents the relative intensities of blue,
 *		green, and red, respectively, for a pixel.
 *		The bmiColors color table is used for optimizing
 *		colors used on palette-based devices, and must
 *		contain the number of entries specified by the
 *		biClrUsed member of the BITMAPINFOHEADER.
 *
 * 32:	The bitmap has a maximum of 2^32 colors.
 *		If the biCompression member of the BITMAPINFOHEADER
 *		is BI_RGB, the bmiColors member of BITMAPINFO
 *		is NULL. Each DWORD in the bitmap array
 *		represents the relative intensities of blue,
 *		green, and red for a pixel. The value for blue
 *		is in the least significant 8 bits, followed
 *		by 8 bits each for green and red. The high
 *		byte in each DWORD is not used. The bmiColors
 *		color table is used for optimizing colors used
 *		on palette-based devices, and must contain the
 *		number of entries specified by the biClrUsed
 *		member of the BITMAPINFOHEADER.
 *
 *		If the biCompression member of the BITMAPINFOHEADER
 *		is BI_BITFIELDS, the bmiColors member contains
 *		three DWORD color masks that specify the red,
 *		green, and blue components, respectively,
 *		of each pixel. Each DWORD in the bitmap array
 *		represents a single pixel.
 *
 *		When the biCompression member is BI_BITFIELDS,
 *		bits set in each DWORD mask must be contiguous and
 *		should not overlap the bits of another mask.
 *		All the bits in the pixel do not need to be used.
 *
 */
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
long_t _bmp_get_data_size(bitmap_file_header_t* fh);
long_t _bmp_get_offset_size(bitmap_file_header_t* fh);

long_t _bmp_get_image_bit_count(bitmap_t* bmp);
long_t _bmp_get_image_x_pixels_per_meter(bitmap_t* bmp);
long_t _bmp_get_image_y_pixels_per_meter(bitmap_t* bmp);

long_t bmp_get_image_size(bitmap_t* bmp);
long_t bmp_get_image_overhead(bitmap_t* bmp);
long_t bmp_get_image_width(bitmap_t* bmp);
long_t bmp_get_image_height(bitmap_t* bmp);

void bmp_get_image_file_header(bitmap_t* bmp, bitmap_file_header_t* fh);
void bmp_get_image_info_header(bitmap_t* bmp, bitmap_info_header_t* ih);
void bmp_get_image_data(bitmap_t* bmp, void* data, size_t data_size);

bitmap_t* bmp_read(const char* bmp_name);
bitmap_t* bmp_create(long_t width, long_t height, void* data, size_t size);
void bmp_write(bitmap_t* bmp, const char* bmp_name);

#endif /* end of include guard: BMP_H */
