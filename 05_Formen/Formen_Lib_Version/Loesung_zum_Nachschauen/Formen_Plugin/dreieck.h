#ifndef DREIECK_H
#define DREIECK_H

#include "register.h"

class PLUGIN Dreieck : public Form
{
protected:
    int breite;
    int hoehe;
public:
    Dreieck(int x = 0, int y = 0, int breite = 0, int hoehe = 0);
    void draw(QPainter &painter);
    Form *parseForm(const QString &data);
};

#endif // DREIECK_H
