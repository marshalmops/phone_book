#include "../../include/editors/phonetypeeditor.h"

PhoneTypeEditor::PhoneTypeEditor(QString &phoneType)
    : m_phoneType(phoneType)
{
    QLabel *phoneTypeLabel = new QLabel(tr("Тип телефона"));
    
    m_phoneTypeLineEdit = new QLineEdit();
    
    QPushButton *acceptButton  = new QPushButton(tr("Принять"));
    QPushButton *declineButton = new QPushButton(tr("Отменить"));
    
    QHBoxLayout *phoneTypeLayout = new QHBoxLayout();
    QHBoxLayout *buttonsLayout   = new QHBoxLayout();
    
    phoneTypeLayout->addWidget(phoneTypeLabel);
    phoneTypeLayout->addWidget(m_phoneTypeLineEdit);
    
    buttonsLayout->addStretch(1);
    buttonsLayout->addWidget(acceptButton);
    buttonsLayout->addWidget(declineButton);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    mainLayout->addLayout(phoneTypeLayout);
    mainLayout->addLayout(buttonsLayout);
    
    if (!phoneType.isEmpty()) {
        setWindowTitle(tr("Редактирование типа телефона"));
        
        m_phoneTypeLineEdit->setText(phoneType);
        
    } else
        setWindowTitle(tr("Добавление типа телефона"));
    
    connect(acceptButton,  &QPushButton::clicked, this, &PhoneTypeEditor::accept);
    connect(declineButton, &QPushButton::clicked, this, &QDialog::reject);
}

void PhoneTypeEditor::accept()
{
    QString phoneType = m_phoneTypeLineEdit->text();
    
    if (phoneType.isEmpty()) {
        QMessageBox::warning(this, tr("Ошибка"), tr("Необходимо ввести информацию полностью!"));
        
        return;
    }
    
    m_phoneType = phoneType;
    
    QDialog::accept();
}
