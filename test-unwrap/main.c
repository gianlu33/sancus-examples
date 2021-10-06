#include <msp430.h>
#include <stdio.h>
#include <sancus/sm_support.h>
#include <sancus_support/sm_io.h>
#include <stdint.h>
#include <string.h>

#define AD_SIZE 4
#define MSG_SIZE 4

int main()
{
    msp430_io_init();
    printf("Hello! %d\n", SANCUS_TAG_SIZE);

    uint8_t key[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    uint8_t ad[] = {0,0,0,0};
    uint8_t data[] = {'c', 'i', 'a', 'o'};
    uint8_t cipher[MSG_SIZE];
    uint8_t tag[SANCUS_TAG_SIZE];
    uint8_t data_decrypted[MSG_SIZE];
    int i;

    if( !sancus_wrap_with_key(key, ad, AD_SIZE, data, MSG_SIZE,
            cipher, tag) ) {
      printf("Error during encryption\n");
      EXIT();
    }

    printf("Encryption succeeded..\n");

    if( !sancus_unwrap_with_key(key, ad, AD_SIZE, cipher, MSG_SIZE,
            tag, data_decrypted) ) {
      printf("Error during decryption\n");
      EXIT();
    }

    printf("Decryption succeeded..\n");

    if(memcmp(data, data_decrypted, MSG_SIZE)) {
      printf("Input buffer differs from decrypted buffer\n");
      EXIT();
    }

    printf("Buffers are equal..\n");

    printf("All done!\n");
    EXIT();
}
