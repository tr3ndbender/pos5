#ifndef ACHTECK_H
#define ACHTECK_H

#include "regelmaessigespolygon.h"

class PLUGIN Achteck : public RegelmaessigesPolygon
{
public:
    Achteck(int x = 0, int y = 0, int radius = 0);
    Form *parseForm(const QString &data);
};

#endif // ACHTECK_H
