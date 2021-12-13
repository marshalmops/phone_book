#include "../../include/models/abonentsmodel.h"

AbonentsModel::AbonentsModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    
}

int AbonentsModel::rowCount(const QModelIndex &parent) const
{
    return m_abonents.length();
}

int AbonentsModel::columnCount(const QModelIndex &parent) const
{
    return Field::C_COUNT;
}

QVariant AbonentsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();
    
    if (index.row() > m_abonents.length())
        return QVariant();
    
    Abonent *curAbonent = static_cast<Abonent*>(index.internalPointer());
    
    if (!curAbonent)
        return QVariant();
    
    switch (index.column()) {
        case Field::C_ID:
            return curAbonent->getAbonentId();
        case Field::C_SURNAME:
            return curAbonent->getSurname();
        case Field::C_NAME:
            return curAbonent->getName();
        case Field::C_PATRONYMIC:
            return curAbonent->getPatronymic();
    }
    
    return QVariant();
}

QVariant AbonentsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Orientation::Vertical || role != Qt::DisplayRole)
        return QVariant();
    
    switch (section) {
        case Field::C_SURNAME:
            return QString(tr("Фамилия"));
        case Field::C_NAME:
            return QString(tr("Имя"));
        case Field::C_PATRONYMIC:
            return QString(tr("Отчество"));
    }
    
    return QVariant();
}

QModelIndex AbonentsModel::index(int row, int column, const QModelIndex &parent) const
{
    if (row > m_abonents.length() || column >= Field::C_COUNT)
        return QModelIndex();
    
    return createIndex(row, column, m_abonents[row].get());
}

void AbonentsModel::setData(const QVector<std::shared_ptr<Abonent> > &abonents)
{
    beginResetModel();
    
    m_abonents = abonents;
    
    endResetModel();
}

void AbonentsModel::addAbonent(const std::shared_ptr<Abonent> abonent)
{
    auto abonentsCount = m_abonents.length();
    
    beginInsertRows(QModelIndex(), abonentsCount, abonentsCount);
    
    m_abonents.push_back(abonent);
    
    endInsertRows();
}

void AbonentsModel::updateAbonent(const QModelIndex index, const std::shared_ptr<Abonent> newAbonentData)
{
    if (!index.isValid())
        return;
    
    m_abonents[index.row()]->changeData(newAbonentData);
    
    emit dataChanged(index, index);
}

void AbonentsModel::removeAbonent(const QModelIndex &index)
{
    if (!index.isValid())
        return;
    
    Abonent *abonent = static_cast<Abonent*>(index.internalPointer());
    
    if (!abonent)
        return;
    
    int abonentIndex{-1};
    
    for (int i = 0; i < m_abonents.length(); ++i) {
        if (m_abonents[i]->getAbonentId() == abonent->getAbonentId()) {
            abonentIndex = i;
            
            break;
        }
    }
    
    if (abonentIndex < 0)
        return;
    
    beginRemoveRows(QModelIndex(), index.row(), index.row());
    
    m_abonents.removeAt(abonentIndex);
    
    endRemoveRows();
}
