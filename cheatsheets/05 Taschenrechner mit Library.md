# Aufgabe 3 – Taschenrechner mit exprtk (als eigene Library)

Zurück: [00 Qt Cheat-Sheets Übersicht](00%20Qt%20Cheat-Sheets%20%C3%9Cbersicht.md) · Grundlagen: [02 Qt Grundlagen und Workflow](02%20Qt%20Grundlagen%20und%20Workflow.md) · Konzepte: [01 Konzepte C++ einfach erklärt](01%20Konzepte%20C%2B%2B%20einfach%20erkl%C3%A4rt.md)
Meine Projekte: App `/Users/justin/Taschenrechner_UE3_Ueben` · Lib `/Users/justin/calcLib`

**Ziel:** Taschenrechner mit Buttons (0–9, `.`, + − * /, Klammern, =) im Grid-Layout. Formel wird angezeigt, bei `=` rechnet **exprtk**. Rechnen steckt in einer **eigenen statischen Library** `calcLib`.

**Was gelernt wird:** Header-only-Library, eigene statische Library bauen und einbinden, Objekt einer Klasse benutzen, Auto-Connect vieler Buttons.

---

## Aufbau (Bild im Kopf)
- **calcLib (Library):** kann nur rechnen. Bekommt Text, gibt Ergebnis-Text zurück.
- **Taschenrechner (App):** Fenster, Buttons, Anzeige. Ruft `calc.calculate(rechnung)` auf.
- **exprtk:** eine einzige Datei `exprtk.hpp`, die Formeln wie `(2+3)*4` ausrechnet.

---

## Teil A – Library `calcLib`

### 1. Projekt
- **Neues Projekt → Library → C++ Library**, qmake, Typ **Statically Linked Library**, Name `calcLib`, Klasse `CalcLib`
- `exprtk.hpp` (aus dem ZIP von partow.net) in den Ordner `calcLib` kopieren → Rechtsklick Projekt → **Vorhandene Dateien hinzufügen**

### 2. `calclib.h`
```cpp
#ifndef CALCLIB_H
#define CALCLIB_H
#include <QString>

class CalcLib
{
public:
    CalcLib();
    QString calculate(const QString &rechnung);   // Methode der Klasse, NICHT im Konstruktor
};
#endif
```

### 3. `calclib.cpp`
```cpp
#include "calclib.h"
#include "exprtk.hpp"          // nur hier, nicht im Header → kompiliert schneller

CalcLib::CalcLib() {}

QString CalcLib::calculate(const QString &rechnung)
{
    exprtk::expression<double> ausdruck;     // hält die übersetzte Formel
    exprtk::parser<double> parser;           // übersetzt Text → Ausdruck

    if (!parser.compile(rechnung.toStdString(), ausdruck))
        return "Fehler";                     // Syntaxfehler, z. B. "2+"

    double ergebnis = ausdruck.value();      // ausrechnen
    if (std::isinf(ergebnis) || std::isnan(ergebnis))
        return "Fehler";                     // z. B. 5/0
    return QString::number(ergebnis, 'g', 12);
}
```
- `#include <cmath>` für `isinf`/`isnan` (meist schon über exprtk da)
- `'g', 12` → `1000000` statt `1e+06`, `0.1+0.2` → `0.3`. Mein Code hatte `'f', 2` → immer 2 Nachkommastellen (`3.00`), geht auch.

### 4. Bauen
- **Cmd+B** (dauert 1–3 Min wegen exprtk). Starten geht nicht – ist ja eine Lib.
- Ergebnis: `libcalcLib.a` in `calcLib/build/Qt_6_11_2_for_macOS_Debug/`

---

## Teil B – App `Taschenrechner`

### 1. Oberfläche
- `QLineEdit` → `rechnungLineEdit` (am besten `readOnly`)
- Buttons: `btn0`…`btn9`, `btnPlus`, `btnMinus`, `btnMal`, `btnDividiert`, `btnKomma`, `btnKlammerAuf`, `btnKlammerZu`, `btnAuswerten`
- Alle markieren → **Objekte tabellarisch anordnen**

### 2. Library einbinden (`.pro` der App)
- Rechtsklick auf App → **Bibliothek hinzufügen → Externe Bibliothek** → `libcalcLib.a` wählen → Qt schreibt:
```
LIBS += -L$$PWD/../calcLib/build/Qt_6_11_2_for_macOS_Debug/ -lcalcLib
INCLUDEPATH += $$PWD/../calcLib
DEPENDPATH += $$PWD/../calcLib
```
- Danach: **Build → qmake ausführen** → Cmd+B
- **Statisch:** Wenn du die Lib änderst → Lib neu bauen → App neu bauen.

### 3. `mainwindow.h`
```cpp
#include "calclib.h"

private:
    Ui::MainWindow *ui;
    QString rechnung = "";     // die aktuelle Formel
    CalcLib calc;              // Objekt der Library – unter private:, NICHT unter private slots:
```

### 4. Ziffern- und Operator-Buttons (Auto-Connect)
```cpp
void MainWindow::on_btn1_clicked()
{
    rechnung.append("1");                         // KEIN Leerzeichen anhängen
    ui->rechnungLineEdit->setText(rechnung);
}
void MainWindow::on_btnPlus_clicked()  { rechnung.append("+"); ui->rechnungLineEdit->setText(rechnung); }
void MainWindow::on_btnKomma_clicked() { rechnung.append("."); ui->rechnungLineEdit->setText(rechnung); }
// … genauso für alle anderen
```
- Kürzer mit **einem** Slot und `sender()`: siehe [02 Qt Grundlagen und Workflow](02%20Qt%20Grundlagen%20und%20Workflow.md#3-slots--auf-klicks-reagieren) (Abschnitt „Ein Slot für viele Buttons“)

### 5. Auswerten
```cpp
void MainWindow::on_btnAuswerten_clicked()
{
    if (rechnung.isEmpty()) return;
    QString ergebnis = calc.calculate(rechnung);    // auf dem OBJEKT aufrufen

    if (ergebnis == "Fehler") {
        rechnung.clear();                           // kaputte Formel verwerfen
        ui->rechnungLineEdit->setText("Fehler");
    } else {
        rechnung = ergebnis;                        // weiterrechnen mit dem Ergebnis
        ui->rechnungLineEdit->setText(rechnung);
    }
}
```
- Optional `btnClear`: `rechnung.clear(); ui->rechnungLineEdit->clear();`

---

## Variante ohne eigene Library (nur exprtk)
- `exprtk.hpp` direkt ins App-Projekt, in `mainwindow.cpp` ganz oben:
```cpp
#define exprtk_disable_enhanced_features   // optional: schneller kompilieren
#include "exprtk.hpp"
```
- Den Code aus `calculate` direkt in `on_btnAuswerten_clicked` schreiben.

## Variante dynamische Library (falls verlangt)
- Lib-Typ **Shared Library** → Qt erzeugt `calcLib_global.h` mit `CALCLIB_EXPORT`
- `class CALCLIB_EXPORT CalcLib { … };`
- Start-Fehler „Library not loaded“ → Projekte → Run → Umgebung → `DYLD_LIBRARY_PATH` = Build-Ordner der Lib

---

## Fallen (aus meinem Code)
- **Funktion in den Konstruktor geschrieben** (`CalcLib::CalcLib() { double calculate(...) }`) → eigene Methode.
- **`CalcLib::calculate(rechnung)`** → `Call to non-static member function without an object argument`. Richtig: `calc.calculate(rechnung)`.
- **`CalcLib calc;` unter `private slots:`** → `Not a signal or slot declaration`.
- **Run-Ziel war die Lib** → `No executable configured` → links unten App wählen.
- **Nach Einbinden nicht neu gebaut** → qmake ausführen, Cmd+B, Cmd+R.
- **Leerzeichen an jede Taste** (`append("1 ")`, vom UPN übernommen) → `1 2` statt `12` → Fehler.
- **`chop(1)`** schneidet beim zweiten `=` echte Zeichen ab.
- **Ergebnis nicht als neue `rechnung` gespeichert** → nächste Taste hängt an die alte Formel.
- `×`/`÷` auf Buttons → exprtk kennt nur `*` und `/`.
- `,` als Dezimaltrenner → vorher `rechnung.replace(',', '.')`.
- `QString &` ohne const im Parameter: geht, aber nur mit Variablen, nicht mit `"1+2"` direkt. `const QString &` ist sauberer.

## Testfälle
- `2+3*4` → 14 · `(2+3)*4` → 20 · `10/4` → 2.5
- `1000*1000` → 1000000 (nicht 1e+06)
- `2+` → Fehler · `5/0` → Fehler
- Nach Ergebnis weitertippen: `14` `+1` `=` → 15
