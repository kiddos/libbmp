#include "bmp.h"

void _bmp_read_file_header(void* content, bitmap_file_header_t* fh)
{
	if (fh)
	{
		uint32_t offset = 0;
		memcpy(&fh->_type, content + offset, sizeof(word_t));

		offset += sizeof(word_t);
		memcpy(&fh->_size, content + offset, sizeof(dword_t));

		offset += sizeof(dword_t);
		memcpy(&fh->_reserved1, content + offset, sizeof(word_t));

		offset += sizeof(word_t);
		memcpy(&fh->_reserved2, content + offset, sizeof(word_t));

		offset += sizeof(word_t);
		memcpy(&fh->_offbit, content + offset, sizeof(dword_t));
	}
	else
	{
		msg_error("bitmap_file_header_t null pointer");
	}
}

void _bmp_write_file_header(bitmap_file_header_t* fh, FILE* file)
{
	if (file)
	{
		fwrite(&fh->_type, sizeof(word_t), 1, file);
		fwrite(&fh->_size, sizeof(dword_t), 1, file);
		fwrite(&fh->_reserved1, sizeof(word_t), 1, file);
		fwrite(&fh->_reserved2, sizeof(word_t), 1, file);
		fwrite(&fh->_offbit, sizeof(dword_t), 1, file);
	}
	else
	{
		msg_error("file null pointer");
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

void _bmp_read_info_header(void* content, bitmap_info_header_t* ih)
{
	if (ih)
	{
		uint32_t offset = 0;
		memcpy(&ih->_size, content + offset, sizeof(dword_t));

		offset += sizeof(dword_t);
		memcpy(&ih->_width, content + offset, sizeof(long32_t));

		offset += sizeof(long32_t);
		memcpy(&ih->_height, content + offset, sizeof(long32_t));

		offset += sizeof(long32_t);
		memcpy(&ih->_planes, content + offset, sizeof(word_t));

		offset += sizeof(word_t);
		memcpy(&ih->_bit_count,
				content + offset, sizeof(word_t));

		offset += sizeof(word_t);
		memcpy(&ih->_compression,
				content + offset, sizeof(dword_t));

		offset += sizeof(dword_t);
		memcpy(&ih->_size_image,
				content + offset, sizeof(dword_t));

		offset += sizeof(dword_t);
		memcpy(&ih->_xpels_per_meter,
				content + offset, sizeof(long32_t));

		offset += sizeof(long32_t);
		memcpy(&ih->_ypels_per_meter,
				content + offset, sizeof(long32_t));

		offset += sizeof(long32_t);
		memcpy(&ih->_color_used,
				content + offset, sizeof(dword_t));

		offset += sizeof(dword_t);
		memcpy(&ih->_color_important,
				content + offset, sizeof(dword_t));
	}
	else
	{
		msg_error("bitmap_info_header_t null pointer");
	}
}

void _bmp_write_info_header(bitmap_info_header_t* ih, FILE* file)
{
	if (file)
	{
		fwrite(&ih->_size, sizeof(dword_t), 1, file);
		fwrite(&ih->_width, sizeof(long_t), 1, file);
		fwrite(&ih->_height, sizeof(long_t), 1, file);
		fwrite(&ih->_planes, sizeof(word_t), 1, file);
		fwrite(&ih->_bit_count, sizeof(word_t), 1, file);
		fwrite(&ih->_compression, sizeof(dword_t), 1, file);
		fwrite(&ih->_size_image, sizeof(dword_t), 1, file);
		fwrite(&ih->_xpels_per_meter, sizeof(long_t), 1, file);
		fwrite(&ih->_ypels_per_meter, sizeof(long_t), 1, file);
		fwrite(&ih->_color_used, sizeof(dword_t), 1, file);
		fwrite(&ih->_color_important, sizeof(dword_t), 1, file);
	}
	else
	{
		msg_error("input file null pointer");
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

void _bmp_read_data(void* src, void* dst, size_t size)
{
	if (src && dst)
	{
		if (dst)
		{
			memcpy(dst, src, size);
		}
		else
		{
			msg_error("null dst pointer");
		}
	}
	else
	{
		msg_error("null src pointer");
	}
}

void _bmp_print_data(void* data, size_t row_size, size_t height)
{
	size_t x, y;
	if (data)
	{
		printf("data:\n");
		for (y = 0 ; y < 1 ; y ++)
		{
			for (x = 0 ; x < row_size ; x ++)
			{
				printf("%4d", ((uchar_t*)data)[(height-y-1)*row_size+x]);
			}
			printf("\n");
		}
		/*for (i = 0 ; i < size * 0.01 ; i ++)*/
		/*{*/
			/*if (i % 30 == 0) printf("\n");*/
			/*printf("%4d", ((uchar_t*)data)[i]);*/
		/*}*/
		/*printf("\n");*/
	}
	else
	{
		msg_error("null data pointer");
	}
}

long_t _bmp_get_data_size(bitmap_file_header_t* fh)
{
	if (fh)
	{
		return fh->_size - BITMAP_FILE_HEADER_SIZE -
				BITMAP_INFO_HEADER_SIZE;
	}
	else
	{
		return 0;
	}
}

long_t _bmp_get_offset_size(bitmap_file_header_t* fh)
{
	if (fh)
	{
		return fh->_offbit - BITMAP_FILE_HEADER_SIZE -
				BITMAP_INFO_HEADER_SIZE;
	}
	else
	{
		return 0;
	}
}

long_t _bmp_get_image_bit_count(bitmap_t* bmp)
{
	if (bmp)
	{
		return bmp->_info_header._bit_count;
	}
	else
	{
		return 0;
	}
}

long_t _bmp_get_image_x_pixels_per_meter(bitmap_t* bmp)
{
	if (bmp)
	{
		return bmp->_info_header._xpels_per_meter;
	}
	else
	{
		return 0;
	}
}

long_t _bmp_get_image_y_pixels_per_meter(bitmap_t* bmp)
{
	if (bmp)
	{
		return bmp->_info_header._xpels_per_meter;
	}
	else
	{
		return 0;
	}
}

long_t bmp_get_image_size(bitmap_t* bmp)
{
	if (bmp)
	{
		return bmp->_file_header._size;
	}
	else
	{
		return 0;
	}
}

long_t bmp_get_image_overhead(bitmap_t* bmp)
{
	if (bmp)
	{
		return bmp->_file_header._offbit;
	}
	else
	{
		return 0;
	}
}

long_t bmp_get_image_width(bitmap_t* bmp)
{
	if (bmp)
	{
		return bmp->_info_header._width;
	}
	else
	{
		return 0;
	}
}

long_t bmp_get_image_height(bitmap_t* bmp)
{
	if (bmp)
	{
		return bmp->_info_header._height;
	}
	else
	{
		return 0;
	}
}

void bmp_get_image_file_header(bitmap_t* bmp, bitmap_file_header_t* fh)
{
	if (fh)
	{
		memcpy(fh, &bmp->_file_header, BITMAP_FILE_HEADER_SIZE);
	}
	else
	{
		msg_error("input null pointer");
	}
}

void bmp_get_image_info_header(bitmap_t* bmp, bitmap_info_header_t* ih)
{
	if (ih)
	{
		memcpy(ih, &bmp->_info_header, BITMAP_INFO_HEADER_SIZE);
	}
	else
	{
		msg_error("input null pointer");
	}
}

uchar_t* bmp_get_image_data(bitmap_t* bmp)
{
	if (bmp)
	{
		return (uchar_t*)bmp->data;
	}
	else
	{
		msg_error("input bitmap null pointer");
		return NULL;
	}
}

void bmp_copy_image_data(bitmap_t* bmp, void* data, size_t data_size)
{
	if (data)
	{
		if (data_size != bmp->_info_header._size_image)
		{
			msg_warning("input size does not match");
		}
		memcpy(data, bmp->data, data_size);
	}
	else
	{
		msg_error("input null pointer");
	}
}

// TODO
// need to implement PNG/JPEG
static size_t _bmp_get_row_size(long_t width, bit_count_t bit_count)
{
	size_t i, row_size = 0;
	switch (bit_count)
	{
	case 0:
		break;
	case 1:
		row_size = width / 8;
		break;
	case 4:
		row_size = width / 2;
		break;
	case 8:
		row_size = width;
		break;
	case 16:
		row_size = width * 2;
		break;
	case 24:
		row_size = width * 3;
		break;
	case 32:
		row_size = width * 4;
		break;
	}

	for (i = 0 ; i < 4 ; i ++)
	{
		if ((row_size + i) % 4 == 0)
			return row_size + i;
	}
	return row_size;
}

bitmap_t* bmp_read(const char* bmp_name)
{
	MSG_IS_NULL_STRING(bmp_name, NULL);

	FILE* file = fopen(bmp_name, "r");
	if (file)
	{
		bitmap_t* bmp = (bitmap_t*) malloc(sizeof(bitmap_t));
		size_t i, x, y;
		char fh_buf[1024] = {'\0'};
		char ih_buf[1024] = {'\0'};

		for (i = 0 ; i < BITMAP_FILE_HEADER_SIZE ; i ++)
		{
			fh_buf[i] = fgetc(file);
#ifdef DEBUG
			printf("%04u ", fh_buf[i]);
#endif
		}
#ifdef DEBUG
		printf("\n");
#endif

		for (i = 0 ; i < BITMAP_INFO_HEADER_SIZE ; i ++)
		{
			ih_buf[i] = fgetc(file);
#ifdef DEBUG
			printf("%04u ", ih_buf[i]);
#endif
		}

		// read file/info header
		_bmp_read_file_header(fh_buf, &bmp->_file_header);
		_bmp_read_info_header(ih_buf, &bmp->_info_header);

#ifdef DEBUG
		printf("\n");
		_bmp_print_file_header(&bmp->_file_header);
		_bmp_print_info_header(&bmp->_info_header);
#endif

		// fill in other useful members
		bmp->width = bmp_get_image_width(bmp);
		bmp->height = bmp_get_image_height(bmp);
		bmp->data_size = bmp_get_image_size(bmp);
		bmp->row_size = _bmp_get_row_size(bmp->width,
				bmp->_info_header._bit_count);
#ifdef DEBUG
		printf("row_size: %lu\n", bmp->row_size);
#endif

		size_t size = _bmp_get_data_size(&bmp->_file_header);
		bmp->data = malloc(size);

		// read data
		for (y = 0 ; y < bmp->height ; y ++)
		{
			for (x = 0 ; x < bmp->row_size ; x ++)
			{
				((uchar_t*)bmp->data)[(bmp->height-y-1)*bmp->row_size+x] =
						fgetc(file);
			}
		}
#ifdef DEBUG
		_bmp_print_data(bmp->data, bmp->row_size, bmp->height);
#endif

		return bmp;
	}
	else
	{
		msg_error("fail to read file");
		return NULL;
	}

}

bitmap_t* bmp_create(long_t width, long_t height, word_t bit_count,
		void* data, size_t size)
{
	if (data)
	{
		size_t i;
		bitmap_t* bmp = malloc(sizeof(bitmap_t));
		// bitmap file header
		bmp->_file_header._type = BITMAP_TYPE;
		bmp->_file_header._size = size + BITMAP_FILE_HEADER_SIZE +
				BITMAP_INFO_HEADER_SIZE;
		bmp->_file_header._reserved1 = 0;
		bmp->_file_header._reserved2 = 0;
		bmp->_file_header._offbit = BITMAP_FILE_HEADER_SIZE +
				BITMAP_INFO_HEADER_SIZE;

		// bitmap info header
		bmp->_info_header._size = BITMAP_INFO_HEADER_SIZE;
		bmp->_info_header._width = width;
		bmp->_info_header._planes = 1;
		// use default compression RGB
		bmp->_info_header._compression = BITMAP_COMPRESSION_RGB;
		bmp->_info_header._bit_count = bit_count;
		bmp->_info_header._size_image = size;
		// use default 0 for x/y pixels per meter
		bmp->_info_header._xpels_per_meter = 0;
		bmp->_info_header._ypels_per_meter = 0;
		// use default 256 color
		bmp->_info_header._color_used = 256;
		// default all color required
		bmp->_info_header._color_important = 0;

		// other useful member
		bmp->data_size = size;
		bmp->width = width;
		bmp->height = height;
		bmp->row_size = _bmp_get_row_size(bmp->width,
				bmp->_info_header._bit_count);

		// copy data into bitmap data
		for (i = 0 ; i < size ; i ++)
		{
			((uchar_t*)bmp->data)[i] = ((uchar_t*) data)[i];
		}
		return bmp;
	}
	else
	{
		msg_error("data null pointer");
		return NULL;
	}
}

bitmap_t* bmp_produce_copy(bitmap_t* bmp)
{
	bitmap_t* copy = malloc(sizeof(bitmap_t));
	if (bmp)
	{
		if (copy)
		{
			memcpy(copy, bmp, sizeof(bitmap_t));
			return copy;
		}
		else
		{
			msg_error("fail to malloc new bitmap");
			return NULL;
		}
	}
	else
	{
		msg_error("input bitmap null pointer");
		return NULL;
	}
}

bool_t bmp_set_width(bitmap_t* bmp, long_t width)
{
	if (bmp)
	{
		size_t orig_row_size = bmp->row_size;
		size_t new_row_size = _bmp_get_row_size(width,
				bmp->_info_header._bit_count);
		size_t new_size = new_row_size * bmp->height;
		size_t x, y;

		// update useful fields
		bmp->width = width;
		bmp->_info_header._width = width;
		bmp->_info_header._size_image = new_size;
		bmp->_file_header._size = new_size + bmp->_file_header._offbit;
		bmp->row_size = new_row_size;
		bmp->data_size = new_size;

#ifdef DEBUG
		printf("new_row_size: %lu\n", new_row_size);
#endif

		void* new_data = malloc(new_size);
		memset(new_data, 0, new_size);

		for (y = 0 ; y < bmp->height ; y ++)
		{
			for(x = 0 ; x < orig_row_size ; x ++)
			{
				((uchar_t*)new_data)[y*new_row_size+x] =
						((uchar_t*)bmp->data)[y*orig_row_size+x];
			}
		}
		// free the old data
		free(bmp->data);
		bmp->data = new_data;

#ifdef DEBUG
		_bmp_print_file_header(&bmp->_file_header);
		_bmp_print_info_header(&bmp->_info_header);
		_bmp_print_data(bmp->data, bmp->row_size, bmp->height);
#endif
		return true;
	}
	else
	{
		msg_error("input bitmap null pointer");
		return false;
	}
}

bool_t bmp_set_height(bitmap_t* bmp, long_t height)
{
	if (bmp)
	{
		long_t orig_height = bmp->height;
		size_t new_size = height * bmp->row_size;
		size_t x, y;

		// update the fields
		bmp->height = height;
		bmp->_info_header._height = height;
		bmp->_info_header._size_image = new_size;
		bmp->_file_header._size = new_size +
				bmp->_file_header._offbit;
		bmp->data_size = new_size;

		void* new_data = malloc(new_size);
		memset(new_data, 0, new_size);
		for (y = 0 ; y < orig_height ; y ++)
		{
			for (x = 0 ; x < bmp->row_size ; x ++)
			{
				((uchar_t*)new_data)[y*bmp->row_size+x] =
						((uchar_t*)bmp->data)[y*bmp->row_size+x];
			}
		}
		// free the old data
		free(bmp->data);
		bmp->data = new_data;
		return true;
	}
	else
	{
		msg_error("input bitmap null pointer");
		return false;
	}
}

void bmp_destroy(bitmap_t* bmp)
{
	if (bmp)
	{
		if (bmp->data)
		{
			free(bmp->data);
		}
		free(bmp);
	}
}

void bmp_write(bitmap_t* bmp, const char* bmp_name)
{
	MSG_IS_NULL_STRING(bmp_name, );

	FILE* file = fopen(bmp_name, "wb");
	if (file)
	{
		if (bmp)
		{
			_bmp_write_file_header(&bmp->_file_header, file);
			_bmp_write_info_header(&bmp->_info_header, file);

			/*size_t data_size = _bmp_get_data_size(&bmp->_file_header);*/
			size_t x, y;

			for (y = 0 ; y < bmp->height ; y ++)
			{
				for (x = 0 ; x < bmp->row_size ; x ++)
				{
					fputc(((uchar_t*)bmp->data)[
							(bmp->height-y-1)*bmp->row_size+x], file);
				}
			}
			/*for (i = 0 ; i < data_size ; i ++)*/
			/*{*/
				/*fputc(((uchar_t*)bmp->data)[i], file);*/
			/*}*/

			fclose(file);
		}
		else
		{
			msg_error("input bmp null pointer");
		}
	}
	else
	{
		msg_error_line("fail to open new file:", 1, bmp_name);
	}
}
