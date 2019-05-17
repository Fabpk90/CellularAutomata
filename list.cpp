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
    item.stateName=nullptr;
    std::to_string(item.number);
    mItems.append(item);

    emit postItemAppended();
}

void List::appendState()
{
    emit preItemAppended();
    Item item;
    item.number=indice++;
    item.stateName=stateNameTmp;
    std::to_string(item.number);
    mItems.append(item);

    emit postItemAppended();
}

void List::removeItem(int index)
{
    for(int i=0; i<mItems.size();i++)
    {
        if(mItems.at(i).number==index)
        {
            emit preItemRemoved(i);
            mItems.removeAt(i);
            emit postItemRemoved();
        }
    }
}

void List::setEngine(QQmlApplicationEngine *value)
{
    engine = value;
}

void List::setStateName(QString stateName)
{
    stateNameTmp=stateName;
}
