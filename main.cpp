#include <iostream>
#include <cmath>
#include <windows.h>
#include <limits>

using namespace std;
typedef unsigned long Nombre; // long long pour 64 bits

// Prototypes
bool getOChar();


int main() {
    Nombre  nombreAChercher=2,
            nombreTeste=11,
            nombresTestes=4,
            *nombresPremiers;
    bool estPremier=true;

    cout << "Chercheur de nombres premiers" << endl;
    cout << "Nombres premiers à trouver : ";
    cin >> nombreAChercher;
    nombresPremiers=new Nombre[nombreAChercher];
    nombresPremiers[0]=2;
    nombresPremiers[1]=3;
    nombresPremiers[2]=5;
    nombresPremiers[3]=7;
    cout /*<< 2 << endl << 3 << endl */<< "Recherche..." << endl;

    LARGE_INTEGER initTime, finalTime, freqTime;
    QueryPerformanceFrequency(&freqTime);
    ///...
    QueryPerformanceCounter(&initTime);

    while(nombresTestes<nombreAChercher) {

        if(nombreTeste%3) {
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

        if(nombreTeste%3) {
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

        if(nombreTeste%3) {
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

        if(nombreTeste%3) {
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

    QueryPerformanceCounter(&finalTime);
    cout << "Fini en ";// << (((float)(finalTime.QuadPart-initTime.QuadPart))*1000.0f/(float)freqTime.QuadPart) << " ms" << endl;
    float computedTime(((float)(finalTime.QuadPart-initTime.QuadPart))*1000.0f/(float)freqTime.QuadPart);
    if(computedTime>60000.0f) cout << computedTime/60000.0f << " min" << endl;
    else cout << computedTime << " ms" << endl;



    cout << "Tout afficher ?";
    if(getOChar()){
        for(Nombre i=0;i<nombresTestes;i++){
            cout << nombresPremiers[i] << endl;
        }
    }else{
        cout << 2 << endl << 3 << "..." << endl << nombresPremiers[nombresTestes-1] << endl;
    }

    system("PAUSE");

    return 0;
}

bool getOChar(){
    char rep;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << " (O pour oui) > ";
    cin >> rep;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return rep=='O';
}
