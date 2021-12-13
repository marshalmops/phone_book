#ifndef PHONETYPEEDITOR_H
#define PHONETYPEEDITOR_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

class PhoneTypeEditor : public QDialog
{
    Q_OBJECT
public:
    PhoneTypeEditor(QString &phoneType);
    
public slots:
    virtual void accept() override;
    
private:
    QString &m_phoneType;
    
    QLineEdit *m_phoneTypeLineEdit;
};

#endif // PHONETYPEEDITOR_H
