#include "filemanager.h"

using namespace std;

    void SaveData(const string* Filename, char * Data){

        ofstream Stream(Filename->c_str());

        if(Stream){

            Stream << Data ;


        }

        else{
            cout<<"Le chemin du fichier n'est pas valide"<<endl;


        }


    }


    char * LoadData(const string* FileName){/* charge le fichier contenant la topologie de l'automate(dimension, type, nombre d'états, taille, voisinage), les règles et l'ensemble des matrices formant la trace. */

        ifstream File(*FileName);

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
