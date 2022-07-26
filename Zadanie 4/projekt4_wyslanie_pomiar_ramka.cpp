#include <windows.h>
#include <iostream>
#include <ctime>
#include <cstdio>
#include <fstream>
#include <vector>
#include <numeric>
#include <chrono>



int main()
{   static DCB dcb;
static HANDLE hNumPort;
DWORD dwBytesRead = 0;
static DWORD RS_ile;
double  czas_blok[200]= {0};
time_t start=0, stop=0;


for (int i =0; i<200; i++)
    {   czas_blok[i]= 0;
    }

unsigned char szBuff[8 + 1] = {0x01,0x03,0x00,0x00,0x00,0x02,0xC4,0x0B};

hNumPort = CreateFile("COM1", GENERIC_WRITE |GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);

if(hNumPort==INVALID_HANDLE_VALUE)
    { if(GetLastError()==ERROR_FILE_NOT_FOUND)
        { std::cout << "BRAK PROTU" << std::endl;//serial port does not exist. Inform user.
        }
    std::cout << "BLAD" << std::endl;//some other error occurred. Inform user.
    }


dcb.DCBlength = sizeof(dcb);

dcb.BaudRate = CBR_115200;
dcb.fParity = TRUE;
dcb.Parity = NOPARITY;
dcb.StopBits = ONESTOPBIT;
dcb.ByteSize = 8;

dcb.fDtrControl = DTR_CONTROL_ENABLE;
dcb.fRtsControl = RTS_CONTROL_ENABLE;

dcb.fOutxCtsFlow = FALSE;
dcb.fOutxDsrFlow = FALSE;
dcb.fDsrSensitivity = FALSE;
dcb.fAbortOnError = FALSE;
dcb.fOutX = FALSE;
dcb.fInX = FALSE;
dcb.fErrorChar = FALSE;
dcb.fNull = FALSE;

SetCommState(hNumPort, &dcb);   //sprawdza czy port jest dostepny
    std::cout << "Jest dostep: " << SetCommState(hNumPort, &dcb) << std::endl;

    //std::cout.setf( std::ios::fixed );

    for (int j = 0; j<200; j++)
        {//Sleep(10);

        /*auto start = std::chrono::steady_clock::now(); //pomiar z chrono

        //for (int a = 0; a<100; a++)
        //{ WriteFile(hNumPort, szBuff, 8, &RS_ile, NULL);}
        WriteFile(hNumPort, szBuff, 8, &RS_ile, NULL);
        Sleep(200);

        auto finish = std::chrono::steady_clock::now();
        double elapsed_seconds = std::chrono::duration_cast<
        std::chrono::duration<double> >(finish - start).count();

        czas_blok[j] = ((elapsed_seconds*1000)-200)/8 ; //pomiar chrono koniec*/

        start = clock();

        for (int a = 0; a<100; a++)
        { WriteFile(hNumPort, szBuff, 8, &RS_ile, NULL);}

        //if(!WriteFile(hNumPort, szBuff, 8, &RS_ile, NULL)){//error occurred. Report to user.
         //   }

        //Sleep(10);

        stop = clock();
        double diff = stop-start;

        //czas_blok[j] = ((diff/CLOCKS_PER_SEC*1000)-00)/8;  //na ms *1000
        czas_blok[j] = ((diff*1000000/CLOCKS_PER_SEC))/100/8;  //na ms *1000, /10 bo 10 bitow

        //std::cout << " " << std::endl;
        //std::cout << "Czas 1 wyslania bajtu (srednia z bloku 100 bajtowego): " << czas_blok[j] << "ms "  << std::endl;
    }

    CloseHandle(hNumPort);

    std::cout.setf( std::ios::fixed );
    for(int i = 0; i<200; i++){
    std::cout << "Czas wyslania 1 bajtu: " << czas_blok[i] << "ms "  << std::endl;
    }

	std::ofstream zapis("dane.txt");

	for(int i = 0; i<200; i++){
    zapis <<  czas_blok[i] <<  std::endl;
    }

	zapis.close(); //obowiązkowo należy zamknąć plik

    system("pause");
    return(0);
}
