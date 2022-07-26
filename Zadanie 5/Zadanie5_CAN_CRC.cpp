#include <iostream>
#include <sstream>
#include <ctime>
#include <cstring>
#include <math.h>

using namespace std;

unsigned short crc(const void *data, unsigned int data_len)
{
    const unsigned char *d = (const unsigned char *)data;
    unsigned int i;
    bool bit, bit15_bajt, bit15_crc;
    unsigned char c;

    unsigned short crc = 0x0000;
    while (data_len--) {
        c = *d++;
        for (i = 0; i < 8; i++)
        {
            bit15_bajt = (c<<i) & 0x80;
            bit15_crc = crc & 0x4000;
            bit = bit15_bajt ^ bit15_crc;  //XOR 14-bit CRC z bitem wiadomosci
            crc = crc << 1;
            if (bit) {
                crc ^= 0x4599;
            }
            //std::cout <<std::hex<<bit << " " <<(int)crc << endl;
        }
        //std::cout<< std::hex <<crc << endl;;
    }
    return crc & 0x7fff;
}


int main()
{
    unsigned char pMessage[13] = {0};
    char str[25] = {0};
    char buf[] = "aa";
    char znaki_hex[] = "1234567890abcdefABCDEF";
    unsigned short Result = 0x0000;
    unsigned int liczba = 0;
    double czas;
    bool warunek = 0;

    std::cout << "Podaj ramke danych w postaci heksadecymalnej (bez odstepow): ";
    std::cin >> str;
    std::cout << " " << std::endl;
    int N_znaki = strlen(str);
    int N_Bytes = ceil((float)N_znaki/2);

    for (int i = 0; i < N_znaki; i++)
    {   warunek = false;
        for (int j = 0; j < 22; j++)
            {   if(str[i] == znaki_hex[j])
                { warunek = true;
                }
            }
        if(warunek == false)
            {std::cout << "Wpisano niepoprawna ramke danych." << " \n" << std::endl;
             system("pause");
             return(0);
            }
    }

    std::cout << "Wpisano: 0x" << str << std::endl;
    std::cout << "Ilosc bajtow w wpisanej ramce: " << N_Bytes << " \n" << std::endl;

        if(N_Bytes > 12)
        {std::cout << "Wpisano niepoprawna ramke danych." << " \n" << std::endl;
             system("pause");
             return(0);
        }

    std::cout << "Podaj liczbe powtorzen algorytmu wyznaczenia CRC: ";
    std::cin >> liczba;
    std::cout << " " << std::endl;

    for (int i = 0; i < N_znaki; i++)
    {   short a[255];
        buf[0] = str[2*i];
        buf[1] = str[2*i+1];
        std::istringstream iss(buf);
        iss >> std::hex >> a[i];
        pMessage[i] = a[i];
    }

    if(liczba <= 1000000000 && liczba > 0)
    {   time_t czasStart = clock();

        for (int i = 0; i < liczba; i++)
        {   crc(pMessage,N_Bytes);
        }

        czas = (clock()- czasStart)*1000./CLOCKS_PER_SEC;

        Result = crc(pMessage,N_Bytes);
        std::cout << "Wartosc CRC wiadomosci < " << str << " > to: 0x" <<std::hex<< Result << std::endl;
        std::cout << "Czas calkowity: " <<std::dec<< czas << "ms " << std::endl;
        std::cout.setf( std::ios::fixed );
        std::cout << "Czas 1 iteracji: " << czas/liczba << "ms " << " \n" << std::endl;
    }
    else
    {   std::cout << "Wpisano niepoprawna ilosc powtorzen algorytmu." << " \n" << std::endl;
        }

    system("pause");
    return(0);
}

