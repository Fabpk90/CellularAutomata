#include "interface.h"


void Interface::printProbability()
{
    std::cout << "probability : " << m_probability.toStdString() << std::endl;
}

void Interface::CallSetDim(const QString dimension)
{

}

void Interface::CallSetNeighborhood(QString neighborhood)
{

}

void Interface::CallType(QString type)
{

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

Interface::Interface(QObject *parent) : QObject(parent)
{

}

void Interface::initialiseParser()
{

}
