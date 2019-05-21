#include "simulator.h"
#include <iostream>
Automata* automataGlob;


namespace Simulator {
    void Simulate(Automata& automata)
    {
        //Garde l'automate en globale pour les computes
        automataGlob = &automata;
         if (automata.GetCurrentGen().generationID < automata.GetMaxSimulations()){

            //Créer la nouvelle génération à ajouter au vecteur
            Generation newest;
            newest.generationID = automata.GetCurrentGen().generationID + 1;
            newest.cellMatrix = vector<unsigned int>(automata.GetSizeX() * automata.GetSizeY());
            automata.AddGeneration(newest);

            //Etat antécédant
            State oldState;

            for(unsigned int i = 0; i < automata.GetSizeX(); i++)
            {
                for(unsigned int j = 0; j < automata.GetSizeY(); j++)
                {

                    //Init la cellule de la nouvelle gen à son ancienne valeur pour pas ne laisser de trous si aucune règle ne doit s'appliquer
                    oldState = automata.GetCellState(i,j);
                    automata.NextGen();
                    automata.SetCell(i,j, oldState);
                    automata.PreviousGen();


                    for(unsigned int k = 0; k < automata.GetRules().size(); k++)
                        if(automata.GetRules()[k]->GetStartingState().color == automata.GetCellState(i,j).color) //Applique la règle seulement si l'état de départ correspond à l'état de la case testé
                        {
                            automata.GetRules()[k]->Apply(i,j);
                        }
                }
            }

            //simulation d'une génération terminée. On se base sur la nouvelle
            automata.NextGen();
        }

    }

    bool ComputePosition(std::vector<std::pair<int , int >> positions ,std::vector<State*> testState , int  targetX , int  targetY){
        for(int i=0; i<positions.size(); i++)
        {  
            // test entre la position relative entre la case central et celles de la règle pour voir si l'état est le même
            if (automataGlob->GetCellState(targetX+positions[i].second,targetY+positions[i].first).color != testState[i]->color){
                //Si un seul des cas n'est pas satisfait alors la règle ne s'applique pas
                return false;
            }
        }
        return true;
    }

    bool ComputeCount(int amount, State* &toCheckAgainst, int posX, int posY){


        int X = 0, Y = 0;
        int count = 0; //Quantité compté

        for (int i = 0; i < automataGlob->GetNeigborhoodPositions().size(); i++) {

           //Création des coordonnées X+offset du voisinage
           X = automataGlob->GetNeigborhoodPositions()[i].second + posX;
           Y = automataGlob->GetNeigborhoodPositions()[i].first + posY;


           if(automataGlob->GetCellState(X,Y).color == toCheckAgainst->color)
               count++;
        }

        return (amount <= count);
    }
}

