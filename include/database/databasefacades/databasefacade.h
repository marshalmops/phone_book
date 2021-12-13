#ifndef DATABASEFACADE_H
#define DATABASEFACADE_H

#include <QVector>

#include "../databasemanager.h"
#include "databasefacadeabonent.h"
#include "databasefacadephone.h"
#include "databasefacadephonetype.h"

class DatabaseFacade
        : public DatabaseFacadeAbonent,
          public DatabaseFacadePhone,
          public DatabaseFacadePhoneType
{
public:
    DatabaseFacade()  = default;
    ~DatabaseFacade() = default;
};

#endif // DATABASEFACADE_H
