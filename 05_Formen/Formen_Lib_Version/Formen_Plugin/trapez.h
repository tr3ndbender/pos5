#ifndef TRAPEZ_H
#define TRAPEZ_H

#include "register.h"

class PLUGIN Trapez : public Form
{
protected:
    int breite_oben;
    int breite_unten;
    int hoehe;
public:
    Trapez(int x = 0, int y = 0, int breite_oben = 0, int breite_unten = 0, int hoehe = 0);
    void draw(QPainter &painter);
    Form *parseForm(const QString &data);
};

#endif // TRAPEZ_H
