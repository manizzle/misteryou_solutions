#include <openssl/md5.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static char buffer[2*1024*1024];


int main(int argc, char *argv[])
{
   fread(buffer, 1, 1048568, fopen("pass.txt", "r"));
   
   unsigned char hash[16];
   MD5_CTX md;
   uint32_t k = 0;
   MD5_Init(&md);
   MD5_Update(&md, buffer, 1048512);

   for( k = 0; k < 100000000; k++)
   {
      MD5_CTX m;

      memcpy(&m, &md, sizeof(MD5_CTX));

      uint32_t x = k;

      buffer[1048568 + 7] = '0' + x % 10; x /= 10;
      buffer[1048568 + 6] = '0' + x % 10; x /= 10;
      buffer[1048568 + 5] = '0' + x % 10; x /= 10;
      buffer[1048568 + 4] = '0' + x % 10; x /= 10;
      buffer[1048568 + 3] = '0' + x % 10; x /= 10;
      buffer[1048568 + 2] = '0' + x % 10; x /= 10;
      buffer[1048568 + 1] = '0' + x % 10; x /= 10;
      buffer[1048568 + 0] = '0' + x % 10; x /= 10;

      MD5_Update(&m, buffer + 1048512, 64);
      MD5_Final(hash, &m);

      // 287d3298b652c159e654b61121a858e0 38908896 69880983
      // 6bda098a6f8b133b13ba564c5e96791e1d2f68f9

      if(hash[0] == 0x28 && hash[1] == 0x7d && hash[2] == 0x32)
      {
         printf(" %08u\n", k);
      }
   }
   return 0;
}
