#include "../../include/views/phonebookview.h"

PhoneBookView::PhoneBookView(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle(tr("Телефонный справочник"));
    
    QPushButton *addAbonentButton    = new QPushButton("+A");
    QPushButton *editAbonentButton   = new QPushButton("EA");
    QPushButton *removeAbonentButton = new QPushButton("-A");
    
    QPushButton *addPhoneButton    = new QPushButton("+T");
    QPushButton *editPhoneButton   = new QPushButton("ET");
    QPushButton *removePhoneButton = new QPushButton("-T");
    
    QPushButton *administratePhoneTypesButton = new QPushButton("ATT");
    
    QLabel *searchLabel = new QLabel(tr("Найти"));
    
    m_searchLineEdit = new QLineEdit();
    
    m_searchLineEdit->setValidator(new InitialsValidator(this));
    
    QHBoxLayout *searchLayout = new QHBoxLayout();
    
    searchLayout->addWidget(searchLabel);
    searchLayout->addWidget(m_searchLineEdit);
    
    QHBoxLayout *actionsLayout = new QHBoxLayout();
    
    actionsLayout->addWidget(addAbonentButton);
    actionsLayout->addWidget(editAbonentButton);
    actionsLayout->addWidget(removeAbonentButton);
    actionsLayout->addWidget(addPhoneButton);
    actionsLayout->addWidget(editPhoneButton);
    actionsLayout->addWidget(removePhoneButton);
    actionsLayout->addWidget(administratePhoneTypesButton);
    actionsLayout->addStretch(1);
    actionsLayout->addLayout(searchLayout);
    
    QLabel *abonentsLabel = new QLabel(tr("Абоненты"));
    
    m_abonentsTableView = new QTableView();
    
    m_abonentsTableView->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
    m_abonentsTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    m_abonentsTableView->verticalHeader()->hide();
    m_abonentsTableView->setSortingEnabled(true);
    
    QVBoxLayout *abonentsLayout = new QVBoxLayout();
    
    abonentsLayout->addWidget(abonentsLabel);
    abonentsLayout->addWidget(m_abonentsTableView);
    
    QLabel *phonesLabel = new QLabel(tr("Телефоны"));
    
    m_phonesTableView = new QTableView();
    
    m_phonesTableView->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
    m_phonesTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    m_phonesTableView->verticalHeader()->hide();
    m_phonesTableView->setSortingEnabled(true);
    
    QVBoxLayout *phonesLayout = new QVBoxLayout();
    
    phonesLayout->addWidget(phonesLabel);
    phonesLayout->addWidget(m_phonesTableView);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    mainLayout->addLayout(actionsLayout);
    mainLayout->addLayout(abonentsLayout);
    mainLayout->addLayout(phonesLayout);
    
    connect(addAbonentButton,    &QPushButton::clicked, this, &PhoneBookView::addAbonent);
    connect(editAbonentButton,   &QPushButton::clicked, this, &PhoneBookView::prepareEditAbonent);
    connect(removeAbonentButton, &QPushButton::clicked, this, &PhoneBookView::prepareRemoveAbonent);

    connect(addPhoneButton,    &QPushButton::clicked, this, &PhoneBookView::prepareAddPhone);
    connect(editPhoneButton,   &QPushButton::clicked, this, &PhoneBookView::prepareEditPhone);
    connect(removePhoneButton, &QPushButton::clicked, this, &PhoneBookView::prepareRemovePhone);

    connect(administratePhoneTypesButton, &QPushButton::clicked, this, &PhoneBookView::prepareAdministratePhoneTypes);

    connect(m_searchLineEdit, &QLineEdit::textChanged, this, &PhoneBookView::setSearchRegExp);
}

PhoneBookView::~PhoneBookView()
{
    
}

void PhoneBookView::showMessage(const QMessageBox::Icon icon, const QString title, const QString message)
{
    QMessageBox(icon, title, message).exec();
}

void PhoneBookView::setModels(QAbstractItemModel *const abonentsModel, QAbstractItemModel *const phonesModel)
{
    m_abonentsTableView->setModel(abonentsModel);
    m_phonesTableView->setModel(phonesModel);

    m_abonentsTableView->hideColumn(0);
    m_phonesTableView->hideColumn(0);
    
    connect(m_abonentsTableView->selectionModel(), &QItemSelectionModel::currentRowChanged, this, &PhoneBookView::getPhonesOfAbonent);
}

void PhoneBookView::resetSelection()
{
    m_abonentsTableView->selectionModel()->reset();
    m_phonesTableView->selectionModel()->reset();
}

void PhoneBookView::administratePhoneBook()
{
    show();
}

void PhoneBookView::prepareEditAbonent()
{
    QModelIndex curIndex = m_abonentsTableView->currentIndex();
    
    if (!curIndex.isValid()) {
        QMessageBox::warning(this, tr("Ошибка"), tr("Вы должны выбрать абонента!"));
        
        return;
    }
    
    emit editAbonent(curIndex);
}

void PhoneBookView::prepareRemoveAbonent()
{
    QModelIndex curIndex = m_abonentsTableView->currentIndex();
    
    if (!curIndex.isValid()) {
        QMessageBox::warning(this, tr("Ошибка"), tr("Вы должны выбрать абонента!"));
        
        return;
    }
    
    if (QMessageBox::question(this, tr("Удаление абонента"), tr("Вы уверены, что хотите удалить выбранного абонента?")) != QMessageBox::StandardButton::Yes)
        return;
        
    emit removeAbonent(curIndex);
}

void PhoneBookView::prepareAddPhone()
{
    QModelIndex curIndex = m_abonentsTableView->currentIndex();
    
    if (!curIndex.isValid()) {
        QMessageBox::warning(this, tr("Ошибка"), tr("Вы должны выбрать абонента!"));
        
        return;
    }
    
    emit addPhone(curIndex);
}

void PhoneBookView::prepareEditPhone()
{
    QModelIndex curIndex = m_phonesTableView->currentIndex();
    
    if (!curIndex.isValid()) {
        QMessageBox::warning(this, tr("Ошибка"), tr("Вы должны выбрать телефон!"));
        
        return;
    }
    
    emit editPhone(curIndex);
}

void PhoneBookView::prepareRemovePhone()
{
    QModelIndex curIndex = m_phonesTableView->currentIndex();
    
    if (!curIndex.isValid()) {
        QMessageBox::warning(this, tr("Ошибка"), tr("Вы должны выбрать телефон!"));
        
        return;
    }
    
    if (QMessageBox::question(this, tr("Удаление телефона"), tr("Вы уверены, что хотите удалить выбранный телефон?")) != QMessageBox::StandardButton::Yes)
        return;
    
    emit removePhone(curIndex);
}

void PhoneBookView::prepareAdministratePhoneTypes()
{
    resetSelection();
    hide();
    
    emit clearPhonesModel();
    emit administratePhoneTypes();
}
