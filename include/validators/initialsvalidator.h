#ifndef INITIALSVALIDATOR_H
#define INITIALSVALIDATOR_H

#include "datavalidator.h"

class InitialsValidator : public DataValidator
{
public:
    InitialsValidator(QObject *parent = nullptr);
};

#endif // INITIALSVALIDATOR_H
