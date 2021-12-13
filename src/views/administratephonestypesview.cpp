#include "../../include/views/administratephonestypesview.h"

AdministratePhonesTypesView::AdministratePhonesTypesView(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle(tr("Администрирование типов телефонов"));
    
    QPushButton *addPhoneTypeButton    = new QPushButton("+ТТ");
    QPushButton *editPhoneTypeButton   = new QPushButton("EТТ");
    QPushButton *removePhoneTypeButton = new QPushButton("-ТТ");
    
    QPushButton *administratePhoneBookButton = new QPushButton("AТС");
    
    QHBoxLayout *actionsLayout = new QHBoxLayout();
    
    actionsLayout->addWidget(addPhoneTypeButton);
    actionsLayout->addWidget(editPhoneTypeButton);
    actionsLayout->addWidget(removePhoneTypeButton);
    actionsLayout->addWidget(administratePhoneBookButton);
    
    QLabel *phonesTypesLabel = new QLabel(tr("Типы телефонов"));
    
    m_phonesTypesListView = new QListView();
    
    m_phonesTypesListView->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
    m_phonesTypesListView->setSelectionMode(QAbstractItemView::SingleSelection);
    
    QVBoxLayout *phonesTypesLayout = new QVBoxLayout();
    
    phonesTypesLayout->addWidget(phonesTypesLabel);
    phonesTypesLayout->addWidget(m_phonesTypesListView);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    mainLayout->addLayout(actionsLayout);
    mainLayout->addLayout(phonesTypesLayout);
    
    connect(addPhoneTypeButton,    &QPushButton::clicked, this, &AdministratePhonesTypesView::addPhoneType);
    connect(editPhoneTypeButton,   &QPushButton::clicked, this, &AdministratePhonesTypesView::prepareEditPhoneType);
    connect(removePhoneTypeButton, &QPushButton::clicked, this, &AdministratePhonesTypesView::prepareRemovePhoneType);

    connect(administratePhoneBookButton, &QPushButton::clicked, this, &AdministratePhonesTypesView::prepareAdministratePhoneBook);
}

void AdministratePhonesTypesView::administratePhoneTypes()
{
    show();
}

void AdministratePhonesTypesView::showMessage(const QMessageBox::Icon icon, const QString title, const QString message)
{
    QMessageBox(icon, title, message).exec();    
}

void AdministratePhonesTypesView::setModel(QAbstractItemModel * const phonesTypesModel)
{
    m_phonesTypesListView->setModel(phonesTypesModel);
}

void AdministratePhonesTypesView::resetSelection()
{
    m_phonesTypesListView->selectionModel()->reset();
}

void AdministratePhonesTypesView::prepareEditPhoneType()
{
    QModelIndex curIndex = m_phonesTypesListView->currentIndex();
    
    if (!curIndex.isValid()) {
        QMessageBox::warning(this, tr("Ошибка"), tr("Вы должны выбрать тип телефона!"));
        
        return;
    }
    
    emit editPhoneType(curIndex);
}

void AdministratePhonesTypesView::prepareRemovePhoneType()
{
    QModelIndex curIndex = m_phonesTypesListView->currentIndex();
    
    if (!curIndex.isValid()) {
        QMessageBox::warning(this, tr("Ошибка"), tr("Вы должны выбрать тип телефона!"));
        
        return;
    }
    
    if (QMessageBox::question(this, tr("Удаление типа телефона"), tr("Вы уверены, что хотите удалить выбранный тип телефона?")) != QMessageBox::StandardButton::Yes)
        return;
        
    emit removePhoneType(curIndex);
}

void AdministratePhonesTypesView::prepareAdministratePhoneBook()
{
    hide();
    
    emit administratePhoneBook();
}
