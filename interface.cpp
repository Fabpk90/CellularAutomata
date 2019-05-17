#include "interface.h"
#include <QQmlComponent>
#include <QQmlEngine>
#include <vector>
#include <QFile>
#include <string>

void Interface::initialiseParser()
{

    this->parser= Parser();
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
    CallSetType();
    CallSetDim();
    CallSetNeighborhood();
    CallMatrixSize();
    CallMaxGenerationsToSimulate();
    std::cout<< "dataToParseFromInterface: " << dataToParse[0] << dataToParse[1] <<std::endl;
    //parser.ParseAndAddType(&dataToParse);
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
    //parser.ParseAndAddSize(&size);
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

void Interface::OkCreateState(QString state){


}

void Interface::printStateName()
{
    std::cout << "StateName : " << m_stateName.toStdString() << std::endl;
}

void Interface::printStateColor()
{
    std::cout << "StateColor : " << m_stateColor.toStdString() << std::endl;
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

   Automata* test =this->parser.GetAutomata();
    Simulate(*test);


}

