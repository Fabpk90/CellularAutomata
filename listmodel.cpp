#include "listmodel.h"
#include "list.h"
#include <string.h>


ListModel::ListModel(QObject *parent)
    : QAbstractListModel(parent)
    , m_list_var(nullptr)
{
}

int ListModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !m_list_var)
        return 0;

    return m_list_var->items().size();
}

int ListModel::getRowCount()
{
    return m_list_var->getListCount();
}

QVariant ListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !m_list_var)
        return QVariant();

    const Item item = m_list_var->items().at(index.row());
    switch (role) {
    case number:
        return QString::number(item.number);
    case stateName:
        return  QString(item.stateName);
    case stateColor:
        return QString(item.stateColor);
    }

    return QVariant();
}

bool ListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!m_list_var)
        return false;

    Item item = m_list_var->items().at(index.row());
    switch (role) {
    case number:
        item.number = value.toInt();
        break;
    case stateName:
        item.stateName = value.toString();
        break;
    case stateColor:
        item.stateColor=value.toString();
        break;
    }

    if (m_list_var->setItemAt(index.row(), item)) {
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags ListModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> ListModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[number]="number";
    names[stateName]= "stateName";
    names[stateColor]="stateColor";
    return names;
}

List *ListModel::list_var() const
{
    return m_list_var;
}

void ListModel::setList(List *list_var)
{
    beginResetModel();

    if (m_list_var)
        m_list_var->disconnect(this);

    m_list_var = list_var;

    if (m_list_var) {
        connect(m_list_var, &List::preItemAppended, this, [=]() {
            const int index = m_list_var->items().size();
            beginInsertRows(QModelIndex(), index, index);
        });
        connect(m_list_var, &List::postItemAppended, this, [=]() {
            endInsertRows();
        });

        connect(m_list_var, &List::preItemRemoved, this, [=](int index) {
            beginRemoveRows(QModelIndex(), index, index);
        });
        connect(m_list_var, &List::postItemRemoved, this, [=]() {
            endRemoveRows();
        });
    }

    endResetModel();
}
