#ifndef REGELMAESSIGESPOLYGON_H
#define REGELMAESSIGESPOLYGON_H

#include "register.h"

class PLUGIN RegelmaessigesPolygon : public Form
{
protected:
    int radius;
    int ecken;
public:
    RegelmaessigesPolygon(int x = 0, int y = 0, int radius = 0, int ecken = 3);
    void draw(QPainter &painter);
    Form *parseForm(const QString &data);
};

#endif // REGELMAESSIGESPOLYGON_H
