#include <iostream>
#include <cmath>
#include <windows.h>

using namespace std;

int main()
{
    int nombreAChercher=2,
        nombreTeste=9,
        nombresTestes=4;
    int *nombresPremiers;
    bool estPremier=true;
    cout << "Chercheur de nombres premiers" << endl;
    cout << "Nombres premiers à trouver : ";
    cin >> nombreAChercher;
    nombresPremiers=new int[nombreAChercher];
    nombresPremiers[0]=2;
    nombresPremiers[1]=3;
    nombresPremiers[2]=5;
    nombresPremiers[3]=7;
    cout << 2 << endl << 3 << endl;

    LARGE_INTEGER initTime, finalTime, freqTime;
    QueryPerformanceFrequency(&freqTime);
    ///...
    QueryPerformanceCounter(&initTime);

    while(nombresTestes<nombreAChercher) {

        if(!(nombreTeste%3)) {
            estPremier=true;
            for(int j=3;pow(nombresPremiers[j],2)<=nombreTeste;j++) {
                if(!(nombreTeste%nombresPremiers[j])) {
                    estPremier=false;
                    break;
                }
            }
            if(estPremier) {
                nombresPremiers[nombresTestes]=nombreTeste;
                nombresTestes++;
                //cout << nombreTeste << endl;
            }
        }
        nombreTeste+=2;

        if(!(nombreTeste%3)) {
            estPremier=true;
            for(int j=3;pow(nombresPremiers[j],2)<=nombreTeste;j++) {
                if(!(nombreTeste%nombresPremiers[j])) {
                    estPremier=false;
                    break;
                }
            }
            if(estPremier) {
                nombresPremiers[nombresTestes]=nombreTeste;
                nombresTestes++;
                //cout << nombreTeste << endl;
            }
        }
        nombreTeste+=4;

        if(!(nombreTeste%3)) {
            estPremier=true;
            for(int j=3;pow(nombresPremiers[j],2)<=nombreTeste;j++) {
                if(!(nombreTeste%nombresPremiers[j])) {
                    estPremier=false;
                    break;
                }
            }
            if(estPremier) {
                nombresPremiers[nombresTestes]=nombreTeste;
                nombresTestes++;
                //cout << nombreTeste << endl;
            }
        }
        nombreTeste+=2;



    }
    cout << nombresPremiers[nombresTestes-1] << endl;

    QueryPerformanceCounter(&finalTime);
    cout << "Fini en " << (((float)(finalTime.QuadPart-initTime.QuadPart))*1000.0f/(float)freqTime.QuadPart) << " ms" << endl;

    return 0;
}
