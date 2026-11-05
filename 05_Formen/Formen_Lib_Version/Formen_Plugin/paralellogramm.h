#ifndef PARALELLOGRAMM_H
#define PARALELLOGRAMM_H

#include "register.h"

class PLUGIN Paralellogramm : public Form
{
protected:
    int breite;
    int laenge;
    int winkel;
public:
    Paralellogramm(int x = 0, int y = 0, int breite = 0, int laenge=0, int winkel= 0);
    void draw(QPainter &painter);
    Form *parseForm(const QString &data);
};

#endif // PARALELLOGRAMM_H
