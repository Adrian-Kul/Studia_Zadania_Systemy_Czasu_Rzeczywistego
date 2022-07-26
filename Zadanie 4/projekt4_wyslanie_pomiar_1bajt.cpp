#include <windows.h>
#include <iostream>
#include <ctime>
#include <cstdio>
#include <fstream>


int main()
{   static DCB dcb;
static HANDLE hNumPort;
static char lpBuffor_read[2], lpBuffor_write[2];
static DWORD RS_ile;
//DWORD dwBytesRead = 0;
unsigned int liczba = 0;
double czas, czas_blok[200];
time_t czasStart;

/*char szBuff[100 + 1] = {0xC4};
for (int aaa =0; aaa<101; aaa++)
{ szBuff[aaa] = 0xC4;
}*/

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

    for (int j = 0; j<200; j++){

    czasStart = clock();

    for (int i = 0; i<200; i++){
        strcpy(lpBuffor_write, "Ä");     // Niech to bedzie przykladowe polecenie dla urzadzenia
        WriteFile(hNumPort, lpBuffor_write, 1, &RS_ile, 0);    //zapisanie wiadomosci do "zmiennej portu" - wyslanie
    }
        //if(!WriteFile(hNumPort, szBuff, 100, &dwBytesRead, NULL)){//error occurred. Report to user.
        //}

    czas_blok[j] = ((clock()- czasStart)*1000./CLOCKS_PER_SEC)/200;

    //Sleep(50);
    }

    CloseHandle(hNumPort);

    std::cout.setf( std::ios::fixed );
    for(int i = 0; i<200; i++){
    std::cout << "Czas 1 wyslania bajtu (srednia z bloku 200 bajtowego): " << czas_blok[i] << "ms "  << std::endl;
    }

	std::ofstream zapis("dane.txt");

	for(int i = 0; i<200; i++){
    zapis <<  czas_blok[i] <<  std::endl;
    }

	zapis.close(); //obowiazkowo nalezy zamknac plik

    system("pause");
    return(0);
}
