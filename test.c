#include "bmp.h"

int main(int argc, char *argv[])
{
	if (argc != 2)
		return 0;

	/*printf("size of long = %lu\n", sizeof(long long ));*/

	unsigned char file_header[sizeof(bitmap_file_header_t)];
	unsigned char info_header[sizeof(bitmap_info_header_t)];
	unsigned int i;
	FILE* file = fopen(argv[1], "r");

	for (i = 0 ; i < BITMAP_FILE_HEADER_SIZE ; i ++)
	{
		file_header[i] = fgetc(file);
		printf("%04u ", file_header[i]);
	}
	printf("\n");

	for (i = 0 ; i < BITMAP_INFO_HEADER_SIZE ; i ++)
	{
		info_header[i] = fgetc(file);
		printf("%04u ", info_header[i]);
	}
	printf("\n");

	bitmap_file_header_t fh;
	bitmap_info_header_t ih;
	_bmp_read_file_header(file_header, &fh);
	_bmp_print_file_header(&fh);
	_bmp_read_info_header(info_header, &ih);
	_bmp_print_info_header(&ih);
	return 0;
}
