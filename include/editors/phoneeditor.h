#ifndef PHONEEDITOR_H
#define PHONEEDITOR_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QListView>
#include <QAbstractItemModel>
#include <QComboBox>

#include "../validators/phonevalidator.h"

class PhoneEditor : public QDialog
{
    Q_OBJECT
public:
    PhoneEditor(QString &number, quint64 &typeRow);
    
public slots:
    virtual void accept() override;
    
    void setPhonesModel(QAbstractItemModel *const phonesTypesModel);
    
private:
    QString &m_number;
    quint64 &m_typeRow;
    
    QComboBox *m_phoneTypeView;
    QLineEdit *m_numberLineEdit;
};

#endif // PHONEEDITOR_H
