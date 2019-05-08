#ifndef LIST_H
#define LIST_H

#include <QObject>
#include <QVector>
#include <qqmlapplicationengine.h>

struct Item
{
    QString description;
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
        void removeItem();

    private:
    QVector<Item> mItems;
    QQmlApplicationEngine* engine;
};

#endif // LIST_H
