#ifndef PHONEBOOKVIEW_H
#define PHONEBOOKVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QTableView>
#include <QLineEdit>
#include <QMessageBox>
#include <QHeaderView>
#include <QAbstractItemModel>

#include "../validators/initialsvalidator.h"

class PhoneBookView : public QWidget
{
    Q_OBJECT
    
public:
    PhoneBookView(QWidget *parent = nullptr);
    ~PhoneBookView();
    
public slots:
    void showMessage   (const QMessageBox::Icon icon, const QString title, const QString message);
    void setModels     (QAbstractItemModel * const abonentsModel, QAbstractItemModel * const phonesModel);
    void resetSelection();
    
    void administratePhoneBook();
    
signals:
    void clearPhonesModel();
    
    void addAbonent   ();
    void editAbonent  (const QModelIndex index);
    void removeAbonent(const QModelIndex index);
    
    void addPhone   (const QModelIndex abonentIndex);
    void editPhone  (const QModelIndex index);
    void removePhone(const QModelIndex index);
    
    void getPhonesOfAbonent(const QModelIndex index, const QModelIndex prevIndex);
    
    void administratePhoneTypes();
    
    void setSearchRegExp(QString pattern);
    
private slots: 
    void prepareEditAbonent  ();
    void prepareRemoveAbonent();
    
    void prepareAddPhone   ();
    void prepareEditPhone  ();
    void prepareRemovePhone();
    
    void prepareAdministratePhoneTypes();
    
private:
    QTableView *m_abonentsTableView;
    QTableView *m_phonesTableView;
    
    QLineEdit *m_searchLineEdit;
};
#endif // PHONEBOOKVIEW_H
