#include <stdlib.h>
#include "tag36h10.h"

static uint64_t codedata[2320] = {
   0x00000001a42f9469UL,
   0x000000021a48c08dUL,
   0x000000026dfdbc5dUL,
   0x00000002d19b78fbUL,
   0x000000031c5557dfUL,
   0x00000003f2b3d349UL,
   0x00000003e6d4a7a5UL,
   0x000000043d6dfb6dUL,
   0x00000005688d2affUL,
   0x000000054663b474UL,
   0x000000067fd759e4UL,
   0x000000073b196d82UL,
   0x00000007de71c630UL,
   0x00000008492722d4UL,
   0x0000000835407afaUL,
   0x0000000893a6fe16UL,
   0x000000095668d348UL,
   0x00000009c20e37a4UL,
   0x0000000a19bb676cUL,
   0x0000000ad1355c1bUL,
   0x0000000b2ab4ac53UL,
   0x0000000b14f27095UL,
   0x0000000bef6b014dUL,
   0x0000000c9ecbadc7UL,
   0x0000000e1996a6bdUL,
   0x0000000edc588fcbUL,
   0x0000000f26d9d7a1UL,
   0x0000000035e79c1aUL,
   0x00000001644f74a8UL,
   0x00000001bfda85e0UL,
   0x000000020573db2aUL,
   0x000000027614bfd6UL,
   0x00000002daf26b72UL,
   0x0000000332930a98UL,
   0x00000003176c5674UL,
   0x00000003892ad2d0UL,
   0x00000003fd4d26acUL,
   0x00000004b88a1fcaUL,
   0x0000000555b6b579UL,
   0x00000006103880d7UL,
   0x00000006045e58fbUL,
   0x00000006dedf28a3UL,
   0x000000072766f249UL,
   0x00000007e4a0c77fUL,
   0x0000000973ba8e61UL,
   0x0000000965fd5285UL,
   0x00000009d99bd6a9UL,
   0x0000000a221264e6UL,
   0x0000000a1455fccaUL,
   0x0000000a7cb3193eUL,
   0x0000000aead44d92UL,
   0x0000000ad50ac954UL,
   0x0000000b2f0bb19cUL,
   0x0000000cba043aa2UL,
   0x0000000d73d7f6b4UL,
   0x0000000d6d189310UL,
   0x0000000f41278885UL,
   0x00000001c45306afUL,
   0x0000000222b4420bUL,
   0x00000002d70ceeb1UL,
   0x0000000392cb439fUL,
   0x000000045d1179eeUL,
};
apriltag_family_t *tag36h10_create()
{
   apriltag_family_t *tf = calloc(1, sizeof(apriltag_family_t));
   tf->name = strdup("tag36h10");
   tf->h = 10;
   tf->ncodes = 2320;
   tf->codes = codedata;
   tf->nbits = 36;
   tf->bit_x = calloc(36, sizeof(uint32_t));
   tf->bit_y = calloc(36, sizeof(uint32_t));
   tf->bit_x[0] = 1;
   tf->bit_y[0] = 1;
   tf->bit_x[1] = 2;
   tf->bit_y[1] = 1;
   tf->bit_x[2] = 3;
   tf->bit_y[2] = 1;
   tf->bit_x[3] = 4;
   tf->bit_y[3] = 1;
   tf->bit_x[4] = 5;
   tf->bit_y[4] = 1;
   tf->bit_x[5] = 2;
   tf->bit_y[5] = 2;
   tf->bit_x[6] = 3;
   tf->bit_y[6] = 2;
   tf->bit_x[7] = 4;
   tf->bit_y[7] = 2;
   tf->bit_x[8] = 3;
   tf->bit_y[8] = 3;
   tf->bit_x[9] = 6;
   tf->bit_y[9] = 1;
   tf->bit_x[10] = 6;
   tf->bit_y[10] = 2;
   tf->bit_x[11] = 6;
   tf->bit_y[11] = 3;
   tf->bit_x[12] = 6;
   tf->bit_y[12] = 4;
   tf->bit_x[13] = 6;
   tf->bit_y[13] = 5;
   tf->bit_x[14] = 5;
   tf->bit_y[14] = 2;
   tf->bit_x[15] = 5;
   tf->bit_y[15] = 3;
   tf->bit_x[16] = 5;
   tf->bit_y[16] = 4;
   tf->bit_x[17] = 4;
   tf->bit_y[17] = 3;
   tf->bit_x[18] = 6;
   tf->bit_y[18] = 6;
   tf->bit_x[19] = 5;
   tf->bit_y[19] = 6;
   tf->bit_x[20] = 4;
   tf->bit_y[20] = 6;
   tf->bit_x[21] = 3;
   tf->bit_y[21] = 6;
   tf->bit_x[22] = 2;
   tf->bit_y[22] = 6;
   tf->bit_x[23] = 5;
   tf->bit_y[23] = 5;
   tf->bit_x[24] = 4;
   tf->bit_y[24] = 5;
   tf->bit_x[25] = 3;
   tf->bit_y[25] = 5;
   tf->bit_x[26] = 4;
   tf->bit_y[26] = 4;
   tf->bit_x[27] = 1;
   tf->bit_y[27] = 6;
   tf->bit_x[28] = 1;
   tf->bit_y[28] = 5;
   tf->bit_x[29] = 1;
   tf->bit_y[29] = 4;
   tf->bit_x[30] = 1;
   tf->bit_y[30] = 3;
   tf->bit_x[31] = 1;
   tf->bit_y[31] = 2;
   tf->bit_x[32] = 2;
   tf->bit_y[32] = 5;
   tf->bit_x[33] = 2;
   tf->bit_y[33] = 4;
   tf->bit_x[34] = 2;
   tf->bit_y[34] = 3;
   tf->bit_x[35] = 3;
   tf->bit_y[35] = 4;
   tf->width_at_border = 8;
   tf->total_width = 10;
   tf->reversed_border = false;
   return tf;
}

void tag36h10_destroy(apriltag_family_t *tf)
{
   free(tf->bit_x);
   free(tf->bit_y);
   free(tf->name);
   free(tf);
}
