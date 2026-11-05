#ifndef SECHSECK_H
#define SECHSECK_H

#include "regelmaessigespolygon.h"

class PLUGIN Sechseck : public RegelmaessigesPolygon
{
public:
    Sechseck(int x = 0, int y = 0, int radius = 0);
    Form *parseForm(const QString &data);
};

#endif // SECHSECK_H
