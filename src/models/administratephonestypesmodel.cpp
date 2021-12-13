#include "../../include/models/administratephonestypesmodel.h"

AdministratePhonesTypesModel::AdministratePhonesTypesModel(std::shared_ptr<DatabaseFacade> dbFacade, QObject *parent)
    : QObject             (parent),
      m_dbFacadePhoneType (dbFacade),
      m_isModelInitialized(false)
{
    
}

void AdministratePhonesTypesModel::initializeModel()
{
    if (m_isModelInitialized)
        return;
    
    QVector<std::shared_ptr<PhoneType>> phoneTypes{}; 
    
    if (!m_dbFacadePhoneType->selectAllPhoneTypes(phoneTypes)) {
        emit showMessage(QMessageBox::Warning, "Ошибка", "Типы телефонов не были получены!");        
        
        return;
    }
    
    m_isModelInitialized = true;
    m_phonesTypesModel   = new PhonesTypesModel(phoneTypes, this);
    
    emit setModel(m_phonesTypesModel);
}

void AdministratePhonesTypesModel::addPhoneType()
{
    QString phoneType{};
            
    if (PhoneTypeEditor(phoneType).exec() != QDialog::Accepted)
        return;
    
    std::shared_ptr<PhoneType> newPhoneType = std::make_shared<PhoneType>(PhoneType(phoneType));
    
    if (!m_dbFacadePhoneType->insertPhoneType(newPhoneType)) {
        emit showMessage(QMessageBox::Warning, "Ошибка", "Новый абонент не был добавлен!");                
        
        return;
    }
    
    m_phonesTypesModel->addPhoneType(newPhoneType);
}

void AdministratePhonesTypesModel::editPhoneType(const QModelIndex index)
{
    PhoneType *currentPhoneType = static_cast<PhoneType*>(index.internalPointer());
    
    if (!currentPhoneType) {
        emit showMessage(QMessageBox::Warning, "Ошибка", "Текущий элемент не найден!");
        
        return;
    }
    
    QString phoneType = currentPhoneType->getType();
            
    if (PhoneTypeEditor(phoneType).exec() != QDialog::Accepted)
        return;
    
    std::shared_ptr<PhoneType> newPhoneTypeData = std::make_shared<PhoneType>(phoneType, currentPhoneType->getTypeId());
    
    if (!m_dbFacadePhoneType->updatePhoneType(newPhoneTypeData)) {
        emit showMessage(QMessageBox::Warning, "Ошибка", "Выбранный тип телефона не был изменен!");                
        
        return;
    }
    
    m_phonesTypesModel->updatePhoneType(index, newPhoneTypeData);
}

void AdministratePhonesTypesModel::removePhoneType(const QModelIndex index)
{
    PhoneType *currentPhoneType = static_cast<PhoneType*>(index.internalPointer());
    
    if (!currentPhoneType) {
        emit showMessage(QMessageBox::Warning, "Ошибка", "Текущий элемент не найден!");
        
        return;
    }
    
    emit resetSelection();
    
    if (!m_dbFacadePhoneType->deletePhoneType(currentPhoneType->getTypeId())) {
        emit showMessage(QMessageBox::Warning, "Ошибка", "Текущий элемент не был удален!");        
        
        return;
    }
    
    m_phonesTypesModel->removePhoneType(index);
}
