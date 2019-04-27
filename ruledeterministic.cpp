#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "ruledeterministic.h"

void RuleDeterministic::Apply(int x, int y){

// la je suis un peu perdu parce que on récupère x et y mais pas la matrice donc on a pas le reste pour tester les règles
    bool ruleTrue = true; // utilisé pour tester si tous les params sont vrais
    for( RuleParameters & Rparams : this->parameters) { // on parcours chaque paramètres de la règle
        if (automata.matrice[x+Rparams.x][y+Rparams.y].state.name == Rparams.toCheckAgainst.name ){ // test entre la position relative entre la case central et celles de la règle pour voir si l'état est le même
            ruleTrue= ruleTrue && true;
        }
        else {
            ruleTrue=false;
        }
    }
    if(ruleTrue){ // si la règle est effectivement vraie on applique
        automata.matrice[x][y]=this->toChangeInto; // changement de l'état de la cellule

    }


}

