#include "../include/appinitializer.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication  a(argc, argv);  
    
    PhoneBookView  pbView;
    
    if (!AppInitializer::initializeApp(&pbView))
        return 1;
    
    pbView.show();
    
    return a.exec();
}
