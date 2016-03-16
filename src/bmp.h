#ifndef BMP_H
#define BMP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "msg.h"

// basic data type definitions
typedef unsigned char bool_t;
#define true 1
#define TRUE 1
#define false 0
#define FALSE 0
typedef unsigned char byte_t;

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

typedef struct bitmap_file_header_t {
  byte_t type[2];
  dword_t size;
  word_t reserved1;
  word_t reserved2;
  dword_t offbit;
} bitmap_file_header_t;

#define BITMAP_FILE_HEADER_SIZE (3*sizeof(word_t)+2*sizeof(dword_t))

typedef struct bitmap_info_header_t {
  dword_t size;
  long_t width;
  long_t height;
  word_t planes;
  word_t bit_count;
  dword_t compression;
  dword_t size_image;
  long_t xpels_per_meter;
  long_t ypels_per_meter;
  dword_t color_used;
  dword_t color_important;
} bitmap_info_header_t;

#define BITMAP_INFO_HEADER_SIZE \
    (2*sizeof(word_t)+4*sizeof(long32_t)+5*sizeof(dword_t))

typedef struct bitmap_t {
  bitmap_file_header_t file_header;
  bitmap_info_header_t info_header;
  size_t color_map_size;
  byte_t *color_map;
  byte_t *color_data;
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
 */
typedef enum {
  BITMAP_BIT_COUNT0    =   0,
  BITMAP_BIT_COUNT1    =   1,
  BITMAP_BIT_COUNT4    =   4,
  BITMAP_BIT_COUNT8    =   8,
  BITMAP_BIT_COUNT16   =   16,
  BITMAP_BIT_COUNT24   =   24,
  BITMAP_BIT_COUNT32   =   32
} bit_count_t;

/*** Compression types
 *	RGB:	An uncompressed format.
 *
 *	RLE8:	A run-length encoded (RLE) format for
 *			bitmaps with 8 bpp. The compression format
 *			is a 2-byte format consisting of a count
 *			byte followed by a byte containing a
 *			color index.
 *
 *	RLE4:	An RLE format for bitmaps with 4 bpp.
 *			The compression format is a 2-byte format
 *			consisting of a count byte followed by two
 *			word-length color indexes.
 *
 *	BITFIELDS:	Specifies that the bitmap is not compressed
 *				and that the color table consists of three
 *				DWORD color masks that specify the red, green,
 *				and blue components, respectively, of each
 *				pixel. This is valid when used with 16-
 *				and 32-bpp bitmaps.
 *
 * JPEG:	Indicates that the image is a JPEG image.
 *
 * PNG:		Indicates that the image is a PNG image.
 */

// TODO
// only support RGB for now
typedef enum {
  BITMAP_COMPRESSION_RGB         =   0,
  BITMAP_COMPRESSION_RLE8        =   0,
  BITMAP_COMPRESSION_RLE4        =   0,
  BITMAP_COMPRESSION_BITFILEDS   =   0,
  BITMAP_COMPRESSION_JPG         =   0,
  BITMAP_COMPRESSION_PNG         =   0
} compression_t;

void bmp_print_file_header(const bitmap_t *bmp);
void bmp_print_info_header(const bitmap_t *bmp);
void bmp_print_color_map(const bitmap_t *bmp);
void bmp_print_color_data(const bitmap_t *bmp);

/* bitmap get functions */
long_t bmp_get_color_map_size(const bitmap_t* bmp);
long_t bmp_get_color_data_size(const bitmap_t* bmp);
long_t bmp_get_image_bit_count(const bitmap_t* bmp);
long_t bmp_get_image_x_pixels_per_meter(const bitmap_t* bmp);
long_t bmp_get_image_y_pixels_per_meter(const bitmap_t* bmp);
long_t bmp_get_image_size(const bitmap_t* bmp);
long_t bmp_get_image_width(const bitmap_t* bmp);
long_t bmp_get_image_height(const bitmap_t* bmp);

void bmp_get_image_file_header(const bitmap_t* bmp, bitmap_file_header_t* fh);
void bmp_get_image_info_header(const bitmap_t* bmp, bitmap_info_header_t* ih);
byte_t* bmp_get_color_data(const bitmap_t* bmp);
void bmp_copy_color_data(const bitmap_t* bmp, byte_t* color_data, size_t *data_size);
void bmp_copy_color_map(const bitmap_t* bmp, byte_t* color_map, size_t *data_size);

/* set functions */
bool_t bmp_set_width(bitmap_t* bmp, const long_t width);
bool_t bmp_set_height(bitmap_t* bmp, const long_t height);
bool_t bmp_set_bit_count(bitmap_t* bmp, const bit_count_t bit_count);
bool_t bmp_set_compression(bitmap_t* bmp, const compression_t compression);
bool_t bmp_set_x_pixel_per_meter(bitmap_t* bmp, const long_t xpels_per_meter);
bool_t bmp_set_y_pixel_per_meter(bitmap_t* bmp, const long_t ypels_per_meter);
bool_t bmp_set_color_used(bitmap_t* bmp, const dword_t color_used);
bool_t bmp_set_color_important(bitmap_t* bmp, const dword_t color_important);
bool_t bmp_set_data(bitmap_t* bmp, const byte_t* data, size_t size);

bitmap_t* bmp_read(const char* const bmp_name);
bitmap_t* bmp_create(const long_t width, const long_t height,
                     word_t bit_count, byte_t* data, const size_t size);
bitmap_t* bmp_produce_copy(const bitmap_t* bmp);
void bmp_destroy(bitmap_t* bmp);
void bmp_write(const bitmap_t* bmp, const char* const bmp_name);

#endif /* end of include guard: BMP_H */
