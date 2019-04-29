#ifndef INTERFACE_H
#define INTERFACE_H

#include <QObject>
#include <iostream>

class Interface : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString probability READ probability WRITE setProbability NOTIFY probabilityChanged)
private:
    QString m_probability;

public:
    explicit Interface(QObject *parent = nullptr);

    //probability
    QString probability() const
    {
        return m_probability;
    }
    void setProbability(const QString &probability);
    Q_INVOKABLE void printProbability(); //for tests


signals:

    void probabilityChanged(QString probability);

public slots:
};

#endif // INTERFACE_H
