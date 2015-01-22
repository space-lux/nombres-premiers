#include <iostream>
#include <fstream>
#include <windows.h>
#include <cmath>
#include <limits>

using namespace std;
typedef unsigned long Nombre; // long long pour 64 bits

// Prototypes
bool getOChar(const char* msg);


int main() {
    Nombre  nombreAChercher=2,
            nombreTeste=11,
            nombresTestes=4,
            *nombresPremiers;
    bool estPremier=true;
    LARGE_INTEGER initTime, finalTime, freqTime;
    QueryPerformanceFrequency(&freqTime);

    cout << "Chercheur de nombres premiers" << endl;
    do{
        cout << "Nombres premiers à trouver (au moins 5) : > ";
        cin >> nombreAChercher;
        if(!cin){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }while(nombreAChercher<5);

    ///...

    if(getOChar("Charger des donnees ?")){
        // Fenêtre d'ouverture de fichier
        CHAR nameFilter[]= "Fichier de nombres .nbpr\0*.nbpr\0\0";
        CHAR nameDefault[MAX_PATH]= "nombresPremiers";
        OPENFILENAME ofn({0});
        ofn.lStructSize=sizeof(OPENFILENAME);
        //ofn.hwndOwner=HWND_TOP;
        // La fenêtre ne se met en avant qu'à la deuxième ouverture (en ouvrant puis en sauvegardant) mais cette ligne n'y change rien
        ofn.lpstrFilter=nameFilter;
        ofn.nMaxFile=(260);
        ofn.lpstrFile=nameDefault;
        ofn.lpstrDefExt="nbpr";
        ofn.lpstrTitle="Ouvrir un fichier de nombres";
        ofn.Flags=OFN_OVERWRITEPROMPT | OFN_FILEMUSTEXIST;
        if(GetOpenFileName(&ofn)){
            //cout << "Chargement de " << ofn.lpstrFile << endl;
            ifstream file(ofn.lpstrFile, ios::binary | ios::ate);
            if(file){
                size_t fileSize;
                //file.seekg(0, ios::end | ios::ate);
                fileSize=file.tellg();
                file.seekg(0,ios::beg);
                char fileC;
                file.get(fileC);
                if(fileC=='S' && fileSize>10){
                    file.read((char*)&nombresTestes, sizeof(Nombre));
                    cout << fileSize << " octets -- "<< nombresTestes << " nombres stockes." << endl;
                    if(fileSize==2+(nombresTestes+1)*sizeof(Nombre)){
                        file.get(fileC);
                        if(fileC=='C'){
                            nombreAChercher+=nombresTestes;
                            nombresPremiers=new Nombre[nombreAChercher]; // NOTE : NOMBRE TOTAL, pour en rajouter après, d'où la somme ci-dessus
                            file.read((char*)nombresPremiers, nombresTestes*sizeof(Nombre));
                            nombreTeste=nombresPremiers[nombresTestes-1]+2; // On reprend au dernier nombre premier. Je sais rendre un nombre pair mais pas multiple de 10...
                            // On affiche pour tester :
                            if(getOChar("Voir les nombres dans le fichier ?")){
                                cout << "Nombres : ";
                                for(Nombre nbDisp=0; nbDisp<nombresTestes; nbDisp++){
                                    cout << nombresPremiers[nbDisp] << " ";
                                }
                                cout << endl;
                            }
                        }else cout << "Le fichier est invalide. Il est probablement fait pour une autre taille de Nombre." << endl;
                    }else cout << "Le fichier est corrompu. Il est probablement fait pour une autre taille de Nombre." << endl;
                }else{
                    cout << "Le fichier ne correspond pas." << endl;
                }
            }else cout << "Impossible d'ouvrir le fichier." << endl;
        }
    }
    // Dans tous les cas où ça n'a pas marché, initialiser normalement
    if(nombresTestes==4){
        cout << "Pas d'ouverture de fichier." << endl;
        nombresPremiers=new Nombre[nombreAChercher];
        nombresPremiers[0]=2;
        nombresPremiers[1]=3;
        nombresPremiers[2]=5;
        nombresPremiers[3]=7;
        cout << endl << "Calcul des " << nombreAChercher << " premieres valeurs..." << endl;
    }else{
        cout << endl << "Calcul de " << nombreAChercher-nombresTestes << " nouvelles valeurs..." << endl;
    }


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
                if(nombresTestes==nombreAChercher) break;
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
                if(nombresTestes==nombreAChercher) break;
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
                if(nombresTestes==nombreAChercher) break;
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
    cout << endl << " --------" << endl << "Fini en ";// << (((float)(finalTime.QuadPart-initTime.QuadPart))*1000.0f/(float)freqTime.QuadPart) << " ms" << endl;
    float computedTime(((float)(finalTime.QuadPart-initTime.QuadPart))*1000.0f/(float)freqTime.QuadPart);
    if(computedTime>60000.0f) cout << computedTime/60000.0f << " min" << endl;
    else cout << computedTime << " ms" << endl;

    cout << "Sauvegarder les " << nombreAChercher;
    if(getOChar(" nombres ?")){
        CHAR nameFilter[]= "Fichier de nombres .nbpr\0*.nbpr\0\0";
        CHAR nameDefault[MAX_PATH]= "nombresPremiers";
        OPENFILENAME ofn({0});
        ofn.lStructSize=sizeof(OPENFILENAME);
        //ofn.hwndOwnfer=hwnd;
        ofn.lpstrFilter=nameFilter;
        ofn.nMaxFile=(260);
        ofn.lpstrFile=nameDefault;
        ofn.lpstrDefExt="nbpr";
        ofn.lpstrTitle="Sauvegarder un fichier de nombres";
        ofn.Flags=OFN_OVERWRITEPROMPT | OFN_FILEMUSTEXIST; // OFN_CREATEPROMPT pour dire un truc après ? // OFN_EXPLORER useless ?
        if(GetSaveFileName(&ofn)){
            ofstream file(ofn.lpstrFile, ios::binary);
            //cout << "Sauvegarde de " << ofn.lpstrFile << endl;
            if(file){
                file.put('S');
                file.write((char*)&nombreAChercher, sizeof(Nombre)); // NOTE : LE TOTAL
                file.put('C');
                file.write((char*)nombresPremiers, sizeof(Nombre)*nombreAChercher);
                cout << "Fichier sauvegarde." << endl;
            }else cout << "Impossible d'ouvrir le fichier." << endl;
        }
    }

    if(getOChar("Voir les resultats : tout afficher ?")){
        for(Nombre i=0;i<nombresTestes;i++){
            cout << nombresPremiers[i] << " ";
            if(!((i+1)%1001)){ // Pour éviter la double-pause quand on calcule des valeurs rondes, du moins abaisser la proba
                cout << endl;
                system("PAUSE");
            }
        }
        cout << endl;
    }else{
        cout << 2 << /*endl << 3 << (supprimé pour le cas où on ne demande que 5 chiffres, les "..." sont inutiles)*/endl << "..." << endl << nombresPremiers[nombresTestes-3] << endl << nombresPremiers[nombresTestes-2] << endl << nombresPremiers[nombresTestes-1] << endl;
    }

    cout << "Fin. ";
    system("PAUSE");

    return 0;
}

bool getOChar(const char* msg){
    char rep;
    cin.clear();
    //cin.ignore(numeric_limits<streamsize>::max());
    fflush(stdin); // Relativement déprécié

    cout << msg << " (O pour Oui) > ";
    cin >> rep;

    //cin.ignore(numeric_limits<streamsize>::max(), '\n');
    fflush(stdin);
    return rep=='O';
}
