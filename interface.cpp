#include "interface.h"
#include <QQmlComponent>
#include <QQmlEngine>
#include <vector>
#include <QFile>
#include <string>
#include <algorithm>

void Interface::initialiseParser()
{

    this->parser.SetAutomata(&ca);
    setType("Deterministic");
    setDimension("TwoDimensions");
    setNeighborhood("Moore");
    setMaxGenerationsToSimulate("1");
    setSizeX("1");
    setSizeY("1");
}

void Interface::printProbability()
{
    std::cout << "probability : " << m_probability.toStdString() << std::endl;
}

void Interface::sendMandatoryInfo()
{
    dataToParse="";
    CallSetType();
    CallSetDim();
    CallSetNeighborhood();
    CallMatrixSize();
    CallMaxGenerationsToSimulate();
    //Pour avoir sizeof(dataToParse)=4
    dataToParse+="0";
    dataToParse+="0";
    std::cout<< "dataToParseFromInterface: " << dataToParse <<std::endl;
    this->parser.ParseAndAddType(&dataToParse);
}

void Interface::CallSetDim()
{
    std::cout << "Dim : " << m_dimension.toStdString() << std::endl;
}

void Interface::CallSetNeighborhood()
{
    if(m_neighborhood.toStdString()=="Von Neumann")
        dataToParse+="1";
    else dataToParse+="0";
    std::cout << "Neigh : " << m_neighborhood.toStdString() << std::endl;
}

void Interface::CallSetType()
{
    if(m_type.toStdString()=="Stochastic")
        dataToParse+="1";
    else dataToParse+="0";
    std::cout << "Type : " << m_type.toStdString() << std::endl;
}

void Interface::CallMaxGenerationsToSimulate()
{
    string maxGen=m_maxGenerationsToSimulate.toStdString();
    std::cout << "MaxGenerations : " << m_maxGenerationsToSimulate.toStdString() << std::endl;
}

void Interface::CallMatrixSize()
{
    string size=m_sizeX.toStdString() + ";" + m_sizeY.toStdString();
    this->parser.ParseAndAddSize(&size);
    std::cout << "Size : " << m_sizeX.toStdString() + ";" + m_sizeY.toStdString() << std::endl;
}


void Interface::printComputeProbability()
{
    std::cout << "computeProbability : " << m_computeProbability.toStdString() << std::endl;
}

void Interface::printPosAndCount()
{
    std::cout << "posAndCount : " << m_posAndCount.toStdString() << std::endl;
}

void Interface::printStateToChangeTo()
{
    std::cout << "stateToChangeTo : " << m_stateToChangeTo.toStdString() << std::endl;
}

void Interface::CallSetProbability(QString probability)
{

}

void Interface::CallSetComputeProbability(QString computeProbability)
{

}

void Interface::CallSetPosAndCount(QString posAndCount)
{

}

void Interface::CallSetStateToChangeTo(QString stateToChangeTo)
{

}

void Interface::CallGetStates()
{

}

void Interface::okCreateRule()
{   

    /*on veut envoyer un string de la forme :
        Type;EtatDep ;EtatArr;lengthCond;(x;y;EtatCond)*;Proba;EtatCond;
        où Type = Position ou Count
        où EtatDep est l'index de l'etat "central"
        où EtatArr est l'index de l'etat "toChangeTo"
        où lengthCond est le nombre de fois qu'un bloc de parenthese va apparaitre (on les appelera "*")
        où
            Pour Position: x et y sont les coordonnées relatives au "centre"
            Pour Count: x est le nombre de fois qu'un etat doit apparaitre et y n'est pas utilisé
        où EtatCond est l'index de l'etat selectionné par x & y
        où Proba est la probabilité que l'action soit effectuée
        //TODO EtatCond
    */
    int lengthCond = 0;
    QString rule = "";//la regle qu'on va envoyer au parser
    QString compositeCount = "";

    rule.append(posAndCount()); //position
    rule.append(";");

    if(posAndCount() == "Position"){
        if(dimension() == "OneDimension"){
            rule.append(matrixIndexAndStateIndex[1]); //index etat de depart
            for(int i = 0; i < 9; i++){
                if(posIndex[i] != "(" && i != 1){
                lengthCond++;
                }
            }
        }
        else if (dimension() == "TwoDimensions") {
            rule.append(matrixIndexAndStateIndex[4]); //index etat de depart
            for(int i = 0; i < 9; i++){
                if(posIndex[i] != "(" && i != 4){
                lengthCond++;
                }
            }
        }
        rule.append(";");
        if(matrixIndexAndStateIndex[9] != "("){ //TODO else? //index etat d'arrive
            rule.append(matrixIndexAndStateIndex[9]);
        }
        rule.append(";");
        QString length = QString::number(lengthCond); //lengthCond
        rule.append(length);
        rule.append(";");
        for (int i = 0; i < 9; i++) { // "*"
            if(posIndex[i] != "("){
                rule.append(posIndex[i]);
                rule.append(";");
            }
        }
    }
    else if (posAndCount() == "Count") {
        if(dimension() == "OneDimension"){ //etat de depart
            rule.append(matrixIndexAndStateIndex[1]);
        }
        else if (dimension() == "TwoDimensions") {
            rule.append(matrixIndexAndStateIndex[4]);
        }
        rule.append(";");
        if(matrixIndexAndStateIndex[9] != "("){//etat d'arrivee
            rule.append(matrixIndexAndStateIndex[9]);
        }
        rule.append(";");
        //on va creer un tableau dont la taille sera le plus grand indice d'etat
        //l'indice du tableau sera l'index de l'etat, la valeur stockée a cet indice sera le nombre de repetitions de cet etat
        int sizeofarray = matrixIndexAndStateIndex[0].toInt();
        for (int i = 1;i<9;i++) { //trouve le plus grand index d'etat
            if(sizeofarray < matrixIndexAndStateIndex[i].toInt()){
                sizeofarray = matrixIndexAndStateIndex[i].toInt();
            }
        }
        sizeofarray = sizeofarray + 1; //cette taille va aussi servir a determiner length cond
        std::cout << "sizeofarray = " << sizeofarray << std::endl; //test
        int stateArray[sizeofarray];
        for(int i = 0; i<sizeofarray; i++){//initialise le tableau (impossible d'initialiser un tableau de taille variable avec {0})
            stateArray[i] = 0;
        }
        for(int i = 0; i < 9; i++){
            if(dimension() == "OneDimension"){//evite le cas "central"
                if(i!=1){
                    stateArray[matrixIndexAndStateIndex[i].toInt()]++;
                }
            }
            if(dimension() == "TwoDimensions"){//evite le cas "central"
                if(i!=4){
                    stateArray[matrixIndexAndStateIndex[i].toInt()]++;
                }
            }
        }
        for(int n = 0; n<sizeofarray; n++){//test
            std::cout << "state " << n << " apparait " << stateArray[n] << " fois" <<std::endl;
        }
        lengthCond = sizeofarray;
        for (int i = 0; i < sizeofarray; i++)
        {
            if (stateArray[i] == 0)
            {
                lengthCond--;
            }
        }
        rule.append(QString::number(lengthCond));
        rule.append(";");
        //a partir du tableau precedent on va determiner la syntaxe des (x;y;Stateindex) où x est la valeur de stateArray[StateIndex]
        for (int i = 0;i<sizeofarray; i++) {
            if(stateArray[i] != 0){
                compositeCount.append("(");
                compositeCount.append(QString::number(stateArray[i])); //x
                compositeCount.append(";");
                compositeCount.append("0"); //y
                compositeCount.append(";");
                compositeCount.append(QString::number(i));//StateIndex
                compositeCount.append(")");
                rule.append(compositeCount);
                rule.append(";");
                compositeCount = "";
            }
        }

    }
    if(probability() != ""){
        rule.append(probability());
        rule.append(";");
    }
    //TODO etat cond
    string stdRule = rule.toStdString();
    std::cout << "Rule sent to parser = " << stdRule << std::endl;
    try {
         parser.ParseAndAddRules(&stdRule);
    } catch (const string &error) {
       cout << error << endl;
    }

}

void Interface::printDimension()
{
    std::cout << "Dimension : " << m_dimension.toStdString() << std::endl;
}

void Interface::printMaxGenerationsToSimulate()
{
    std::cout << "MaxGenerations : " << m_maxGenerationsToSimulate.toStdString() << std::endl;
}

void Interface::setComputeProbability(QString computeProbability)
{
    if (m_computeProbability == computeProbability)
        return;

    m_computeProbability = computeProbability;
    emit computeProbabilityChanged(m_computeProbability);
}

void Interface::setProbability(QString probability)
{
    if (m_probability == probability)
        return;

    m_probability = probability;
    emit probabilityChanged(m_probability);
}

void Interface::setPosAndCount(QString posAndCount)
{
    if (m_posAndCount == posAndCount)
        return;

    m_posAndCount = posAndCount;
    emit posAndCountChanged(m_posAndCount);
}

void Interface::setStateToChangeTo(QString stateToChangeTo)
{
    if (m_stateToChangeTo == stateToChangeTo)
        return;

    m_stateToChangeTo = stateToChangeTo;
    emit stateToChangeToChanged(m_stateToChangeTo);
}

void Interface::setDimension(QString dimension)
{
    if (m_dimension == dimension)
        return;

    m_dimension = dimension;
    emit dimensionChanged(m_dimension);
}

void Interface::setType(QString type)
{
    if (m_type == type)
        return;

    m_type = type;
    emit typeChanged(m_type);
}

void Interface::setNeighborhood(QString neighborhood)
{
    if (m_neighborhood == neighborhood)
        return;

    m_neighborhood = neighborhood;
    emit neighborhoodChanged(m_neighborhood);
}

void Interface::setMaxGenerationsToSimulate(QString maxGenerationsToSimulate)
{
    if (m_maxGenerationsToSimulate == maxGenerationsToSimulate)
        return;

    m_maxGenerationsToSimulate = maxGenerationsToSimulate;
    emit maxGenerationsToSimulateChanged(m_maxGenerationsToSimulate);
}

void Interface::setSizeX(QString sizeX)
{
    if (m_sizeX == sizeX)
        return;

    m_sizeX = sizeX;
    emit sizeXChanged(m_sizeX);
}

void Interface::setSizeY(QString sizeY)
{
    if (m_sizeY == sizeY)
        return;

    m_sizeY = sizeY;
    emit sizeYChanged(m_sizeY);
}

void Interface::setStateName(QString name)
{
    if(m_stateName != name)
    {
        m_stateName = name;
        emit stateNameChanged(name);
    }
}

void Interface::setStateColor(QString color)
{
    if(m_stateColor != color)
    {
        m_stateColor=color;
        emit stateColorChanged(color);
    }

}

//Interface::Interface(QObject *parent) : QObject(parent)
void Interface::CallSetStateName(QString probability){





}

void Interface::CallSetColor(QString color){



}

void Interface::okCreateState(QString state){

    QString composite;
    composite.append("1;");
    composite.append(m_stateName);
    composite.append(state);
    composite.append(m_stateColor);
    string string= composite.toStdString();
    cout<<string<<endl;
    try {
         parser.ParseAndAddStates(&string);
    } catch (std::string) {

    }

}

void Interface::printStateName()
{
    std::cout << "StateName : " << m_stateName.toStdString() << std::endl;
}

void Interface::printStateColor()
{
    std::cout << "StateColor : " << m_stateColor.toStdString() << std::endl;
}

void Interface::chooseGen(QString gen)
{
    parser.GetAutomata()->ChooseGen(gen.toUInt());//to check after merge
}

void Interface::loadInterface()
{
   if(parser.GetAutomata()->GetIsStocha())
           setType("Stochastic");
   else setType("Deterministic");
   if(parser.GetAutomata()->GetIsVonNeighborhood())
       setNeighborhood("Von Neumann");
   else  setNeighborhood("Moore");
   setSizeX(QString::number(parser.GetAutomata()->GetSizeX()));
   setSizeY(QString::number(parser.GetAutomata()->GetSizeY()));
   for(int i=0; i<parser.GetAutomata()->GetRules().size(); i++)
   {
       List ruleListView;
       ruleListView.appendItem(); //TODO: pas sûre du tout
   }
   for(int i=0; i<parser.GetAutomata()->GetStates().size(); i++)
   {
       //stateListView.appendState();
       setStateName(QString::fromStdString(parser.GetAutomata()->GetStates().at(i).name));
       setStateColor(parser.GetAutomata()->GetStates().at(i).color.name(QColor::HexRgb));
       List stateListView;
       stateListView.appendState(); //TODO: pas sûre du tout
   }
   if(parser.GetAutomata()->GetSizeY()==1) setDimension("OneDimension");
   else setDimension("TwoDimensions");
}

QString Interface::returnCurrentGen()
{
    return QString::number(parser.GetAutomata()->GetCurrentGen().generationID);
}


int Interface::getRememberIndex() const
{
    return  rememberIndex;
}

void Interface::setRememberIndex(int value)
{
    rememberIndex = value;
}

//met "(x;y;StateIndex)" dans le tableau posIndex pour okCreateRule() dans le cas Position
void Interface::associateStateAndIndex(QString StateIndex)
{
    QString composite = "(";
    if(posAndCount() == "Position"){
            if (dimension() == "OneDimension"){
            switch (rememberIndex) {
            case 0:
                composite.append("-1;0;");
                composite.append(StateIndex);
                composite.append(")");
                break;
            //4 est le centre et ne doit pas etre dans la liste composite
            case 2:
                composite.append("1;0;");
                composite.append(StateIndex);
                composite.append(")");
                break;
            default:
                break;
            }
        }
        if(dimension() == "TwoDimensions"){
            switch (rememberIndex) {
            case 0:
                composite.append("-1;1;");
                composite.append(StateIndex);
                composite.append(")");
                break;
            case 1:
                composite.append("0;1;");
                composite.append(StateIndex);
                composite.append(")");
                break;
            case 2:
                composite.append("1;1;");
                composite.append(StateIndex);
                composite.append(")");
                break;
            case 3:
                composite.append("-1;0;");
                composite.append(StateIndex);
                composite.append(")");
                break;
            //4 est le centre et ne doit pas etre dans la liste composite
            case 5:
                composite.append("1;0;");
                composite.append(StateIndex);
                composite.append(")");
                break;
            case 6:
                composite.append("-1;-1;");
                composite.append(StateIndex);
                composite.append(")");
                break;
            case 7:
                composite.append("0;-1;");
                composite.append(StateIndex);
                composite.append(")");
                break;
            case 8:
                composite.append("1;-1;");
                composite.append(StateIndex);
                composite.append(")");
                break;
            default:
                break;
            }
        }
        posIndex[rememberIndex] = composite;
    }
    matrixIndexAndStateIndex[rememberIndex] = StateIndex; //version non convertie de [index] -> etat aussi utilisé pour le mode Count
    std::cout << composite.toStdString() << std::endl; //test
}

void Interface::cleanRuleCreationWindow()
{
    for(int i = 0; i<10; i++){
        matrixIndexAndStateIndex[i]="(";
        posIndex[i]="(";
    }
}




Interface::Interface(QObject *parent) : QObject(parent)
{

}

void Interface::callSaveMatrix(string path, string name, string firstGen=string(), string lastGen=string()){

    string tmp;
    if(!firstGen.empty() && !lastGen.empty() ) tmp= this->parser.GetDataToBeSaved(10,10 );
    else tmp= this->parser.GetDataToBeSaved();

    char * Data = new char[tmp.length() + 1];
    strcpy(Data, tmp.c_str());
    SaveData(&name, Data);



}

void Interface::callLoad(string name, string path){

   this->parser.ParseFile(&name);

}

void Interface::callExecution(){
   this->parser.GetAutomata()->Simulate();
}

