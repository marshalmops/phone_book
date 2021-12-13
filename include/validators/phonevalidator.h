#ifndef PHONEVALIDATOR_H
#define PHONEVALIDATOR_H

#include "datavalidator.h"

class PhoneValidator : public DataValidator
{
    Q_OBJECT
public:
    explicit PhoneValidator(QObject *parent = nullptr);
};

#endif // PHONEVALIDATOR_H
