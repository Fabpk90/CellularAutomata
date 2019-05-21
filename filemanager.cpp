#include "filemanager.h"
#include <QSysInfo>
#include <QString>

using namespace std;

    void SaveData(const string* Filename, char * Data){

        string tmp;
        if(QSysInfo::productVersion().toStdString() == "7 SP 1" || QSysInfo::productVersion().toStdString() == "8.1" || QSysInfo::productVersion().toStdString() == "10"){
            tmp=Filename->substr(8,Filename->size());
        }
        else{
            tmp= Filename->substr(7,Filename->size());
        }
        ofstream Stream(tmp.c_str());

        if(Stream){
            Stream << Data ;
        }

        else{
            cout<<tmp<<endl;
            cout<<"Le chemin du fichier n'est pas valide"<<endl;
        }
    }


    char * LoadData(const string* FileName){/* charge le fichier contenant la topologie de l'automate(dimension, type, nombre d'états, taille, voisinage), les règles et l'ensemble des matrices formant la trace. */

        string tmp;
        if(QSysInfo::productVersion().toStdString() == "7 SP 1" || QSysInfo::productVersion().toStdString() == "8.1" || QSysInfo::productVersion().toStdString() == "10"){
            tmp=FileName->substr(8,FileName->size());
        }
        else{
            tmp= FileName->substr(7,FileName->size());
        }
        ifstream File(tmp);
        string Data;

        if(File){
            string Line;
            while(getline(File, Line)){

                Data += Line;
                Data += "\n";
            }
        }

        else {
            cout << "Le chemin du fichier n'est pas valide" << endl;
        }

        char * Result = new char[Data.length() + 1];
        std::strcpy(Result, Data.c_str());
        return Result;
    }
