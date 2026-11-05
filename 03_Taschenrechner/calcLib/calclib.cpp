#include "calclib.h"


CalcLib::CalcLib() {
}


    QString CalcLib::calculate(/*const*/ QString &rechnung) { //ohne const hätte ich die Möglichkeit die Variable zu verändern!
        // exprtk in 3 Schritten: Ausdruck-Objekt, Parser, compile() -> value()
        exprtk::expression<double> ausdruck;   // hält die „übersetzte“ Formel
        exprtk::parser<double> parser;         // übersetzt Text in einen Ausdruck

        if (parser.compile(rechnung.toStdString(), ausdruck)) {   // false bei Syntaxfehler (z. B. "2+")

            return QString::number(ausdruck.value(), 'f', 2);

        } else {
            return QString("Fehler"); //Casten warum auch immer

        }
    }

