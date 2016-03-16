#include "../src/bmp.h"

#define WIDTH 128
#define HEIGHT 128

void init(unsigned char data[WIDTH * HEIGHT * 3]) {
  int i, j;
  for (i = 0 ; i < HEIGHT ; i ++) {
    for (j = 0 ; j < WIDTH ; j ++) {
      if (i == j) {
        data[i * WIDTH * 3 + j * 3] = 255;
      }
    }
  }
}

int main(void) {
  unsigned char data[WIDTH * HEIGHT * 3] = {0};
  memset(data, 60, WIDTH * HEIGHT * 3);
  init(data);
  bitmap_t* custom = bmp_create(128, 128, BITMAP_BIT_COUNT24, data, 128*128*3);
  bmp_write(custom, "custom.bmp");
  printf("custom bitmap:\n");
  bmp_destroy(custom);

  bitmap_t *uv = bmp_read("./uvtemplate.bmp");
  printf("uv bitmap:\n");
  bmp_destroy(uv);
  return 0;
}

#undef WIDTH
#undef HEIGHT

