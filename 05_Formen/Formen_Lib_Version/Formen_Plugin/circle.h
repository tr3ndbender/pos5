#ifndef CIRCLE_H
#define CIRCLE_H

#include "ellipse.h"

class PLUGIN Circle : public Ellipse
{
public:
    Circle(int x = 0, int y = 0, int radius = 0);
    Form *parseForm(const QString &data);
};

#endif // CIRCLE_H
