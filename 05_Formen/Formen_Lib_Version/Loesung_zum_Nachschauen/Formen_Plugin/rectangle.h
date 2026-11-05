#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "register.h"

class PLUGIN Rectangle : public Form
{
protected:
    int width;
    int height;
public:
    Rectangle(int x = 0, int y = 0, int width = 0, int height = 0);
    void draw(QPainter &painter);
    Form *parseForm(const QString &data);
};

#endif // RECTANGLE_H
