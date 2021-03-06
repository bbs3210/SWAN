#include <stdint.h>
#include <stdio.h>
#include <wbswan/wbswan.h>
#include <time.h>

int wbswan64_test(int weak_or_strong, enum swan_cipher_config_t cfg);


int main()
{
    int weak_or_strong = 0;

    wbswan64_test(weak_or_strong, swan_cfg_B64_K128);
    wbswan64_test(!weak_or_strong, swan_cfg_B64_K128);

    wbswan64_test(weak_or_strong, swan_cfg_B64_K256);
    wbswan64_test(!weak_or_strong, swan_cfg_B64_K256);




    return 0;
}