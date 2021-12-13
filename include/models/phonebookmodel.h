#ifndef PHONEBOOKMODEL_H
#define PHONEBOOKMODEL_H

#include <QObject>
#include <QSortFilterProxyModel>
#include <QMessageBox>

#include "../database/databasefacades/databasefacade.h"

#include "abonentsmodel.h"
#include "phonesmodel.h"
#include "phonestypesmodel.h"

#include "../editors/abonenteditor.h"
#include "../editors/phoneeditor.h"

class PhoneBookModel : public QObject
{
    Q_OBJECT
public:
    explicit PhoneBookModel(std::shared_ptr<DatabaseFacade> dbFacade, QObject *parent = nullptr);
    
signals:
    void setModels      (QAbstractItemModel *const abonentsModel, QAbstractItemModel *const phonesModel);    
    void showMessage    (const QMessageBox::Icon icon, const QString title, const QString message);
    void resetSelection ();
    
public slots:
    void clearPhonesModel();
    
    void addAbonent   ();
    void editAbonent  (const QModelIndex index);
    void removeAbonent(const QModelIndex index);
    
    void addPhone   (const QModelIndex abonentIndex);
    void editPhone  (const QModelIndex index);
    void removePhone(const QModelIndex index);
    
    void getPhonesOfAbonent(const QModelIndex index, const QModelIndex prevIndex);
    
    void initializeModels();
    
    void setSearchRegExp(QString pattern);
    
private:
    std::shared_ptr<DatabaseFacadeAbonent>   m_dbFacadeAbonent;
    std::shared_ptr<DatabaseFacadePhone>     m_dbFacadePhone;
    std::shared_ptr<DatabaseFacadePhoneType> m_dbFacadePhoneType;

    AbonentsModel *m_abonentsModel;
    PhonesModel   *m_phonesModel;
    
    QSortFilterProxyModel *m_abonentsProxyModel;
    QSortFilterProxyModel *m_phonesProxyModel;
    
    bool m_areModelsInitialized;
};

#endif // PHONEBOOKMODEL_H
