#include "../../include/validators/phonevalidator.h"

PhoneValidator::PhoneValidator(QObject *parent)
    : DataValidator(parent)
{
    setRegularExpression(QRegularExpression("^[+]{0,1}[0-9]{1,20}$"));
}
