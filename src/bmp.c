#include "bmp.h"

void bmp_print_file_header(const bitmap_t* bmp) {
  printf("bitmap file header type:\n");
  printf("bitmap file header size: %lu\n", BITMAP_FILE_HEADER_SIZE);
  printf("type: %c%c\n", bmp->file_header.type[0], bmp->file_header.type[1]);
  printf("size: %d\n", bmp->file_header.size);
  printf("reserved1: %d\n", bmp->file_header.reserved1);
  printf("reserved2: %d\n", bmp->file_header.reserved2);
  printf("offbit: %d\n", bmp->file_header.offbit);
}

void bmp_print_info_header(const bitmap_t* bmp) {
  printf("bitmap info header type:\n");
  printf("bitmap info header size: %lu\n", BITMAP_INFO_HEADER_SIZE);
  printf("size: %d\n", bmp->info_header.size);
  printf("width: %u\n", bmp->info_header.width);
  printf("height: %u\n", bmp->info_header.height);
  printf("planes: %d\n", bmp->info_header.planes);
  printf("bit_count: %d\n", bmp->info_header.bit_count);
  printf("compression: %d\n", bmp->info_header.compression);
  printf("size_image: %d\n", bmp->info_header.size_image);
  printf("xpels_per_meter: %u\n", bmp->info_header.xpels_per_meter);
  printf("ypels_per_meter: %u\n", bmp->info_header.ypels_per_meter);
  printf("color_used: %d\n", bmp->info_header.color_used);
  printf("color_important: %d\n", bmp->info_header.color_important);
}

void bmp_print_color_map(const bitmap_t* bmp) {
  size_t i;
  for (i = 0 ; i < bmp->color_map_size ; i ++) {
    printf("%i ", bmp->color_map[i]);
    if (i % 16 == 0) printf("\n");
  }
  printf("\n");
}

void bmp_print_color_data(const bitmap_t* bmp) {
  const size_t color_data_size = bmp_get_color_data_size(bmp);
  size_t i;
  for (i = 0 ; i < color_data_size ; i ++) {
    printf("%i ", bmp->color_data[i]);
    if (i % 16 == 0) printf("\n");
  }
  printf("\n");
}

/* get functions */
long_t bmp_get_color_map_size(const bitmap_t* bmp) {
  if (bmp)
    return bmp->color_map_size;
  return -1;
}

long_t bmp_get_color_data_size(const bitmap_t* bmp) {
  if (bmp)
    return bmp->file_header.size - bmp->file_header.offbit;
  return -1;
}

long_t bmp_get_image_bit_count(const bitmap_t* bmp) {
  if (bmp)
    return bmp->info_header.bit_count;
  return -1;
}

long_t bmp_get_image_x_pixels_per_meter(const bitmap_t* bmp) {
  if (bmp)
    return bmp->info_header.xpels_per_meter;
  return -1;
}

long_t bmp_get_image_y_pixels_per_meter(const bitmap_t* bmp) {
  if (bmp)
    return bmp->info_header.ypels_per_meter;
  return -1;
}

long_t bmp_get_image_size(const bitmap_t* bmp) {
  if (bmp)
    return bmp->file_header.size;
  return -1;
}

long_t bmp_get_image_width(const bitmap_t* bmp) {
  if (bmp)
    return bmp->info_header.width;
  return -1;
}

long_t bmp_get_image_height(const bitmap_t* bmp) {
  if (bmp)
    return bmp->info_header.height;
  return -1;
}

/* set functions */
/*bool_t bmp_set_width(bitmap_t* bmp, long_t width)*/
/*{*/
    /*if (bmp)*/
    /*{*/
        /*size_t orig_row_size = bmp->row_size;*/
        /*size_t new_row_size = _bmp_get_row_size(width,*/
                /*bmp->_info_header._bit_count);*/
        /*size_t new_size = new_row_size * bmp->height;*/
        /*size_t x, y;*/

        /*// update useful fields*/
        /*bmp->width = width;*/
        /*bmp->_info_header._width = width;*/
        /*bmp->_info_header._size_image = new_size;*/
        /*bmp->_file_header._size = new_size + bmp->_file_header._offbit;*/
        /*bmp->row_size = new_row_size;*/
        /*bmp->data_size = new_size;*/

/*#ifdef DEBUG*/
        /*printf("new_row_size: %lu\n", new_row_size);*/
/*#endif*/

        /*void* new_data = malloc(new_size);*/
        /*memset(new_data, 0, new_size);*/

        /*for (y = 0 ; y < bmp->height ; y ++)*/
        /*{*/
            /*for(x = 0 ; x < orig_row_size ; x ++)*/
            /*{*/
                /*((uchar_t*)new_data)[y*new_row_size+x] =*/
                        /*((uchar_t*)bmp->data)[y*orig_row_size+x];*/
            /*}*/
        /*}*/
        /*// free the old data*/
        /*free(bmp->data);*/
        /*bmp->data = new_data;*/

/*#ifdef DEBUG*/
        /*_bmp_print_file_header(&bmp->_file_header);*/
        /*_bmp_print_info_header(&bmp->_info_header);*/
        /*_bmp_print_data(bmp->data, bmp->row_size, bmp->height);*/
/*#endif*/
        /*return true;*/
    /*}*/
    /*else*/
    /*{*/
        /*msg_error("input bitmap null pointer");*/
        /*return false;*/
    /*}*/
/*}*/

/*bool_t bmp_set_height(bitmap_t* bmp, long_t height)*/
/*{*/
	/*if (bmp)*/
	/*{*/
		/*long_t orig_height = bmp->height;*/
		/*size_t new_size = height * bmp->row_size;*/
		/*size_t x, y;*/

		/*// update the fields*/
		/*bmp->height = height;*/
		/*bmp->_info_header._height = height;*/
		/*bmp->_info_header._size_image = new_size;*/
		/*bmp->_file_header._size = new_size +*/
				/*bmp->_file_header._offbit;*/
		/*bmp->data_size = new_size;*/

		/*void* new_data = malloc(new_size);*/
		/*memset(new_data, 0, new_size);*/
		/*for (y = 0 ; y < orig_height ; y ++)*/
		/*{*/
			/*for (x = 0 ; x < bmp->row_size ; x ++)*/
			/*{*/
				/*((uchar_t*)new_data)[y*bmp->row_size+x] =*/
						/*((uchar_t*)bmp->data)[y*bmp->row_size+x];*/
			/*}*/
		/*}*/
		/*// free the old data*/
		/*free(bmp->data);*/
		/*bmp->data = new_data;*/
		/*return true;*/
	/*}*/
	/*else*/
	/*{*/
		/*msg_error("input bitmap null pointer");*/
		/*return false;*/
	/*}*/
/*}*/

/*bool_t bmp_set_x_pixel_per_meter(bitmap_t* bmp, long_t xpels_per_meter)*/
/*{*/
	/*if (bmp)*/
	/*{*/
		/*bmp->_info_header._xpels_per_meter = xpels_per_meter;*/
		/*return true;*/
	/*}*/
	/*else*/
	/*{*/
		/*msg_error("input bitmap null pointer");*/
		/*return false;*/
	/*}*/
/*}*/

/*bool_t bmp_set_y_pixel_per_meter(bitmap_t* bmp, long_t ypels_per_meter)*/
/*{*/
	/*if (bmp)*/
	/*{*/
		/*bmp->_info_header._ypels_per_meter = ypels_per_meter;*/
		/*return true;*/
	/*}*/
	/*else*/
	/*{*/
		/*msg_error("input bitmap null pointer");*/
		/*return false;*/
	/*}*/
/*}*/

/*bool_t bmp_set_color_used(bitmap_t* bmp, dword_t color_used)*/
/*{*/
	/*if (bmp)*/
	/*{*/
		/*bmp->_info_header._color_used = color_used;*/
		/*return true;*/
	/*}*/
	/*else*/
	/*{*/
		/*msg_error("input bitmap null pointer");*/
		/*return false;*/
	/*}*/
/*}*/

/*bool_t bmp_set_color_important(bitmap_t* bmp, dword_t color_important)*/
/*{*/
	/*if (bmp)*/
	/*{*/
		/*bmp->_info_header._color_important = color_important;*/
		/*return true;*/
	/*}*/
	/*else*/
	/*{*/
		/*msg_error("input bitmap null pointer");*/
		/*return false;*/
	/*}*/
/*}*/

/*bool_t bmp_set_data(bitmap_t* bmp, void* data, size_t size)*/
/*{*/
	/*if (bmp)*/
	/*{*/
		/*if (size >= bmp->data_size)*/
		/*{*/
			/*size_t i;*/
			/*for (i = 0 ; i < bmp->data_size ; i ++)*/
			/*{*/
				/*((uchar_t*)bmp->data)[i] = ((uchar_t*)data)[i];*/
			/*}*/
			/*return true;*/
		/*}*/
		/*else*/
		/*{*/
			/*msg_error("input data size not large enough");*/
			/*return false;*/
		/*}*/
	/*}*/
	/*else*/
	/*{*/
		/*msg_error("input bitmap null pointer");*/
		/*return false;*/
	/*}*/
/*}*/


void bmp_get_image_file_header(const bitmap_t* bmp,
                               bitmap_file_header_t* file_header) {
  if (file_header)
    memcpy(file_header, &bmp->file_header, BITMAP_FILE_HEADER_SIZE);
  else
    msg_error("input null pointer");
}

void bmp_get_image_info_header(const bitmap_t* bmp,
                               bitmap_info_header_t* info_header) {
  if (info_header)
    memcpy(info_header, &bmp->info_header, BITMAP_INFO_HEADER_SIZE);
  else
    msg_error("input null pointer");
}

byte_t* bmp_get_color_data(const bitmap_t* bmp) {
  if (bmp)
    return (byte_t *) bmp->color_data;
  else {
    msg_error("input bitmap null pointer");
    return NULL;
  }
}

void bmp_copy_color_data(const bitmap_t* bmp, byte_t* color_data, size_t *data_size) {
  if (color_data)  {
    *data_size = bmp_get_color_data_size(bmp);
    memcpy(color_data, bmp->color_data, *data_size);
  } else msg_error("input null pointer");
}

void bmp_copy_color_map(const bitmap_t* bmp, byte_t* color_map, size_t *data_size) {
  if (color_map)  {
    *data_size = bmp->color_map_size;
    memcpy(color_map, bmp->color_map, *data_size);
  } else msg_error("input null pointer");
}

static size_t bmp_get_row_size(long_t width, bit_count_t bit_count) {
  size_t i, row_size = 0;
  switch (bit_count) {
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

  for (i = 0 ; i < 4 ; i ++) {
    if ((row_size + i) % 4 == 0)
      return row_size + i;
  }
  return row_size;
}

bitmap_t* bmp_read(const char* bmp_name) {
  MSG_IS_NULL_STRING(bmp_name, NULL);

  FILE* file = fopen(bmp_name, "r");
  if (file) {
    bitmap_t* bmp = (bitmap_t*) malloc(sizeof(bitmap_t));
    bmp->color_map = NULL;
    bmp->color_data = NULL;

    /* bitmap file header */
    fread(&bmp->file_header.type, sizeof(byte_t), 2, file);
    fread(&bmp->file_header.size, sizeof(dword_t), 1, file);
    fread(&bmp->file_header.reserved1, sizeof(word_t), 1, file);
    fread(&bmp->file_header.reserved2, sizeof(word_t), 1, file);
    fread(&bmp->file_header.offbit, sizeof(dword_t), 1, file);
    bmp_print_file_header(bmp);

    /* bitmap info header */
    fread(&bmp->info_header.size, sizeof(dword_t), 1, file);
    fread(&bmp->info_header.width, sizeof(long_t), 1, file);
    fread(&bmp->info_header.height, sizeof(long_t), 1, file);
    fread(&bmp->info_header.planes, sizeof(word_t), 1, file);
    fread(&bmp->info_header.bit_count, sizeof(word_t), 1, file);
    fread(&bmp->info_header.compression, sizeof(dword_t), 1, file);
    fread(&bmp->info_header.size_image, sizeof(dword_t), 1, file);
    fread(&bmp->info_header.xpels_per_meter, sizeof(long_t), 1, file);
    fread(&bmp->info_header.ypels_per_meter, sizeof(long_t), 1, file);
    fread(&bmp->info_header.color_used, sizeof(dword_t), 1, file);
    fread(&bmp->info_header.color_important, sizeof(dword_t), 1, file);
    bmp_print_info_header(bmp);

    /* bitmap color map */
    bmp->color_map_size = bmp->file_header.offbit -
          BITMAP_INFO_HEADER_SIZE - BITMAP_FILE_HEADER_SIZE;
    bmp->color_map = (byte_t *) malloc(sizeof(byte_t) * bmp->color_map_size);
    if (fread(bmp->color_map, sizeof(byte_t), bmp->color_map_size, file) !=
        bmp->color_map_size) {
      free(bmp);
      msg_error("fail to read color map");
    }

    /* bitmap color data */
    const size_t color_data_size = bmp->file_header.size - bmp->file_header.offbit;
    bmp->color_data = (byte_t *) malloc(sizeof(byte_t) * color_data_size);
    if (fread(bmp->color_data, sizeof(byte_t), color_data_size, file) !=
        color_data_size) {
      msg_error("fail to read color data");
      free(bmp->color_data);
      free(bmp);
      return NULL;
    }

    return bmp;
  } else {
    msg_error("fail to read file");
  }
  return NULL;
}

bitmap_t* bmp_create(const long_t width, const long_t height,
                     const word_t bit_count, byte_t* data, const size_t size) {
  if (data) {
    size_t i, j;
    bitmap_t* bmp = malloc(sizeof(bitmap_t));
    // bitmap file header
    bmp->file_header.type[0] = 'B';
    bmp->file_header.type[1] = 'M';
    bmp->file_header.size = size + BITMAP_FILE_HEADER_SIZE +
      BITMAP_INFO_HEADER_SIZE;
    bmp->file_header.reserved1 = 0;
    bmp->file_header.reserved2 = 0;
    bmp->file_header.offbit = BITMAP_FILE_HEADER_SIZE +
      BITMAP_INFO_HEADER_SIZE;

    // bitmap info header
    bmp->info_header.size = BITMAP_INFO_HEADER_SIZE;
    bmp->info_header.width = width;
    bmp->info_header.height = height;
    bmp->info_header.planes = 1;
    // use default compression RGB
    bmp->info_header.compression = BITMAP_COMPRESSION_RGB;
    bmp->info_header.bit_count = bit_count;
    bmp->info_header.size_image = 0;
    // use default 0 for x/y pixels per meter
    bmp->info_header.xpels_per_meter = 0;
    bmp->info_header.ypels_per_meter = 0;
    // use default 256 color
    bmp->info_header.color_used = 0;
    // default all color required
    bmp->info_header.color_important = 0;

    // other useful member
    size_t row_size = bmp_get_row_size(width, bmp->info_header.bit_count);

    // copy data into bitmap data
    bmp->color_data = (byte_t *) malloc(row_size * height);
    memset(bmp->color_data, '\0', row_size * height * sizeof(byte_t));
    for (i = 0 ; i < height ; i ++) {
      for (j = 0 ; j < width ; j ++) {
        bmp->color_data[i * width + j] = data[i * width + j];
      }
    }
    return bmp;
  } else {
    msg_error("data null pointer");
    return NULL;
  }
}

bitmap_t* bmp_produce_copy(const bitmap_t* bmp) {
  bitmap_t* copy = (bitmap *) malloc(sizeof(bitmap_t));
  if (bmp) {
    if (copy) {
      memcpy(copy, bmp, sizeof(bitmap_t));
      return copy;
    } else {
      msg_error("fail to malloc new bitmap");
      return NULL;
    }
  } else {
    msg_error("input bitmap null pointer");
    return NULL;
  }
}

void bmp_destroy(bitmap_t* bmp) {
  if (bmp) {
    if (bmp->color_data)
      free(bmp->color_data);
    free(bmp);
  }
}

void bmp_write(const bitmap_t* bmp, const char* const bmp_name) {
  MSG_IS_NULL_STRING(bmp_name, );

  FILE* file = fopen(bmp_name, "wb");
  if (file) {
    if (bmp) {
      /* file header */
      fwrite(&bmp->file_header.type, sizeof(byte_t), 2, file);
      fwrite(&bmp->file_header.size, sizeof(dword_t), 1, file);
      fwrite(&bmp->file_header.reserved1, sizeof(word_t), 1, file);
      fwrite(&bmp->file_header.reserved2, sizeof(word_t), 1, file);
      fwrite(&bmp->file_header.offbit, sizeof(dword_t), 1, file);

      /* info header */
      fwrite(&bmp->info_header.size, sizeof(dword_t), 1, file);
      fwrite(&bmp->info_header.width, sizeof(long_t), 1, file);
      fwrite(&bmp->info_header.height, sizeof(long_t), 1, file);
      fwrite(&bmp->info_header.planes, sizeof(word_t), 1, file);
      fwrite(&bmp->info_header.bit_count, sizeof(word_t), 1, file);
      fwrite(&bmp->info_header.compression, sizeof(dword_t), 1, file);
      fwrite(&bmp->info_header.size_image, sizeof(dword_t), 1, file);
      fwrite(&bmp->info_header.xpels_per_meter, sizeof(long_t), 1, file);
      fwrite(&bmp->info_header.ypels_per_meter, sizeof(long_t), 1, file);
      fwrite(&bmp->info_header.color_used, sizeof(dword_t), 1, file);
      fwrite(&bmp->info_header.color_important, sizeof(dword_t), 1, file);

      const size_t height = bmp->info_header.height;
      const size_t width = bmp_get_row_size(bmp->info_header.width,
                                      bmp->info_header.bit_count);
      const size_t color_data_size = height * width * sizeof(byte_t);
      size_t i;
      /* color map */
      for (i = 0 ; i < bmp->color_map_size ; i ++) {
        fputc(bmp->color_map[i], file);
      }
      /* color data */
      for (i = 0 ; i < color_data_size ; i ++) {
        fputc(bmp->color_data[i], file);
      }

      fclose(file);
    } else {
      msg_error("input bmp null pointer");
    }
  } else {
    msg_error_line("fail to open new file:", 1, bmp_name);
  }
}

