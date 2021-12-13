#include "../../include/validators/initialsvalidator.h"

InitialsValidator::InitialsValidator(QObject *parent)
    : DataValidator(parent)
{
    setRegularExpression(QRegularExpression("^[A-ZА-Я]{1}[a-zа-я]{1,}$"));
}
