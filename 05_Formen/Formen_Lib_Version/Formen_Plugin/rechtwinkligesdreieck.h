#ifndef RECHTWINKLIGESDREIECK_H
#define RECHTWINKLIGESDREIECK_H

#include "dreieck.h"

class PLUGIN RechtwinkligesDreieck : public Dreieck
{
public:
    RechtwinkligesDreieck(int x = 0, int y = 0, int breite = 0, int hoehe = 0);
    void draw(QPainter &painter);
    Form *parseForm(const QString &data);
};

#endif // RECHTWINKLIGESDREIECK_H
