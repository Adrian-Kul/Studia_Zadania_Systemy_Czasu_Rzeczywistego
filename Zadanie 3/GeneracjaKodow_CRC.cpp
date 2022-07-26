#include <stdio.h>
#include <iostream>
#include <cstring>
#include <ctime>
#include <windows.h>
#include <bitset>
#include <string>
#include <sstream>
#include <climits>
#include <stdlib.h>
#include <math.h>
#include <utility> // dla std::forward

using namespace std;

unsigned short CRC(unsigned char *pMessage, unsigned int NumberOfBytes)
{
register unsigned short reg16 = 0xFFFF; // Zaladowanie do 16-bits rejestru wartosci 0xFFFF
unsigned char reg8;
unsigned char i;

while (NumberOfBytes--)
{   //aaa++;
    //aaa = (int)*pMessage;
    //std::cout << "Wpisano: " <<std::hex<< aaa << std::endl;
    //std::cout << "Iteracja: " << aaa << std::endl;
    reg16 ^= *pMessage++;  //XOR z bajtem wiadomosci
    i = 8;

while(i--)
{
    if (reg16 & 0x0001)    //jesli LSB rowne 1
{
    reg16 >>= 1;            //to przesuniecie w prawo
    reg16 ^= 0xA001;        //i XOR z A001(hex)
}
    else
    reg16 >>= 1;            //inaczej przesuniecie bitow w prawo o 1
}
};
reg8 = reg16 >> 8;          //zapisanie poczatku reg16
return (reg16); //ostatni bajt reg16 na poczatek, a koncowka to reg8
}

int main()
{
    unsigned char pMessage[16] = {0};
    unsigned char KOD[16] = {0};
    unsigned int wartosc = 0;
    unsigned char *wsk_kod = (unsigned char*)&wartosc;
    unsigned short Result = 0x0000;
    int N_Bytes = 16;
    int liczba_kodow = 0;

     for (unsigned int i = 0; i < 8000000; i++)
    {   wartosc = i;
        KOD[15] = *wsk_kod;
        KOD[14] = *(wsk_kod+1);
        KOD[13] = *(wsk_kod+2);
        KOD[12] = *(wsk_kod+3);

         for( int j = 0; j < 16; j++ )
                { pMessage[j] = KOD[j];
                }

        /*if(i > 222222222222220)
        {   std::cout << "KOD: " ;
            for( int j = 0; j < 8; j++ )
                { int ccc = pMessage[8+j];
                 std::cout<<std::hex<< ccc << " ";
                }
                std::cout << std::endl;;
        }*/

        Result = CRC(pMessage,N_Bytes);
        for( int j = 0; j < 16; j++ ) //zerowanie pMessage
         {pMessage[j] = 0;}

        /*if (i == 430000)
        {   std::cout << "KOD: " ;
            for( int j = 0; j < 16; j++ )
                { int ccc = KOD[j];
                 std::cout<<std::hex<< ccc << " ";
                }
            std::cout << std::endl;
            std::cout << "CRC: " << Result << " "<< std::endl;
        }*/

        if(Result == 0xA77C)
        {   liczba_kodow++;
            std::cout << "KOD: " ;
            for( int j = 0; j < 16; j++ )
                { int ccc = KOD[j];
                 std::cout<<std::hex<< ccc << " ";
                }
                std::cout << std::endl;
        }

    }

        std::cout << "Dla " << std::dec<<wartosc+1 << " iteracji, otrzymano: "<<liczba_kodow<< " kodow." <<std::endl;

         return(0);
}

