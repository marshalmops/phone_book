#include "../../include/models/phonesmodel.h"

PhonesModel::PhonesModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    
}

int PhonesModel::rowCount(const QModelIndex &parent) const
{
    return m_phones.length();
}

int PhonesModel::columnCount(const QModelIndex &parent) const
{
    return Field::C_COUNT;
}

QVariant PhonesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();
    
    if (index.row() > m_phones.length())
        return QVariant();
    
    std::shared_ptr<Phone> curPhone = m_phones[index.row()];
    
    if (!curPhone.get())
        return QVariant();
    
    switch (index.column()) {
        case Field::C_ID:
            return curPhone->getPhoneId();
        case Field::C_PHONE:
            return curPhone->getNumber();
        case Field::C_TYPE:
            return curPhone->getType();
    }
    
    return QVariant();
}

QVariant PhonesModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Orientation::Vertical || role != Qt::DisplayRole)
        return QVariant();
    
    switch (section) {
        case Field::C_PHONE:
            return QString(tr("Телефон"));
        case Field::C_TYPE:
            return QString(tr("Тип"));
    }
    
    return QVariant();
}

QModelIndex PhonesModel::index(int row, int column, const QModelIndex &parent) const
{
    if (row > m_phones.length() || column >= Field::C_COUNT)
        return QModelIndex();
    
    return createIndex(row, column, m_phones[row].get());
}

void PhonesModel::setData(const QVector<std::shared_ptr<Phone> > &phones)
{
    beginResetModel();
    
    m_phones = phones;
    
    endResetModel();
}

void PhonesModel::clearData()
{
    beginResetModel();
    
    m_phones.clear();
    
    endResetModel();
}

void PhonesModel::addPhone(const std::shared_ptr<Phone> phone)
{
    auto phonesCount = m_phones.length();
    
    beginInsertRows(QModelIndex(), phonesCount, phonesCount);
    
    m_phones.push_back(phone);
    
    endInsertRows();
}

void PhonesModel::updatePhone(const QModelIndex index, const std::shared_ptr<Phone> newPhoneData)
{
    if (!index.isValid())
        return;
    
    m_phones[index.row()]->changeData(newPhoneData);
    
    emit dataChanged(index, index);
}

void PhonesModel::removePhone(const QModelIndex &index)
{
    if (!index.isValid())
        return;
    
    Phone *phone = static_cast<Phone*>(index.internalPointer());
    
    if (!phone)
        return;
    
    int phoneIndex{-1};
    
    for (int i = 0; i < m_phones.length(); ++i) {
        if (m_phones[i]->getPhoneId() == phone->getPhoneId()) {
            phoneIndex = i;
            
            break;
        }
    }
    
    if (phoneIndex < 0)
        return;
    
    beginRemoveRows(QModelIndex(), index.row(), index.row());
    
    m_phones.removeAt(phoneIndex);
    
    endRemoveRows();
}
