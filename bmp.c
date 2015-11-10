#include "bmp.h"

void _bmp_read_file_header(void* content, bitmap_file_header_t* header)
{
	if (header)
	{
		uint32_t offset = 0;
		memcpy(&header->_type, content + offset, sizeof(word_t));

		offset += sizeof(word_t);
		memcpy(&header->_size, content + offset, sizeof(dword_t));

		offset += sizeof(dword_t);
		memcpy(&header->_reserved1, content + offset, sizeof(word_t));

		offset += sizeof(word_t);
		memcpy(&header->_reserved2, content + offset, sizeof(word_t));

		offset += sizeof(word_t);
		memcpy(&header->_offbit, content + offset, sizeof(dword_t));

		/*memcpy(header, content, sizeof(bitmap_file_header_t));*/
	}
	else
	{
		fprintf(stderr, "bitmap_file_header_t null pointer\n");
	}
}

void _bmp_print_file_header(bitmap_file_header_t* header)
{
	printf("bitmap_file_header:\n");
	printf("_type: %d\n", header->_type);
	printf("_size: %d\n", header->_size);
	printf("_reserved1: %d\n", header->_reserved1);
	printf("_reserved2: %d\n", header->_reserved2);
	printf("_offbit: %d\n", header->_offbit);
}

void _bmp_read_info_header(void* content, bitmap_info_header_t* info_header)
{
	if (info_header)
	{
		/*memcpy(info_header, content, sizeof(bitmap_info_header_t));*/
		uint32_t offset = 0;
		memcpy(&info_header->_size, content + offset, sizeof(dword_t));

		offset += sizeof(dword_t);
		memcpy(&info_header->_width, content + offset, sizeof(long32_t));

		offset += sizeof(long32_t);
		memcpy(&info_header->_height, content + offset, sizeof(long32_t));

		offset += sizeof(long32_t);
		memcpy(&info_header->_planes, content + offset, sizeof(word_t));

		offset += sizeof(word_t);
		memcpy(&info_header->_bit_count,
				content + offset, sizeof(word_t));

		offset += sizeof(word_t);
		memcpy(&info_header->_compression,
				content + offset, sizeof(dword_t));

		offset += sizeof(dword_t);
		memcpy(&info_header->_size_image,
				content + offset, sizeof(dword_t));

		offset += sizeof(dword_t);
		memcpy(&info_header->_xpels_per_meter,
				content + offset, sizeof(long32_t));

		offset += sizeof(long32_t);
		memcpy(&info_header->_ypels_per_meter,
				content + offset, sizeof(long32_t));

		offset += sizeof(long32_t);
		memcpy(&info_header->_color_used,
				content + offset, sizeof(dword_t));

		offset += sizeof(dword_t);
		memcpy(&info_header->_color_important,
				content + offset, sizeof(dword_t));
	}
}

void _bmp_print_info_header(bitmap_info_header_t* header)
{
	printf("bitmap_info_header_t:\n");
	printf("_size: %d\n", header->_size);
	printf("_width: %u\n", header->_width);
	printf("_height: %u\n", header->_height);
	printf("_planes: %d\n", header->_planes);
	printf("_bit_count: %d\n", header->_bit_count);
	printf("_compression: %d\n", header->_compression);
	printf("_size_image: %d\n", header->_size_image);
	printf("_xpels_per_meter: %u\n", header->_xpels_per_meter);
	printf("_ypels_per_meter: %u\n", header->_ypels_per_meter);
	printf("_color_used: %d\n", header->_color_used);
	printf("_color_important: %d\n", header->_color_important);
}
