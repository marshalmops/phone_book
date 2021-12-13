#include "../../include/editors/abonenteditor.h"

AbonentEditor::AbonentEditor(QString &surname, 
                             QString &name, 
                             QString &patronymic)
    : m_surname   (surname),
      m_name      (name),
      m_patronymic(patronymic)
{
    QLabel *surnameLabel    = new QLabel(tr("Фамилия"));
    QLabel *nameLabel       = new QLabel(tr("Имя"));
    QLabel *patronymicLabel = new QLabel(tr("Отчество"));
    
    m_surnameLineEdit    = new QLineEdit();
    m_nameLineEdit       = new QLineEdit();
    m_patronymicLineEdit = new QLineEdit();
    
    InitialsValidator *initialsValidator = new InitialsValidator(this);
    
    m_surnameLineEdit->setValidator(initialsValidator);
    m_nameLineEdit->setValidator(initialsValidator);
    m_patronymicLineEdit->setValidator(initialsValidator);
            
    QPushButton *acceptButton  = new QPushButton(tr("Принять"));
    QPushButton *declineButton = new QPushButton(tr("Отменить"));

    QVBoxLayout *labelLayout   = new QVBoxLayout();
    QVBoxLayout *inputLayout   = new QVBoxLayout();
    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    
    labelLayout->addWidget(surnameLabel);
    labelLayout->addWidget(nameLabel);
    labelLayout->addWidget(patronymicLabel);
    
    inputLayout->addWidget(m_surnameLineEdit);
    inputLayout->addWidget(m_nameLineEdit);
    inputLayout->addWidget(m_patronymicLineEdit);
    
    buttonsLayout->addStretch(1);
    buttonsLayout->addWidget(acceptButton);
    buttonsLayout->addWidget(declineButton);
    
    QHBoxLayout *formLayout = new QHBoxLayout();
    
    formLayout->addLayout(labelLayout);
    formLayout->addLayout(inputLayout);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(buttonsLayout);
    
    if (!surname.isEmpty()) {
        setWindowTitle(tr("Редактирование абонента"));
        
        m_surnameLineEdit->setText(surname);
        m_nameLineEdit->setText(name);
        m_patronymicLineEdit->setText(patronymic);
        
    } else
        setWindowTitle(tr("Добавление абонента"));
    
    connect(acceptButton,  &QPushButton::clicked, this, &AbonentEditor::accept);
    connect(declineButton, &QPushButton::clicked, this, &QDialog::reject);
}

void AbonentEditor::accept()
{
    QString surname    = m_surnameLineEdit->text();
    QString name       = m_nameLineEdit->text();
    QString patronymic = m_patronymicLineEdit->text();
    
    if (surname.isEmpty()
     || name.isEmpty()
     || patronymic.isEmpty())
    {
        QMessageBox::warning(this, tr("Ошибка"), tr("Необходимо ввести информацию полностью!"));
        
        return;
    }
    
    m_surname    = surname;
    m_name       = name;
    m_patronymic = patronymic;
    
    QDialog::accept();
}
