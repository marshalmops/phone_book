#ifndef ABONENTSMODEL_H
#define ABONENTSMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <QVector>

#include "../entities/abonent.h"

class AbonentsModel : public QAbstractTableModel
{
    Q_OBJECT
    
public:
    enum Field {
        C_ID,
        C_SURNAME,
        C_NAME,
        C_PATRONYMIC,
        C_COUNT
    };
    
    explicit AbonentsModel(QObject *parent = nullptr);

    virtual int         rowCount   (const QModelIndex &parent)                          const override;
    virtual int         columnCount(const QModelIndex &parent)                          const override;
    virtual QVariant    data       (const QModelIndex &index, int role)                 const override;
    virtual QVariant    headerData (int section, Qt::Orientation orientation, int role) const override;
    virtual QModelIndex index      (int row, int column, const QModelIndex &parent) const override;
    
    void setData(const QVector<std::shared_ptr<Abonent>> &abonents);
    
    void addAbonent   (const std::shared_ptr<Abonent> abonent);
    void updateAbonent(const QModelIndex index, const std::shared_ptr<Abonent> newAbonentData);
    void removeAbonent(const QModelIndex &index);
    
private:
    QVector<std::shared_ptr<Abonent>> m_abonents;

};

#endif // ABONENTSMODEL_H
