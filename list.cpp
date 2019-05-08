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

void List::removeCompletedItems()
{

}

void List::setEngine(QQmlApplicationEngine *value)
{
    engine = value;
}
