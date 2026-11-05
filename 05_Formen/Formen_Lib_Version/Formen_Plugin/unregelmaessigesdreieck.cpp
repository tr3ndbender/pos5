#include "unregelmaessigesdreieck.h"

// Punkt 1 = (x, y) aus Form, Punkt 2 = (x2, y2), Punkt 3 = (x3, y3)
UnregelmaessigesDreieck::UnregelmaessigesDreieck(int x, int y, int x2, int y2, int x3, int y3) : Form("Unregelmaessiges Dreieck", "Datenformat: x1,y1,x2,y2,x3,y3", x, y), x2(x2), y2(y2), x3(x3), y3(y3)
{

}

void UnregelmaessigesDreieck::draw(QPainter &painter)
{
    QPolygon p;
    p << QPoint(x, y);
    p << QPoint(x2, y2);
    p << QPoint(x3, y3);
    painter.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap));
    painter.drawPolygon(p);
}

Form *UnregelmaessigesDreieck::parseForm(const QString &data)
{
    QStringList d = data.split(",");
    if(d.size() == 6)
    {
        return new UnregelmaessigesDreieck(d[0].toInt(), d[1].toInt(), d[2].toInt(), d[3].toInt(), d[4].toInt(), d[5].toInt());
    }
    return nullptr;
}
