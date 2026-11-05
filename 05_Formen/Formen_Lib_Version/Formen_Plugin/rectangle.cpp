#include "rectangle.h"
#include <iostream>

Rectangle::Rectangle(int x, int y, int width, int height) : Form("Rectangle", "Datenformat: x,y,breite,höhe", x, y), width(width), height(height)
{

}

void Rectangle::draw(QPainter &painter)
{
    painter.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap));
    painter.drawRect(x,y,width,height);
}

Form *Rectangle::parseForm(const QString &data)
{
    QStringList d = data.split(",");
    if(d.size() == 4)
    {
        return new Rectangle(d[0].toInt(), d[1].toInt(), d[2].toInt(), d[3].toInt());
    }
    return nullptr;
}
