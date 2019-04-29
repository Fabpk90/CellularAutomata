#include "interface.h"

void Interface::setProbability(const QString &probability)
{
    m_probability = probability;
}

void Interface::printProbability()
{
    std::cout << m_probability.toStdString() << std::endl;
}

Interface::Interface(QObject *parent) : QObject(parent)
{

}
