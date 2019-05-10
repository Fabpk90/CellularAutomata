#include "list.h"
#include <string>
#include <iostream>

List::List(QObject *parent) : QObject(parent)
{

}

QVector<Item> List::items() const
{
    return mItems;
}

bool List::setItemAt(int index, const Item &item)
{
    if (index < 0 || index >= mItems.size())
        return false;

    const Item &oldItem = mItems.at(index);
    if (item.number == oldItem.number)
        return false;

    mItems[index] = item;
    return true;
}

void List::appendItem()
{
    emit preItemAppended();
    Item item;
    item.number=indice++;
    std::to_string(item.number);
    mItems.append(item);

    emit postItemAppended();
}

void List::removeItem(int index)
{
    emit preItemRemoved(index);
    mItems.removeAt(index);
    emit postItemRemoved();
}

void List::setEngine(QQmlApplicationEngine *value)
{
    engine = value;
}
