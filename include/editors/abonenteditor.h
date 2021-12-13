#ifndef ABONENTEDITOR_H
#define ABONENTEDITOR_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

#include "../validators/initialsvalidator.h"

class AbonentEditor : public QDialog
{
public:
    AbonentEditor(QString &surname, QString &name, QString &patronymic);
    
public slots:
    virtual void accept() override;
    
private:
    QString &m_surname;
    QString &m_name;
    QString &m_patronymic;
    
    QLineEdit *m_surnameLineEdit;
    QLineEdit *m_nameLineEdit;
    QLineEdit *m_patronymicLineEdit;
};

#endif // ABONENTEDITOR_H
