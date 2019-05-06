#include "interface.h"
#include <QQmlComponent>
#include <QQmlEngine>
#include <vector>
#include <QFile>
void Interface::printProbability()
{
    std::cout << "probability : " << m_probability.toStdString() << std::endl;
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

void CallSetStateName(QString probability){





}

void CallSetColor(QString color){



}

void OkCreateState(QString state){




}

Matrixview *Interface::getMatrixview() const
{
    return matrixview;
}

void Interface::setMatrixview(Matrixview *value)
{
    matrixview = value;
}

QQmlApplicationEngine *Interface::getEngine() const
{
    return engine;
}

void Interface::setEngine(QQmlApplicationEngine *value)
{
    engine = value;
}

Interface::Interface(QObject *parent) : QObject(parent)
{
    
}

void Interface::initialiseParser()
{
    
    this->parser= Parser();
    
    
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

   Automata* test =this->parser.GetAutomata();
    Simulate(*test);


}

void Interface::displayMatrix(){
QQmlApplicationEngine tmpengine;
Matrixview tmp;
    for(int i=0;i<92;i++){
        matrixview->setCellAt(i,{QColor("red"),"State"+to_string(i)});


    }

   // tmpengine.rootContext()->setContextProperty(QStringLiteral("matrixview"),&tmp);

}

unsigned int Interface::getSizeX(){
    return this->parser.GetAutomata()->GetSizeX();
}

unsigned int Interface::getSizeY(){
    return this->parser.GetAutomata()->GetSizeY();
}

