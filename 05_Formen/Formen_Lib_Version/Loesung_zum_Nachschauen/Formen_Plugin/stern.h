#ifndef STERN_H
#define STERN_H

#include "regelmaessigespolygon.h"

class PLUGIN Stern : public RegelmaessigesPolygon
{
public:
    Stern(int x = 0, int y = 0, int radius = 0, int zacken = 5);
    void draw(QPainter &painter);
    Form *parseForm(const QString &data);
};

#endif // STERN_H
