#ifndef DATAVALIDATOR_H
#define DATAVALIDATOR_H

#include <QRegularExpressionValidator>

class DataValidator : public QRegularExpressionValidator
{
    Q_OBJECT
public:
    DataValidator(QObject *parent = nullptr);
};

#endif // DATAVALIDATOR_H
