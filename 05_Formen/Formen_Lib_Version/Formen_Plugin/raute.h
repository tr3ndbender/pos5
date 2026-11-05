#ifndef RAUTE_H
#define RAUTE_H

#include "paralellogramm.h"

class PLUGIN Raute : public Paralellogramm
{
public:
    Raute(int x = 0, int y = 0, int seite = 0, int winkel = 0);
    Form *parseForm(const QString &data);
};

#endif // RAUTE_H
