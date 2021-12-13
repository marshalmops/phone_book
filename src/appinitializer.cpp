#include "../include/appinitializer.h"

bool AppInitializer::initializeApp(PhoneBookView  *phoneBookView)
{
    std::shared_ptr<DatabaseFacade> dbFacade = std::make_shared<DatabaseFacade>(DatabaseFacade());
    
    PhoneBookModel               *phoneBookModel      = new PhoneBookModel              (dbFacade, phoneBookView);
    AdministratePhonesTypesView  *admPhonesTypesView  = new AdministratePhonesTypesView ();
    AdministratePhonesTypesModel *admPhonesTypesModel = new AdministratePhonesTypesModel(dbFacade, phoneBookView);
    
    QSqlDatabase db = QSqlDatabase::database();
    
    if (!DatabaseManager::initializeDatabaseConnection(IDatabaseConnection::Type::T_SQLITE)) {
        QMessageBox::warning(phoneBookView, QObject::tr("Ошибка"), QObject::tr("Не удалось инициализировать подключение к базе данных!"));
        
        return false;
    }
    
    // PhoneBook:
    
    QObject::connect(phoneBookModel, &PhoneBookModel::setModels,       phoneBookView, &PhoneBookView::setModels);
    QObject::connect(phoneBookModel, &PhoneBookModel::showMessage,     phoneBookView, &PhoneBookView::showMessage);
    QObject::connect(phoneBookModel, &PhoneBookModel::resetSelection,  phoneBookView, &PhoneBookView::resetSelection);    
    
    QObject::connect(phoneBookView, &PhoneBookView::clearPhonesModel, phoneBookModel, &PhoneBookModel::clearPhonesModel);        
    QObject::connect(phoneBookView, &PhoneBookView::setSearchRegExp,  phoneBookModel, &PhoneBookModel::setSearchRegExp);            
    
    QObject::connect(phoneBookView, &PhoneBookView::addAbonent,    phoneBookModel, &PhoneBookModel::addAbonent);
    QObject::connect(phoneBookView, &PhoneBookView::editAbonent,   phoneBookModel, &PhoneBookModel::editAbonent);
    QObject::connect(phoneBookView, &PhoneBookView::removeAbonent, phoneBookModel, &PhoneBookModel::removeAbonent);
    
    QObject::connect(phoneBookView, &PhoneBookView::addPhone,    phoneBookModel, &PhoneBookModel::addPhone);
    QObject::connect(phoneBookView, &PhoneBookView::editPhone,   phoneBookModel, &PhoneBookModel::editPhone);
    QObject::connect(phoneBookView, &PhoneBookView::removePhone, phoneBookModel, &PhoneBookModel::removePhone);
    
    QObject::connect(phoneBookView, &PhoneBookView::getPhonesOfAbonent, phoneBookModel, &PhoneBookModel::getPhonesOfAbonent);
    
    // AdministratePhonesTypes:
    
    QObject::connect(admPhonesTypesModel, &AdministratePhonesTypesModel::setModel,       admPhonesTypesView, &AdministratePhonesTypesView::setModel);
    QObject::connect(admPhonesTypesModel, &AdministratePhonesTypesModel::showMessage,    admPhonesTypesView, &AdministratePhonesTypesView::showMessage);
    QObject::connect(admPhonesTypesModel, &AdministratePhonesTypesModel::resetSelection, admPhonesTypesView, &AdministratePhonesTypesView::resetSelection);    
    
    QObject::connect(admPhonesTypesView, &AdministratePhonesTypesView::addPhoneType,    admPhonesTypesModel, &AdministratePhonesTypesModel::addPhoneType);
    QObject::connect(admPhonesTypesView, &AdministratePhonesTypesView::editPhoneType,   admPhonesTypesModel, &AdministratePhonesTypesModel::editPhoneType);
    QObject::connect(admPhonesTypesView, &AdministratePhonesTypesView::removePhoneType, admPhonesTypesModel, &AdministratePhonesTypesModel::removePhoneType);
    
    // PhoneBook & AdministratePhonesTypes:
    
    QObject::connect(phoneBookView,      &PhoneBookView::administratePhoneTypes,              admPhonesTypesView, &AdministratePhonesTypesView::administratePhoneTypes);
    QObject::connect(admPhonesTypesView, &AdministratePhonesTypesView::administratePhoneBook, phoneBookView,      &PhoneBookView::administratePhoneBook);    
    
    phoneBookModel->initializeModels();
    admPhonesTypesModel->initializeModel();
    
    return true;
}
