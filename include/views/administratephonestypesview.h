#ifndef ADMINISTRATEPHONESTYPESVIEW_H
#define ADMINISTRATEPHONESTYPESVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QListView>
#include <QLineEdit>
#include <QMessageBox>

class AdministratePhonesTypesView : public QWidget
{
    Q_OBJECT
public:
    explicit AdministratePhonesTypesView(QWidget *parent = nullptr);
    
public slots:
    void administratePhoneTypes();
    void showMessage           (const QMessageBox::Icon icon, const QString title, const QString message);
    void setModel              (QAbstractItemModel * const phonesTypesModel);
    void resetSelection        ();
    
signals:
    void addPhoneType   ();
    void editPhoneType  (const QModelIndex index);
    void removePhoneType(const QModelIndex index);
    
    void administratePhoneBook();    
    
private slots:
    void prepareEditPhoneType        ();
    void prepareRemovePhoneType      ();
    void prepareAdministratePhoneBook();
    
private:
    QListView *m_phonesTypesListView;
};

#endif // ADMINISTRATEPHONESTYPESVIEW_H
