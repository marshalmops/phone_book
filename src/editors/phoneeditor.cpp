#include "../../include/editors/phoneeditor.h"

PhoneEditor::PhoneEditor(QString &number, quint64 &typeRow)
    : m_number (number),
      m_typeRow(typeRow)
{
    QLabel *numberLabel = new QLabel(tr("Номер"));
    QLabel *typeLabel   = new QLabel(tr("Тип телефона"));
    
    m_numberLineEdit = new QLineEdit();
    m_phoneTypeView  = new QComboBox();
    
    m_numberLineEdit->setValidator(new PhoneValidator(this));
    
    QPushButton *acceptButton  = new QPushButton(tr("Принять"));
    QPushButton *declineButton = new QPushButton(tr("Отменить"));
    
    QVBoxLayout *labelLayout   = new QVBoxLayout();
    QVBoxLayout *inputLayout   = new QVBoxLayout();
    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    
    labelLayout->addWidget(numberLabel);
    labelLayout->addWidget(typeLabel);
    
    inputLayout->addWidget(m_numberLineEdit);
    inputLayout->addWidget(m_phoneTypeView);
    
    buttonsLayout->addStretch(1);
    buttonsLayout->addWidget(acceptButton);
    buttonsLayout->addWidget(declineButton);
    
    QHBoxLayout *formLayout = new QHBoxLayout();
    
    formLayout->addLayout(labelLayout);
    formLayout->addLayout(inputLayout);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(buttonsLayout);
    
    if (!number.isEmpty()) {
        setWindowTitle(tr("Редактирование телефона"));
        
        m_numberLineEdit->setText(number);
        
    } else
        setWindowTitle(tr("Добавление телефона"));
    
    connect(acceptButton,  &QPushButton::clicked, this, &PhoneEditor::accept);
    connect(declineButton, &QPushButton::clicked, this, &QDialog::reject);
}

void PhoneEditor::accept()
{
    QString number  = m_numberLineEdit->text();
    quint64 typeRow = m_phoneTypeView->currentIndex();
    
    if (number.isEmpty()
     ||!(m_phoneTypeView->currentIndex() >= 0))
    {
        QMessageBox::warning(this, tr("Ошибка"), tr("Необходимо ввести информацию полностью!"));
        
        return;
    }
    
    m_number  = number;
    m_typeRow = typeRow;
    
    QDialog::accept();
}

void PhoneEditor::setPhonesModel(QAbstractItemModel *const phonesTypesModel)
{
    m_phoneTypeView->setModel(phonesTypesModel);
    m_phoneTypeView->setCurrentIndex(m_typeRow);
    //m_phoneTypeView->setCurrentIndex(phonesTypesModel->index(m_typeRow, 0));
}
