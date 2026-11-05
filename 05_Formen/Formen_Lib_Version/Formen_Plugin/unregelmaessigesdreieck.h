#ifndef UNREGELMAESSIGESDREIECK_H
#define UNREGELMAESSIGESDREIECK_H

#include "register.h"

class PLUGIN UnregelmaessigesDreieck : public Form
{
protected:
    int x2;
    int y2;
    int x3;
    int y3;
public:
    UnregelmaessigesDreieck(int x = 0, int y = 0, int x2 = 0, int y2 = 0, int x3 = 0, int y3 = 0);
    void draw(QPainter &painter);
    Form *parseForm(const QString &data);
};

#endif // UNREGELMAESSIGESDREIECK_H
