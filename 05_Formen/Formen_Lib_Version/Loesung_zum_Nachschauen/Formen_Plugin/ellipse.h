#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "register.h"

class PLUGIN Ellipse : public Form
{
protected:
    int radiusX;
    int radiusY;
public:
    Ellipse(int x = 0, int y = 0, int radiusX = 0, int radiusY = 0);
    void draw(QPainter &painter);
    Form *parseForm(const QString &data);
};

#endif // ELLIPSE_H
