#include "ellipse.h"

Ellipse::Ellipse(int x, int y, int radiusX, int radiusY) : Form("Ellipse", "Datenformat: x,y,radius_x,radius_y", x, y), radiusX(radiusX), radiusY(radiusY)
{

}

void Ellipse::draw(QPainter &painter)
{
    // x,y ist der Mittelpunkt -> linke obere Ecke der Box = (x - radiusX, y - radiusY)
    painter.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap));
    painter.drawEllipse(x - radiusX, y - radiusY, 2 * radiusX, 2 * radiusY);
}

Form *Ellipse::parseForm(const QString &data)
{
    QStringList d = data.split(",");
    if(d.size() == 4)
    {
        return new Ellipse(d[0].toInt(), d[1].toInt(), d[2].toInt(), d[3].toInt());
    }
    return nullptr;
}
