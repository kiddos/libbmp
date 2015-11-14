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

		/*memcpy(header, content, sizeof(bitmap_file_header_t));*/
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
		/*memcpy(info_header, content, sizeof(bitmap_info_header_t));*/
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

void _bmp_read_data(void* content, void* dst, size_t size)
{
	// TODO
	// might have order issue
	memcpy(dst, content, size);
}

void _bmp_print_data(void* dst, size_t size)
{
	size_t i;
	printf("data:\n");
	for (i = 0 ; i < size *.1 ; i ++)
	{
		printf("%4d", ((unsigned char*)dst)[i]);
	}
	printf("\n");
}

long_t _bmp_get_data_size(bitmap_file_header_t* fh)
{
	return fh->_size - fh->_offbit;
}

long_t bmp_get_image_size(bitmap_t* bmp)
{
	return bmp->_file_header._size;
}

long_t bmp_get_image_overhead(bitmap_t* bmp)
{
	return bmp->_file_header._offbit;
}

long_t bmp_get_image_width(bitmap_t* bmp)
{
	return bmp->_info_header._width;
}

long_t bmp_get_image_height(bitmap_t* bmp)
{
	return bmp->_info_header._height;
}

long_t _bmp_get_image_bit_count(bitmap_t* bmp)
{
	return bmp->_info_header._bit_count;
}

long_t _bmp_get_image_x_pixels_per_meter(bitmap_t* bmp)
{
	return bmp->_info_header._xpels_per_meter;
}

long_t _bmp_get_image_y_pixels_per_meter(bitmap_t* bmp)
{
	return bmp->_info_header._xpels_per_meter;
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

void bmp_get_image_data(bitmap_t* bmp, void* data, size_t data_size)
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

bitmap_t* bmp_read(const char* bmp_name)
{
	FILE* file = fopen(bmp_name, "r");
	if (file)
	{
		bitmap_t* bmp = (bitmap_t*) malloc(sizeof(bitmap_t));
		size_t i;
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
#ifdef DEBUG
		printf("\n");
#endif

		// read file/info header
		_bmp_read_file_header(fh_buf, &bmp->_file_header);
		_bmp_read_info_header(ih_buf, &bmp->_info_header);

#ifdef DEBUG
		_bmp_print_file_header(&bmp->_file_header);
		_bmp_print_info_header(&bmp->_info_header);
#endif

		size_t size = _bmp_get_data_size(&bmp->_file_header);
		bmp->data = malloc(size);

		// read data
		for (i = 0 ; i < size ; i ++)
		{
			((unsigned char*)bmp->data)[i] = fgetc(file);
		}

#ifdef DEBUG
		_bmp_print_data(bmp->data, size);
#endif

		return bmp;
	}
	else
	{
		msg_error("fail to read file");
		return NULL;
	}

}

void bmp_write(bitmap_t* bmp, const char* bmp_name)
{
	FILE* file = fopen(bmp_name, "wb");
	if (file)
	{
		if (bmp)
		{
			_bmp_write_file_header(&bmp->_file_header, file);
			_bmp_write_info_header(&bmp->_info_header, file);

			size_t data_size = _bmp_get_data_size(&bmp->_file_header);
			size_t i;
			for (i = 0 ; i < data_size ; i ++)
				fputc(((unsigned char*)bmp->data)[i], file);

			fclose(file);
		}
		else
		{
			msg_error("input bmp null pointer");
		}
	}
	else
	{
		msg_error("fail to open new file");
	}
}
