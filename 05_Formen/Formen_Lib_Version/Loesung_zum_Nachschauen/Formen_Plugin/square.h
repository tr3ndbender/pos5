#ifndef SQUARE_H
#define SQUARE_H

#include "rectangle.h"

class PLUGIN Square : public Rectangle
{
public:
    Square(int x = 0, int y = 0, int seite = 0);
    Form *parseForm(const QString &data);
};

#endif // SQUARE_H
