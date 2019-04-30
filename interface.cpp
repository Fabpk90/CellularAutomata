#include "interface.h"


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

Interface::Interface(QObject *parent) : QObject(parent)
{

}

void Interface::initialiseParser()
{

}
