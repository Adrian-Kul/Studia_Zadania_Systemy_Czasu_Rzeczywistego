#include <stdio.h>
#include <stdint.h>

uint16_t can_crc_next(uint16_t crc, uint8_t data)
{
    uint8_t i, j;

    crc ^= (uint16_t)data << 7;

    for (i = 0; i < 8; i++) {
        crc <<= 1;
        if (crc & 0x8000) {
            crc ^= 0xc599;
        }
    }

    return crc & 0x7fff;
}

int main()
{
    int i;
    uint8_t data[] = {0x02, 0xAA, 0x80};    //dane wpisane recznie
    uint16_t crc;

    crc = 0;

    for (i = 0; i < sizeof(data); i++) {
        crc = can_crc_next(crc, data[i]);
    }

    printf("%x\n", crc);
}
