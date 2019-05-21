#include "simulator.h"
#include <iostream>
Automata* automataGlob; // TEMPORAIRE POUR EVITER ERRRORS


namespace Simulator {
    void Simulate(Automata& automata)
    {
        automataGlob = &automata;
         if (automata.GetCurrentGen().generationID < automata.GetMaxSimulations()){
            Generation newest;
            newest.generationID = automata.GetCurrentGen().generationID + 1;
            newest.cellMatrix = vector<unsigned int>(automata.GetSizeX() * automata.GetSizeY());

            std::cout <<"Yeppa" << automata.GetCurrentGen().generationID << std::endl;
            cout << "Newest ID: " << newest.generationID << endl;

            automata.AddGeneration(newest);
            State oldState;

            for(unsigned int i = 0; i < automata.GetSizeX(); i++)
            {
                for(unsigned int j = 0; j < automata.GetSizeY(); j++)
                {
                    cout << endl << "Taking care of i: " << i << " j: " << j << endl;
                    //Init la cellule de la nouvelle gen à son ancienne valeur
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

            automata.NextGen();
        }

    }

    bool ComputePosition(std::vector<std::pair<int , int >> positions ,std::vector<State*> testState , int  targetX , int  targetY){
        for(int i=0; i<positions.size(); i++)
        {
            cout << "Positions X: " << targetX << " Position Y: " << targetY << endl;
            cout << "Neib name: " << automataGlob->GetCellState(targetX+positions[i].second,targetY+positions[i].first).name << " Test name: " << testState[i]->name << endl;
            cout << "Position vect X: " << positions[0].second << "Position vect Y: " << positions[0].first << endl;
            if (automataGlob->GetCellState(targetX+positions[i].second,targetY+positions[i].first).color != testState[i]->color){ // test entre la position relative entre la case central et celles de la règle pour voir si l'état est le même
                cout << "False Truth" << endl;
                return false;
            }
        }
        cout << "True Administrator" << endl;
        return true;
    }

    bool ComputeCount(int amount, State* &toCheckAgainst, int posX, int posY){


        int X = 0, Y = 0;
        int count = 0;
        cout << "Amount: " << amount << endl;
        cout << "To check against: " << toCheckAgainst->name << endl;
        cout << "Neigborh amount: " << automataGlob->GetNeigborhoodPositions().size() << endl;

        for (int i = 0; i < automataGlob->GetNeigborhoodPositions().size(); i++) {
           X = automataGlob->GetNeigborhoodPositions()[i].second + posX;
           Y = automataGlob->GetNeigborhoodPositions()[i].first + posY;

           if(automataGlob->GetCellState(X,Y).color == toCheckAgainst->color)
               count++;

           cout << "Checked State " << automataGlob->GetCellState(X,Y).name << endl;
        }

        cout << "Counted number " << count << endl;
        if(amount <= count)
        {
            cout << "True Administrator" << endl;
        }
        else
            cout << "False Truth" << endl;
        return (amount <= count);
    }
}

