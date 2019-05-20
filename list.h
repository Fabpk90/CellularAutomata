#ifndef LIST_H
#define LIST_H

#include <QObject>
#include <QVector>
#include <qqmlapplicationengine.h>

struct Item
{
    int number;
    QString stateName;
    QString stateColor;
};

class List : public QObject
{
    Q_OBJECT
    public:
        explicit List(QObject *parent = nullptr);

        QVector<Item> items() const;

        bool setItemAt(int index, const Item &item);
        void setEngine(QQmlApplicationEngine *value);
        QVector<Item> getListItem()
        {
            return mItems;
        }


    signals:
        void preItemAppended();
        void postItemAppended();

        void preItemRemoved(int index);
        void postItemRemoved();

    public slots:
        void appendItem();
        void appendState();
        void removeItem(int index);
        void setStateName(QString stateName);
        void removeAllItems();
        void setStateColor(QString stateColor);
        int getListCount(){
            return mItems.size();
        }

    private:
    QVector<Item> mItems;
    QQmlApplicationEngine* engine;
    int indice=1;
    QString stateNameTmp;
    QString stateColorTmp;
};

#endif // LIST_H
