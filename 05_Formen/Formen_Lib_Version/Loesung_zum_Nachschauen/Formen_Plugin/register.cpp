#include "register.h"
#include "square.h"
#include "rectangle.h"
#include "circle.h"
#include "trapez.h"
#include "dreieck.h"
#include "paralellogramm.h"
#include "ellipse.h"
#include "raute.h"
#include "regelmaessigespolygon.h"
#include "sechseck.h"
#include "stern.h"
#include "rechtwinkligesdreieck.h"
#include "unregelmaessigesdreieck.h"
#include <iostream>

bool registerForm(Factory *factory)
{
    std::cout << "Squaring up..." << std::endl;
    factory->registerForm(new Square());

    std::cout << "Circling up..." << std::endl;
    factory->registerForm(new Circle());

    std::cout << "Rectangling up..." << std::endl;
    factory->registerForm(new Rectangle());

    std::cout << "Trapezzing up..." << std::endl;
    factory->registerForm(new Trapez());

    std::cout << "Parallelogramming up..." << std::endl;
    factory->registerForm(new Paralellogramm());

    std::cout << "Triangling up..." << std::endl;
    factory->registerForm(new Dreieck());

    factory->registerForm(new Ellipse());
    factory->registerForm(new Raute());
    factory->registerForm(new RegelmaessigesPolygon());
    factory->registerForm(new Sechseck());
    factory->registerForm(new Stern());
    factory->registerForm(new RechtwinkligesDreieck());
    factory->registerForm(new UnregelmaessigesDreieck());

    return true;
}
