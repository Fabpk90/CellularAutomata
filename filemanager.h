#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>



    void SaveData(const std::string* filename, char * data);// fonction qui enregistre les matrices de la trace, les règles et la topologie de l'automate(dimension, type, nombre d'états, taille, voisinage) dans un fichier.


    char * LoadData(const std::string* fileName);// charge le fichier contenant la topologie de l'automate(dimension, type, nombre d'états, taille, voisinage), les règles et l'ensemble des matrices formant la trace.

#endif // FILEMANAGER_H
