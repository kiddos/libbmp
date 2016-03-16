#include "../src/bmp.h"

int main(int argc, char *argv[]) {
  bitmap_t* bmp1 = bmp_read("test.bmp");
  printf("\n");
  bitmap_t* bmp2 = bmp_read("lena512.bmp");
  bmp_write(bmp2, "lena512-2.bmp");
  bmp_destroy(bmp1);
  bmp_destroy(bmp2);
  return 0;
}
