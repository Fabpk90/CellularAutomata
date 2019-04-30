#ifndef INTERFACE_H
#define INTERFACE_H

#include <QObject>
#include <iostream>

//TODO ALL THE INPUT TESTS
class Interface : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString probability READ probability WRITE setProbability NOTIFY probabilityChanged) //TODO input has to be int
    Q_PROPERTY(QString computeProbability READ computeProbability WRITE setComputeProbability NOTIFY computeProbabilityChanged) //TODO input has to be int
    Q_PROPERTY(QString posAndCount READ posAndCount WRITE setPosAndCount NOTIFY posAndCountChanged)
    Q_PROPERTY(QString stateToChangeTo READ stateToChangeTo WRITE setStateToChangeTo NOTIFY stateToChangeToChanged)

private:
    QString m_probability;
    QString m_computeProbability;
    QString m_posAndCount;
    QString m_stateToChangeTo;

public:
    explicit Interface(QObject *parent = nullptr);

    //init
    void initialiseParser(); //TODO

    //probability
    QString probability() const
    {
        return m_probability;
    }
    Q_INVOKABLE void printProbability(); //for tests

    //computeProbability
    QString computeProbability() const
    {
        return m_computeProbability;
    }
    Q_INVOKABLE void printComputeProbability(); // for tests

    //posAndCount
    QString posAndCount() const
    {
        return m_posAndCount;
    }
    Q_INVOKABLE void printPosAndCount(); //for tests

    //stateToChangeTo
    QString stateToChangeTo() const
    {
        return m_stateToChangeTo;
    }
    Q_INVOKABLE void printStateToChangeTo(); //for tests

    void callGetStates(); //TODO
    void okCreateRule(); //TODO

signals:

    void probabilityChanged(QString probability);

    void computeProbabilityChanged(QString computeProbability);

    void posAndCountChanged(QString posAndCount);

    void stateToChangeToChanged(QString stateToChangeTo);

public slots:
void setComputeProbability(QString computeProbability);
void setProbability(QString probability);
void setPosAndCount(QString posAndCount);
void setStateToChangeTo(QString stateToChangeTo);
};

#endif // INTERFACE_H
