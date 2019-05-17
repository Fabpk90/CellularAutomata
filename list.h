#ifndef LIST_H
#define LIST_H

#include <QObject>
#include <QVector>
#include <qqmlapplicationengine.h>
#include "interface.h"

struct Item
{
    int number;
    QString stateName;
};

class List : public QObject
{
    Q_OBJECT
    public:
        explicit List(QObject *parent = nullptr);

        QVector<Item> items() const;

        bool setItemAt(int index, const Item &item);
        void setEngine(QQmlApplicationEngine *value);

    signals:
        void preItemAppended();
        void postItemAppended();

        void preItemRemoved(int index);
        void postItemRemoved();

    public slots:
        void appendItem();
        void appendState();
        void removeItem(int index);

    private:
    QVector<Item> mItems;
    QQmlApplicationEngine* engine;
    int indice=1;
    Interface interface;
};

#endif // LIST_H
