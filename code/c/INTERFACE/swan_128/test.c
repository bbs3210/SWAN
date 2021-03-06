#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "swan128.h"
#define TEST 100000

void dump(const uint8_t *li, int len)
{
    int line_ctrl = 16;
    int i;
    for (i = 0; i < len; i++)
    {
        printf("%02X", (*li++));
        if ((i + 1) % line_ctrl == 0)
        {
            printf("\n");
        }
        else
        {
            printf(" ");
        }
    }
}
uint64_t start_rdtsc()
{
    uint32_t cycles_high, cycles_low;
    __asm__ volatile(
        "CPUID\n\t"
        "RDTSC\n\t"
        "mov %%edx, %0\n\t"
        "mov %%eax, %1\n\t"
        : "=r"(cycles_high), "=r"(cycles_low)::"%rax", "%rbx", "%rcx", "%rdx");
    return ((uint64_t)cycles_low) | (((uint64_t)cycles_high) << 32);
}

uint64_t end_rdtsc()
{
    uint32_t cycles_high, cycles_low;
    __asm__ volatile(
        "RDTSCP\n\t"
        "mov %%edx, %0\n\t"
        "mov %%eax, %1\n\t"
        "CPUID\n\t"
        : "=r"(cycles_high), "=r"(cycles_low)::"%rax", "%rbx", "%rcx", "%rdx");
    return ((uint64_t)cycles_low) | (((uint64_t)cycles_high) << 32);
}
int main()
{
    uint64_t begin;
    uint64_t end;
    uint64_t ans = 0;
    int i;
    uint16_t subkey[128][4] = {0};
    unsigned char in[16] = {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0, 0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0};
    unsigned char out[16];
    unsigned char key[32] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    ;

    
    printf("--------------------SWAN-128block-128keysize--------------------\n");
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        Key_Schedule(key, 128, 1, subkey);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("\n key_schedule for keysize 128 cost %llu CPU cycles\n", (ans) / TEST);
  
    printf("the plaintext\n");
    dump(in, sizeof(in));
    printf("\n");
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        Crypt_Enc_Block(in, 128, out, 128, subkey, KEY128);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("the ciphertext\n");
    dump(out, sizeof(out));
    printf("\nSWAN128K128 encrypt cost %llu CPU cycles\n", (ans) / TEST);
    begin = start_rdtsc();
    for (i= 0; i < TEST; i++)
    {
        Crypt_Dec_Block(out, 128, in, 128, subkey, KEY128);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("the plaintext\n");
    dump(in, sizeof(in));
    printf("\nSWAN128K128 decrypt cost %llu CPU cycles\n", (ans) / TEST);
    printf("--------------------SWAN-128block-256keysize--------------------\n");
    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        Key_Schedule(key, 256, 1, subkey);
    }
    end = end_rdtsc();
    ans = (end - begin);

    printf("\n key_schedule for keysize 256 cost %llu CPU cycles\n", (ans) / TEST);
    printf("the plaintext\n");
    dump(in, sizeof(in));
    printf("\n");

    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        Crypt_Enc_Block(in, 128, out, 128, subkey, KEY256);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("the ciphertext\n");
    dump(out, sizeof(out));
    printf("\nSWAN128K256 encrypt cost %llu CPU cycles\n", (ans) / TEST);


    begin = start_rdtsc();
    for (i = 0; i < TEST; i++)
    {
        Crypt_Dec_Block(in, 128, out, 128, subkey, KEY256);
    }
    end = end_rdtsc();
    ans = (end - begin);
    printf("the plaintext\n");
    dump(in, sizeof(in));
    printf("\nSWAN128K256 decrypt cost %llu CPU cycles\n", (ans) / TEST);

    
    printf("round test-swan128-128:\n");
    Key_Schedule(key, 128, 1, subkey);
    Crypt_Enc_Block_Round(in, 128, out, 128, subkey, 128, 2);
    dump(out, sizeof(out));
    printf("\nround test-swan128-256:\n");
    Key_Schedule(key, 256, 1, subkey);
    Crypt_Enc_Block_Round(in, 128, out, 128, subkey, 256, 2);
    dump(out, sizeof(out));
    printf("\n");

    return 0;
}
