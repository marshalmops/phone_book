#ifndef APPINITIALIZER_H
#define APPINITIALIZER_H

#include "views/phonebookview.h"
#include "models/phonebookmodel.h"
#include "views/administratephonestypesview.h"
#include "models/administratephonestypesmodel.h"

#include "database/databasemanager.h"
#include "database/databasefacades/databasefacade.h"

class AppInitializer
{
public:
    AppInitializer() = delete;
    
    static bool initializeApp(PhoneBookView *phoneBookView);
};

#endif // APPINITIALIZER_H
