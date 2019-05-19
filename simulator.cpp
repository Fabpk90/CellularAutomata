#include "simulator.h"

Automata automataGlob; // TEMPORAIRE POUR EVITER ERRRORS

void Simulate(Automata& automata)
{
    automataGlob = automata;

    Generation newest;
    newest.generationID = automata.GetCurrentGen().generationID + 1;
    automata.AddGeneration(newest);
    State oldState;

    for(unsigned int i = 0; i < automata.GetSizeX(); i++)
    {
        for(unsigned int j = 0; j < automata.GetSizeY(); j++)
        {
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

bool ComputePosition(std::vector<std::pair<int , int >> positions ,std::vector<State*> testState , int  targetX , int  targetY){
    for(int i=0; i<positions.size(); i++)
    {
        if (automataGlob.GetCellState(targetX+positions[i].first,targetY+positions[i].second).color != testState[i]->color){ // test entre la position relative entre la case central et celles de la règle pour voir si l'état est le même
            return false;
        }
    }
    return true;
}

bool ComputeCount(int amount, State* &toCheckAgainst, int posX, int posY){


    int X = 0, Y = 0;
    int count = 0;
    for (int i = 0; i < automataGlob.GetNeigborhoodPositions().size(); i++) {
       X = automataGlob.GetNeigborhoodPositions()[i].first + posX;
       Y = automataGlob.GetNeigborhoodPositions()[i].second + posY;

       count += (automataGlob.GetCellState(X,Y).color
                 == toCheckAgainst->color);
    }

    return (amount <= count);
}
