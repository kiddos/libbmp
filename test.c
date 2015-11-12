#include "bmp.h"

int main(int argc, char *argv[])
{
	if (argc != 2)
		return 0;

	/*printf("size of long = %lu\n", sizeof(long long ));*/

	bmp_read(argv[1]);
	return 0;
}
