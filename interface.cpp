#include "interface.h"
#include <QQmlComponent>
#include <QQmlEngine>
#include <vector>
#include <QFile>
#include <string>
#include <algorithm>

void Interface::initialiseParser()
{

   matrixview->pause();
    if(ca != nullptr)
        delete ca;

    ca = new Automata(false, false, 1, 1, vector<Rule*>(), vector<State>(), vector<Generation>());

    ruleListView.removeAllItems();
    stateListView.removeAllItems();

    this->parser.SetAutomata(ca);
    setType("Deterministic");
    setDimension("TwoDimensions");
    setNeighborhood("Moore");
    setMaxGenerationsToSimulate("1");
    setSizeX("2");
    setSizeY("2");
    matrixview->setParser(&parser);
    setNumbState("0");
}

void Interface::initMatrix()
{
    matrixview->initMatrix();
    isReady=true;
}

QString Interface::type() const
{
    return m_type;
}

QString Interface::dimension() const
{
    return m_dimension;
}

void Interface::sendMandatoryInfo()
{
    dataToParse="";
    CallSetType();
    CallSetDim();
    CallMatrixSize();
    CallMaxGenerationsToSimulate();
    //Pour avoir sizeof(dataToParse)=4, conforme au Parser
    dataToParse+="0";
    CallSetNeighborhood();
    dataToParse+="0";
    this->parser.ParseAndAddType(&dataToParse);
    this->parser.GetAutomata()->SetMaxSimulations(m_maxGenerationsToSimulate.toUInt());
}

void Interface::CallSetDim()
{
}

void Interface::CallSetNeighborhood()
{
    if(m_neighborhood.toStdString()=="Von Neumann")
        dataToParse+="1";
    else dataToParse+="0";
}

void Interface::CallSetType()
{
    if(m_type.toStdString()=="Stochastic")
        dataToParse+="1";
    else dataToParse+="0";
}

void Interface::CallMaxGenerationsToSimulate()
{
}

void Interface::CallMatrixSize()
{
    if(m_dimension=="TwoDimensions"){ m_sizeY=m_sizeX;matrixview->dim="TwoDimensions";}
    else{ m_sizeY="1";matrixview->dim="OneDimension";}
    string size=m_sizeX.toStdString() + ";" + m_sizeY.toStdString();
    this->parser.ParseAndAddSize(&size);
}

QString Interface::stateToChangeTo() const
{
    return m_stateToChangeTo;
}

void Interface::CallSetProbability()
{

}

void Interface::CallSetPosAndCount()
{

}

void Interface::CallSetStateToChangeTo()
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
        où EtatCond est utilisé comme etat augmentant la probabilité dans le cas stochastic dynamic
    */
    int lengthCond = 0;
    QString rule = "";//la regle qu'on va envoyer au parser
    QString compositeCount = "";
    rule.append("1;");
    rule.append(posAndCount()); //position
    rule.append(";");

    if(posAndCount() == "Position"){
        if(dimension() == "OneDimension"){
            rule.append(matrixIndexAndStateIndex[1]); //index etat de depart
            for(int i = 0; i < SIZEOFINDEXARRAYS-2; i++){
                if(posIndex[i] != "(" && i != 1){
                lengthCond++;
                }
            }
        }
        else if (dimension() == "TwoDimensions") {
            rule.append(matrixIndexAndStateIndex[4]); //index etat de depart
            for(int i = 0; i < SIZEOFINDEXARRAYS - 2; i++){
                if(posIndex[i] != "(" && i != 4){
                lengthCond++;
                }
            }
        }
        rule.append(";");
        if(matrixIndexAndStateIndex[9] != "("){//index etat d'arrivee
            rule.append(matrixIndexAndStateIndex[9]);
        }
        rule.append(";");
        QString length = QString::number(lengthCond); //lengthCond
        rule.append(length);
        rule.append(";");
        for (int i = 0; i < SIZEOFINDEXARRAYS - 2; i++) { // "*"
            if(posIndex[i] != "("){
                rule.append(posIndex[i]);
                rule.append(";");
            }
        }

    }
    else if (posAndCount() == "Count") {
        if(dimension() == "OneDimension" && matrixIndexAndStateIndex[1] != "("){ //etat de depart
            rule.append(matrixIndexAndStateIndex[1]);
        }
        else if (dimension() == "TwoDimensions" && matrixIndexAndStateIndex[4] != "(") {
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
        for (int i = 1;i<SIZEOFINDEXARRAYS - 2;i++) { //trouve le plus grand index d'etat
            if(sizeofarray < matrixIndexAndStateIndex[i].toInt()){
                sizeofarray = matrixIndexAndStateIndex[i].toInt();
            }
        }
        sizeofarray = sizeofarray + 1; //cette taille va aussi servir a determiner length cond
        int stateArray[sizeofarray];
        for(int i = 0; i<sizeofarray; i++){//initialise le tableau (impossible d'initialiser un tableau de taille variable avec {0})
            stateArray[i] = 0;
        }
        for(int i = 0; i < SIZEOFINDEXARRAYS - 2; i++){
            if(dimension() == "OneDimension"){//evite le cas "central"
                if(i!=1 && matrixIndexAndStateIndex[i] != "("){
                    stateArray[matrixIndexAndStateIndex[i].toInt()]++;
                }
            }
            if(dimension() == "TwoDimensions"){//evite le cas "central"
                if(neighborhood() == "Moore"){
                    if(i!=4 && matrixIndexAndStateIndex[i] != "("){
                        stateArray[matrixIndexAndStateIndex[i].toInt()]++;
                    }
                }
                else if (neighborhood() == "Von Neumann")
                {
                    if(i!=4 && i!= 0 && i!=2 && i!=6 && i!=8 && matrixIndexAndStateIndex[i] != "("){
                        stateArray[matrixIndexAndStateIndex[i].toInt()]++;
                    }
                }
                
                
            }
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
                compositeCount.append(";)");
                rule.append(compositeCount);
                rule.append(";");
                compositeCount = "";
            }
        }

    }
    if(type() == "Stochastic"){//EtatCond
        rule.append(probability());
        rule.append(";");
        if(matrixIndexAndStateIndex[10] != "("){
            rule.append(matrixIndexAndStateIndex[10]);
            rule.append(";");
        }
    }
    string stdRule = rule.toStdString();
    stdRule.append("\n");
    try {
         parser.ParseAndAddRules(&stdRule);
    } catch (const string &error) {
       cout << error << endl;
    }
}

QString Interface::neighborhood() const
{
    return m_neighborhood;
}

QString Interface::maxGenerationsToSimulate() const
{
    return m_maxGenerationsToSimulate;
}

QString Interface::sizeX() const
{
    return m_sizeX;
}

QString Interface::sizeY() const
{
    return m_sizeY;
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

void Interface::setNumbState(QString numbState)
{
    if (m_numbState == numbState)
        return;

    m_numbState = numbState;
    emit numbStateChanged(m_numbState);
}

void Interface::CallSetStateName(){
}

void Interface::CallSetColor(){
}

void Interface::okCreateState(QString state){

    QString composite;
    composite.append("1;");
    composite.append(m_stateColor);
    composite.append(state);
    composite.append(m_stateName);
    composite.append(";");
    string string= composite.toStdString();
    try {
         parser.ParseAndAddStates(&string);
    } catch (std::string s) {
        cout<<"erreur"<<s<<endl;
    }
    int numStateTmp=m_numbState.toInt()+1;
    setNumbState(QString::number(numStateTmp));

}

void Interface::okCreateHistory()
{
    int s=stateVector.size();
    int sizeOfStates=parser.GetAutomata()->GetStates().size();
    QString composite;
    composite.append("1;0;");
    if(s)
    {
        for (int stateId : stateVector) {

            if(stateId !=-1){

                composite.append(QString::number(stateId));

            }
            else {
                composite.append(QString::number(rand()%sizeOfStates));//mettre en fonction de la taille de la liste des états
            }
            composite.append(",");
        }

        composite.resize(composite.size()-1);
        composite.append(";");
    }

    string res=composite.toStdString();
    parser.ParseHistory(&res);
}

QString Interface::stateName() const
{
    return m_stateName;
}

QString Interface::getStateName()
{
    return m_stateName;
}

QString Interface::stateColor() const
{
    return m_stateColor;
}

QString Interface::getStateColor()
{
    return m_stateColor;
}

void Interface::chooseGen(QString gen)
{
   matrixview->selectGen(gen.toInt());


}

//Permet de mettre à jour l'interface losqu'on load à partir d'un fichier
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
   for(uint i=0; i<parser.GetAutomata()->GetRules().size(); i++)
   {
       ruleListView.appendItem();
   }
   for(uint i=0; i<parser.GetAutomata()->GetStates().size(); i++)
   {
       setStateName(QString::fromStdString(parser.GetAutomata()->GetStates().at(i).name));
       stateListView.setStateName(m_stateName);
       setStateColor(parser.GetAutomata()->GetStates().at(i).color.name(QColor::HexRgb));
       stateListView.setStateColor(m_stateColor);
       stateListView.appendState();
   }
   if(parser.GetAutomata()->GetSizeY()==1){ setDimension("OneDimension");matrixview->dim="OneDimension";}
   else {setDimension("TwoDimensions");matrixview->dim="TwoDimensions";}
}

QString Interface::returnCurrentGen()
{
   if (parser.GetAutomata() != nullptr && !parser.GetAutomata()->GetStates().empty())
    return QString::number(parser.GetAutomata()->GetCurrentGen().generationID);
   return QString("0");
}

void Interface::removeStateAutomata(int index)
{
    if(parser.GetAutomata()->GetStates().size()!=0)
    {
        for(int i=0; i<stateListView.getListItem().size();i++)
        {
            if(stateListView.getListItem().at(i).number==index)
                parser.GetAutomata()->RemoveState(parser.GetAutomata()->GetStates().at(i));
        }
    }
}

void Interface::removeRuleAutomata(int index)
{
    if(parser.GetAutomata()->GetRules().size()!=0)
    {
        for(int i=0; i<stateListView.getListItem().size();i++)
        {
            if(stateListView.getListItem().at(i).number==index)
                parser.GetAutomata()->RemoveRule(*parser.GetAutomata()->GetRules().at(i));
        }
    }
}

void Interface::removeAllRulesAutomata()
{
    parser.GetAutomata()->RemoveAllRules();
}

void Interface::removeAllStatesAutomata()
{
    parser.GetAutomata()->RemoveAllStates();
}

void Interface::updateStateVector(int index, int stateId)
{
    stateVector[index]=stateId;

}

void Interface::sizeTheVector()
{
    int size=m_sizeX.toInt()*m_sizeY.toInt();
    stateVector.resize(size);
    for (int i=0; i<size;i++) {
     stateVector[i]=-1;

    }
}

void Interface::displayEverything()
{
    engine->rootContext()->setContextProperty(QStringLiteral("matrixview"),matrixview);
}

QColor Interface::stateColorFromSquareIndex(int index)
{
    unsigned int indexOfState = matrixIndexAndStateIndex[index].toUInt();
    return parser.GetAutomata()->GetStates().at(indexOfState).color.name(QColor::HexRgb);
}

bool Interface::getReadyness()
{
    return isReady;
}

QString Interface::numbState() const
{
    return m_numbState;
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
                composite.append(";)");
                break;
            //4 est le centre et ne doit pas etre dans la liste composite
            case 2:
                composite.append("1;0;");
                composite.append(StateIndex);
                composite.append(";)");
                break;
            default:
                break;
            }
        }
        /*
                    Voici le repère qui est utilisé dans le logiciel:
                              Y
                     0------------------>
                     |
                     |
                     |
                    X|
                     |
                     |
                     |
                     v

                     Des modifications ont donc été apportées au mappage a deux dimensions (seulement, pour l'instantn faut voir 1D)
                     Seul les case X ont été réaranger, pour retrouver le comportement d'origine, aller de 0 à 8 en skippant 4
                */
        if(dimension() == "TwoDimensions"){
            switch (rememberIndex) {
            case 2:
                composite.append("-1;1;");
                composite.append(StateIndex);
                composite.append(";)");
                break;
            case 5:
                composite.append("0;1;");
                composite.append(StateIndex);
                composite.append(";)");
                break;
            case 8:
                composite.append("1;1;");
                composite.append(StateIndex);
                composite.append(";)");
                break;
            case 1:
                composite.append("-1;0;");
                composite.append(StateIndex);
                composite.append(";)");
                break;
            //4 est le centre et ne doit pas etre dans la liste composite
            case 7:
                composite.append("1;0;");
                composite.append(StateIndex);
                composite.append(";)");
                break;
            case 0:
                composite.append("-1;-1;");
                composite.append(StateIndex);
                composite.append(";)");
                break;
            case 3:
                composite.append("0;-1;");
                composite.append(StateIndex);
                composite.append(";)");
                break;
            case 6:
                composite.append("1;-1;");
                composite.append(StateIndex);
                composite.append(";)");
                break;
            default:
                break;
            }
        }
        posIndex[rememberIndex] = composite;
    }
    matrixIndexAndStateIndex[rememberIndex] = StateIndex; //version non convertie de [index] -> etat aussi utilisé pour le mode Count
}

void Interface::cleanRuleCreationWindow()
{
    for(int i = 0; i<SIZEOFINDEXARRAYS; i++){
        matrixIndexAndStateIndex[i]="(";
        posIndex[i]="(";

    }
}

QQmlApplicationEngine *Interface::getEngine() const
{
    return engine;
}

void Interface::setEngine(QQmlApplicationEngine *value)
{
    engine = value;
}

List *Interface::getStateListView()
{
    return &stateListView;
}

List *Interface::getRuleListView()
{
    return &ruleListView;
}

QString Interface::probability() const
{
    return m_probability;
}

Matrixview *Interface::getMatrixview() const
{
    return matrixview;
}

void Interface::setMatrixview(Matrixview *value)
{
    matrixview = value;
}

Interface::Interface(QObject *parent) : QObject(parent)
{
}

void Interface::callSaveMatrix(QString path, QString name, QString firstGen, QString lastGen){

    string tmp;string na=name.toStdString();
    /*if(!firstGen.isEmpty() && !lastGen.isEmpty() )*/ tmp= this->parser.GetDataToBeSaved(0,99 );
    //else tmp= this->parser.GetDataToBeSaved();

    char * Data = new char[tmp.length() + 1];
    strcpy(Data, tmp.c_str());
    SaveData(&na, Data);
}

void Interface::callLoad(QString name, QString path){
   string pa=path.toStdString();
   this->parser.ParseFile(&pa);
   matrixview->setParser(&this->parser);
   initMatrix();
   matrixview->getEngine()->rootContext()->setContextProperty(QStringLiteral("matrixview"),matrixview);
}

void Interface::callExecution(){
   this->parser.GetAutomata()->Simulate();
}

QString Interface::posAndCount() const
{
    return m_posAndCount;
}

