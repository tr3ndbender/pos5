#include "regelmaessigespolygon.h"
#include <QtMath>

RegelmaessigesPolygon::RegelmaessigesPolygon(int x, int y, int radius, int ecken) : Form("Polygon", "Datenformat: x,y,radius,ecken", x, y), radius(radius), ecken(ecken)
{

}

void RegelmaessigesPolygon::draw(QPainter &painter)
{
    // Ecken liegen auf einem Kreis um (x,y). Start oben (-90 Grad), dann im Uhrzeigersinn.
    QPolygon p;
    for (int i = 0; i < ecken; i++)
    {
        double rad = qDegreesToRadians(-90.0 + i * 360.0 / ecken);
        p << QPoint(x + qRound(radius * qCos(rad)), y + qRound(radius * qSin(rad)));
    }
    painter.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap));
    painter.drawPolygon(p);
}

Form *RegelmaessigesPolygon::parseForm(const QString &data)
{
    QStringList d = data.split(",");
    if(d.size() == 4)
    {
        return new RegelmaessigesPolygon(d[0].toInt(), d[1].toInt(), d[2].toInt(), d[3].toInt());
    }
    return nullptr;
}
