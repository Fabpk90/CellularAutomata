#include "list.h"
#include <string>
#include <iostream>
#include "interface.h"

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
    item.stateName=nullptr;
    std::to_string(item.number);
    mItems.append(item);

    emit postItemAppended();
}

void List::appendState()
{
    Interface interface;
    emit preItemAppended();
    Item item;
    item.number=indice++;
    item.stateName= interface.stateName();
    std::cout<< "STATE NAME: " << item.stateName.toStdString() <<std::endl;
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
