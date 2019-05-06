#ifndef MATRIXMODEL_H
#define MATRIXMODEL_H

#include <QAbstractListModel>
class Matrixview;

class MatrixModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(Matrixview *listOfState READ getListOfState WRITE setListOfState)
public:
    explicit MatrixModel(QObject *parent = nullptr);
    enum{
        Color=Qt::DecorationRole,
        StateName

    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QHash<int, QByteArray>roleNames() const override;


    Matrixview *getListOfState() const;
    void setListOfState(Matrixview *);


private:
    Matrixview * listOfState;

};

#endif // MATRIXMODEL_H
