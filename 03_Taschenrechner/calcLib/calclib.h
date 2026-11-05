#ifndef CALCLIB_H
#define CALCLIB_H

#include <QString>
#include "exprtk.hpp"   // Tipp: besser nur in der .cpp einbinden -> jede Datei, die calclib.h einbindet, kompiliert sonst exprtk mit (langsam)

class CalcLib
{
public:
    CalcLib();
    QString calculate(QString &rechnung);
};

#endif // CALCLIB_H
