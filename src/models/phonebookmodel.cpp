#include "../../include/models/phonebookmodel.h"

PhoneBookModel::PhoneBookModel(std::shared_ptr<DatabaseFacade> dbFacade,
                               QObject *parent)
    : QObject               (parent),
      m_dbFacadeAbonent     (dbFacade),
      m_dbFacadePhone       (dbFacade),
      m_dbFacadePhoneType   (dbFacade),
      m_areModelsInitialized(false)
{
    
}

void PhoneBookModel::addAbonent()
{
    QString surname   {},
            name      {},
            patronymic{};
            
    if (AbonentEditor(surname, name, patronymic).exec() != QDialog::Accepted)
        return;
    
    std::shared_ptr<Abonent> newAbonent = std::make_shared<Abonent>(Abonent(surname, name, patronymic));
    
    if (!m_dbFacadeAbonent->insertAbonent(newAbonent)) {
        emit showMessage(QMessageBox::Warning, "Ошибка", "Новый абонент не был добавлен!");                
        
        return;
    }
    
    m_abonentsModel->addAbonent(newAbonent);
}

void PhoneBookModel::editAbonent(const QModelIndex index)
{
    QModelIndex sourceIndex    = m_abonentsProxyModel->mapToSource(index);
    Abonent    *currentAbonent = static_cast<Abonent*>(sourceIndex.internalPointer());
    
    if (!currentAbonent) {
        emit showMessage(QMessageBox::Warning, "Ошибка", "Текущий элемент не найден!");
        
        return;
    }
    
    QString surname    = currentAbonent->getSurname(),
            name       = currentAbonent->getName(),
            patronymic = currentAbonent->getPatronymic();
            
    if (AbonentEditor(surname, name, patronymic).exec() != QDialog::Accepted)
        return;
    
    std::shared_ptr<Abonent> newAbonentData = std::make_shared<Abonent>(surname, name, patronymic, currentAbonent->getAbonentId());
    
    if (!m_dbFacadeAbonent->updateAbonent(newAbonentData)) {
        emit showMessage(QMessageBox::Warning, "Ошибка", "Выбранный абонент не был изменен!");                
        
        return;
    }
    
    m_abonentsModel->updateAbonent(sourceIndex, newAbonentData);
}

void PhoneBookModel::removeAbonent(const QModelIndex index)
{
    QModelIndex sourceIndex    = m_abonentsProxyModel->mapToSource(index);
    Abonent    *currentAbonent = static_cast<Abonent*>(sourceIndex.internalPointer());
    
    if (!currentAbonent) {
        emit showMessage(QMessageBox::Warning, "Ошибка", "Текущий элемент не найден!");
        
        return;
    }
    
    emit resetSelection();
    
    if (!m_dbFacadeAbonent->deleteAbonentById(currentAbonent->getAbonentId())) {
        emit showMessage(QMessageBox::Warning, "Ошибка", "Текущий элемент не был удален!");        
        
        return;
    }
    
    m_abonentsModel->removeAbonent(sourceIndex);
    
    clearPhonesModel();
}

void PhoneBookModel::addPhone(const QModelIndex abonentIndex)
{
    QVector<std::shared_ptr<PhoneType>> phoneTypes{};
    
    if (!m_dbFacadePhoneType->selectAllPhoneTypes(phoneTypes)) {
        emit showMessage(QMessageBox::Warning, "Ошибка", "Типы телефонов не были получены!");                        
        
        return;
    }
    
    QString number {};
    quint64 typeRow{0};
    
    PhoneEditor      phoneEditor     {number, typeRow};
    PhonesTypesModel phonesTypesModel{phoneTypes};
    
    phoneEditor.setPhonesModel(&phonesTypesModel);
            
    if (phoneEditor.exec() != QDialog::Accepted)
        return;
    
    std::shared_ptr<Phone> newPhone = std::make_shared<Phone>(Phone(number, 
                                                                    phonesTypesModel.getPhoneTypeStringByRow(typeRow),
                                                                    0, 
                                                                    phonesTypesModel.getPhoneTypeIdByRow(typeRow)));
    
    QModelIndex sourceIndex = m_abonentsProxyModel->mapToSource(abonentIndex);
    Abonent    *curAbonent  = static_cast<Abonent*>(sourceIndex.internalPointer());
    
    if (!m_dbFacadePhone->insertPhoneToAbonent(newPhone, curAbonent->getAbonentId())) {
        emit showMessage(QMessageBox::Warning, "Ошибка", "Новый телефон не был добавлен!");                
        
        return;
    }
    
    m_phonesModel->addPhone(newPhone);
}

void PhoneBookModel::editPhone(const QModelIndex index)
{
    QModelIndex sourceIndex  = m_phonesProxyModel->mapToSource(index);
    Phone      *currentPhone = static_cast<Phone*>(sourceIndex.internalPointer());
    
    if (!currentPhone) {
        emit showMessage(QMessageBox::Warning, "Ошибка", "Текущий элемент не найден!");
        
        return;
    }
    
    QVector<std::shared_ptr<PhoneType>> phoneTypes{};
    
    if (!m_dbFacadePhoneType->selectAllPhoneTypes(phoneTypes)) {
        emit showMessage(QMessageBox::Warning, "Ошибка", "Не были получены типы телефонов!");                        
        
        return;
    }
    
    PhonesTypesModel phonesTypesModel{phoneTypes};
    
    QString number  = currentPhone->getNumber();
    quint64 typeRow = phonesTypesModel.getRowByPhoneType(currentPhone->getTypeId());
    
    PhoneEditor phoneEditor{number, typeRow};
    
    phoneEditor.setPhonesModel(&phonesTypesModel);
            
    if (phoneEditor.exec() != QDialog::Accepted)
        return;
    
    std::shared_ptr<Phone> newPhone = std::make_shared<Phone>(Phone(number, 
                                                                    phonesTypesModel.getPhoneTypeStringByRow(typeRow),
                                                                    currentPhone->getPhoneId(), 
                                                                    phonesTypesModel.getPhoneTypeIdByRow(typeRow)));
    
    if (!m_dbFacadePhone->updatePhone(newPhone)) {
        emit showMessage(QMessageBox::Warning, "Ошибка", "Телефон не был изменен!");                
        
        return;
    }
    
    m_phonesModel->updatePhone(sourceIndex, newPhone);
}

void PhoneBookModel::removePhone(const QModelIndex index)
{
    QModelIndex sourceIndex  = m_phonesProxyModel->mapToSource(index);
    Phone      *currentPhone = static_cast<Phone*>(sourceIndex.internalPointer());
    
    if (!currentPhone) {
        emit showMessage(QMessageBox::Warning, "Ошибка", "Текущий элемент не найден!");
        
        return;
    }
    
    emit resetSelection();
    
    if (!m_dbFacadePhone->deletePhoneById(currentPhone->getPhoneId())) {
        emit showMessage(QMessageBox::Warning, "Ошибка", "Текущий элемент не был удален!");        
        
        return;
    }
    
    m_phonesModel->removePhone(sourceIndex);
}

void PhoneBookModel::clearPhonesModel() {
    m_phonesModel->clearData();
}

void PhoneBookModel::getPhonesOfAbonent(const QModelIndex index, const QModelIndex)
{
    QModelIndex sourceIndex    = m_abonentsProxyModel->mapToSource(index);
    Abonent    *currentAbonent = static_cast<Abonent*>(sourceIndex.internalPointer());
    
    if (!currentAbonent)
        return;

    QVector<std::shared_ptr<Phone>> phones{};
    
    if (!m_dbFacadePhone->selectAllPhonesOfAbonent(phones, QString::number(currentAbonent->getAbonentId()))) {
        emit showMessage(QMessageBox::Warning, "Ошибка", "Телефоны выбранного абонента не были получены!");      
        
        return;
    }
    
    m_phonesModel->setData(phones);
}

void PhoneBookModel::initializeModels()
{
    if (m_areModelsInitialized)
        return;
    
    QVector<std::shared_ptr<Abonent>> abonents{}; 
    
    if (!m_dbFacadeAbonent->selectAllAbonents(abonents)) {
        emit showMessage(QMessageBox::Warning, "Ошибка", "Абоненты не были получены!");        
        
        return;
    }
    
    m_areModelsInitialized = true;
    
    m_abonentsModel = new AbonentsModel(this);
    m_phonesModel   = new PhonesModel(this);
    
    m_abonentsModel->setData(abonents);
    
    m_abonentsProxyModel = new QSortFilterProxyModel(this);
    m_phonesProxyModel   = new QSortFilterProxyModel(this);
    
    m_abonentsProxyModel->setSourceModel(m_abonentsModel);
    m_phonesProxyModel->setSourceModel(m_phonesModel);
    m_abonentsProxyModel->setFilterKeyColumn(AbonentsModel::Field::C_SURNAME);
    
    emit setModels(m_abonentsProxyModel, m_phonesProxyModel);
}

void PhoneBookModel::setSearchRegExp(QString pattern)
{
    clearPhonesModel();
    
    pattern.push_front('^');
    
    m_abonentsProxyModel->setFilterRegularExpression(pattern);
}
