#ifndef ADMINISTRATEPHONESTYPESMODEL_H
#define ADMINISTRATEPHONESTYPESMODEL_H

#include <QObject>

#include "../database/databasefacades/databasefacade.h"
#include "../models/phonestypesmodel.h"

#include "../editors/phonetypeeditor.h"

class AdministratePhonesTypesModel : public QObject
{
    Q_OBJECT
public:
    explicit AdministratePhonesTypesModel(std::shared_ptr<DatabaseFacade> dbFacade, QObject *parent = nullptr);

public slots:
    void initializeModel();  
    
    void addPhoneType   ();
    void editPhoneType  (const QModelIndex index);
    void removePhoneType(const QModelIndex index);
    
signals:
    void showMessage    (const QMessageBox::Icon icon, const QString title, const QString message);    
    void setModel       (QAbstractItemModel *const phonesTypesModel);
    void resetSelection ();
    
private:
    std::shared_ptr<DatabaseFacadePhoneType> m_dbFacadePhoneType;
    
    PhonesTypesModel *m_phonesTypesModel;
    
    bool m_isModelInitialized;
};

#endif // ADMINISTRATEPHONESTYPESMODEL_H
