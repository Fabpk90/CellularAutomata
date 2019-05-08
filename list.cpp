#include "list.h"

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
    if (item.description == oldItem.description)
        return false;

    mItems[index] = item;
    return true;
}

void List::appendItem()
{
    emit preItemAppended();

    Item item;
    mItems.append(item);

    emit postItemAppended();
}

void List::removeItem()
{
    for(int i=0; i<mItems.size();i++){
        emit preItemRemoved(i);
        mItems.removeAt(i);
        emit postItemRemoved();
    }
}

void List::setEngine(QQmlApplicationEngine *value)
{
    engine = value;
}
