#ifndef RULEMODEL_H
#define RULEMODEL_H

#include <QAbstractListModel>

class List;

class ListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(List *list_var READ list_var WRITE setList)

private:

    List * m_list_var;

public:
    explicit ListModel(QObject *parent=nullptr);

    enum {
        number
    };

List * list() const
{
    return m_list_var;
}

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QHash<int, QByteArray>roleNames() const override;

    List *list_var() const;

    void setList(List * list_var);

};

#endif // RULEMODEL_H
