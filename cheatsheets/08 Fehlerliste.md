# Qt/C++ Fehlerliste – meine eigenen Fehler

Zurück: [00 Qt Cheat-Sheets Übersicht](00%20Qt%20Cheat-Sheets%20%C3%9Cbersicht.md)

> [!TIP] So benutzen
> Cmd+F mit dem **Wortlaut der Fehlermeldung** (z. B. `undeclared identifier`, `does not match`, `Undefined symbols`) oder mit dem **Stichwort** (z. B. `MainWindow::`, `pop`, `QPolygon`). Jeder Eintrag: **Symptom → Ursache → Fix**.

---

## 🔥 Top 10 – meine Wiederholungstäter

1. **`MainWindow::` / `Klasse::` vergessen** vor der Methode in der `.cpp` → `Use of undeclared identifier`, `Undefined symbols`. Siehe [Scope-Operator vergessen](#scope-operator-vergessen).
2. **Kopierte Klasse nicht vollständig umbenannt** (Name im Konstruktor, `include`, `Klasse::`, `new`, Member) → Duplikate, Form fehlt in der ComboBox. Siehe [Formen (Aufgabe 5)](#formen-aufgabe-5).
3. **Header und `.cpp` passen nicht zusammen** (Parameteranzahl, Name, Groß/Klein) → `does not match any declaration`.
4. **Zeiger weiterschalten vergessen**: `a->Next()` statt `a = a->Next()` → Endlosschleife.
5. **Nullpointer nicht geprüft** (`currentItem()`, `FirstAttribute()`, Stack leer) → Absturz.
6. **String + Zahl mit `+`** (`"Spieler " + currentPlayer`) → Zeigerarithmetik. `QString("...%1").arg(x)` nehmen.
7. **Falsche Reihenfolge**: Pop-Reihenfolge beim UPN, Punkt-Reihenfolge bei `drawPolygon` → falsches Ergebnis / Sanduhr.
8. **QString an C-API geben** (`LoadFile(pfad)`) → `pfad.toStdString().c_str()`.
9. **Ergebnis nicht gespeichert / zugewiesen** (`calc.calculate(x);` ohne `double r = ...`, Taschenrechner merkt Ergebnis nicht).
10. **Nach `.pro`-Änderung nicht neu qmake/bauen** → Lib nicht gefunden. Ablauf: **Build → qmake ausführen → Cmd+B → Cmd+R**.

---

## Allgemein C++

### Scope-Operator vergessen
- **Symptom:** `Use of undeclared identifier 'buttons'` / `'ui'`, oder Linker: `Undefined symbols for architecture arm64 … mainwindow.o`
- **Ursache:** Methode in der `.cpp` ohne `MainWindow::` geschrieben → freie Funktion, kennt keine Member.
- **Fix:** `void MainWindow::spielzug(int z, int s) { ... }`
- **Merke:** Alles, was in der `.h` in `class MainWindow` steht, beginnt in der `.cpp` mit `MainWindow::`. Trick: in der `.h` auf die Deklaration → **Option+Enter** → „Definition hinzufügen“.

### Name in .h und .cpp unterschiedlich
- **Symptom:** Linker-Fehler `Undefined symbols` (XML-Reader)
- **Ursache:** `.h`: `fuelleBaum`, `.cpp`: `fuellebaum` (kleines b) + kein `MainWindow::`
- **Fix:** Name exakt gleich, Groß-/Kleinschreibung zählt.

### Out-of-line definition does not match
- **Symptom:** `out-of-line definition of 'Rectangle' does not match any declaration in 'Rectangle'`
- **Ursache:** Konstruktor im Header hat 4 Parameter, in der `.cpp` nur 3 (oder anderer Typ/Name).
- **Fix:** Buchstabe für Buchstabe vergleichen: Name, Anzahl, Reihenfolge, Typen. Standardwerte (`= 0`) **nur im Header**.

### Konstruktorname falsch geschrieben
- **Fehler:** `Rectangle::rectangle(...)`
- **Fix:** `Rectangle::Rectangle(...)` – Konstruktor heißt **exakt** wie die Klasse.

### Standardwerte nicht am Ende
- **Fehler:** `Rectangle(int x = 0, int y = 0, int width = 0, int height);`
- **Ursache:** Nach einem Parameter mit Standardwert müssen **alle** weiteren auch einen haben.
- **Fix:** `int height = 0`

### Standardwerte in der .cpp wiederholt
- **Fehler:** `Paralellogramm::Paralellogramm(int x = 0, int y = 0, ...)` in der `.cpp`
- **Fix:** In der `.cpp` ohne `= 0`. Standardwerte gehören nur in die Deklaration (`.h`).

### Klammer zu viel
- **Fehler:** `... int winkel= 0)) : Form(...)`
- **Fix:** Genau eine `)`.

### Member nicht deklariert
- **Symptom:** `height` unbekannt in `draw`
- **Ursache:** Member nur im Konstruktor benutzt, aber im Header nie als `int height;` angelegt.
- **Fix:** Unter `protected:` deklarieren. Header-Member müssen zu den Konstruktor-Parametern passen.

### Initialisierungsliste mit falschen Membern
- **Fehler:** Parallelogramm hatte `breite_oben(breite_oben), breite_unten(...), hoehe(hoehe)` (vom Trapez kopiert), Parameter hießen aber `breite, laenge, winkel`.
- **Fix:** `breite(breite), laenge(laenge), winkel(winkel)` – und Header-Member gleich benennen.

### Variable verwendet, die es nicht gibt
- **Fehler:** `double l1 = b * qCos(rad);` – `b` existiert nicht.
- **Fix:** Den echten Membernamen benutzen.

### Anweisung ohne Aktion / ohne Semikolon
- **Fehler:** `buttons[z][s]` allein in einer Zeile
- **Fix:** Zeiger → `->`: `buttons[z][s]->setText("X");`

### String und Zahl mit + verbinden
- **Fehler:** `"Spieler " + currentPlayer + "gewinnt"`
- **Ursache:** `"..."` ist `const char*` → Zeigerarithmetik, kein Text.
- **Fix:** `QString("Spieler %1 gewinnt!").arg(currentPlayer)` oder `"Spieler " + QString::number(currentPlayer)`

### bool statt int (vermutet bei TicTacToe)
- **Symptom:** Es erscheint immer nur „X“, nie „O“.
- **Ursache:** `currentPlayer` als `bool` → `= 2` wird `true` = 1.
- **Fix:** `int currentPlayer;` Debug mit `qDebug() << currentPlayer;`

### Nicht initialisierte Variable
- **Fehler:** `gameRunning` im Konstruktor nie gesetzt → zufälliger Wert.
- **Fix:** Im Konstruktor `gameRunning = false;`

### Methode über Klassennamen aufgerufen
- **Symptom:** `Call to non-static member function without an object argument`
- **Fehler:** `CalcLib::calculate(rechnung);`
- **Fix:** Objekt anlegen (`CalcLib calc;` in der `.h`) und `double r = calc.calculate(rechnung);`
- **Merke:** `Klasse::` nur beim **Definieren** in der `.cpp` oder bei `static`-Methoden. Aufruf normal mit `objekt.methode()`.

### Funktion im Konstruktor deklariert
- **Fehler:**
  ```cpp
  CalcLib::CalcLib() {
      double calculate(QString rechnung)
  }
  ```
- **Fix:** Eigene Methode: in der `.h` `double calculate(const QString &rechnung);`, in der `.cpp` `double CalcLib::calculate(const QString &rechnung) { ... }`

### Rückgabewert weggeworfen
- **Fehler:** `calc.calculate(rechnung);` ohne Zuweisung
- **Fix:** `double ergebnis = calc.calculate(rechnung);` und anzeigen.

### Referenzen `&`
- `QString text` → Kopie, Original bleibt
- `const QString &text` → keine Kopie, **nicht** änderbar (Standard für Objekte zum Lesen)
- `QString &text` → keine Kopie, **ändert das Original**
- Header und `.cpp` müssen identisch sein, sonst `does not match`.

### Integer-Division
- `breite / 2` mit `int` schneidet ab. Für genau: `breite / 2.0`. Bei Grad→Bogenmaß `180.0` statt `180`.

---

## Qt allgemein

### QMessageBox mit zu wenig Parametern
- **Fehler:** `QMessageBox::information(this, "Text");`
- **Fix:** Fenster, **Titel**, Text: `QMessageBox::information(this, "Spielende", "Text");`

### Zufallszahl
- **Fehler:** `QRandomGenerator::global()->generate(1,3)`
- **Fix:** `QRandomGenerator::global()->bounded(1, 3)` → 1 oder 2 (obere Grenze **exklusiv**).

### Member in falschem Bereich
- **Symptom:** `Not a signal or slot declaration` + `[moc_mainwindow.cpp] Error 1`
- **Ursache:** `CalcLib calc;` unter `private slots:` geschrieben.
- **Fix:** Variablen unter `private:`, unter `private slots:` nur Slot-Funktionen.

### Initialisierung im falschen Slot
- **Fehler:** `buttons[0][0] = ui->btn00; ...` im Start-Slot statt im Konstruktor → Absturz, wenn vor „Start“ geklickt.
- **Fix:** Nach `ui->setupUi(this);` im Konstruktor.

### Flag gesetzt, aber nie geprüft
- **Fehler:** `gameRunning = true` gesetzt, in `spielzug` nie abgefragt.
- **Fix:** `if (!gameRunning || feld[z][s] != 0) return;`

### Layout im Designer
- Raster heißt auf Deutsch **„Objekte tabellarisch anordnen“** (Cmd+G).
- Buttons flach → **sizePolicy** beide auf `Expanding`, **minimumSize** z. B. 80×80.

### Schrift in Qt Creator verstellt
- Editor: **Einstellungen → Text Editor → Font & Colors** (Menlo, 12), Zoom zurück mit **Cmd+0**.
- Eigenes Programm: Eigenschaft `font` (fett = geändert) → Zurücksetzen-Pfeil, `styleSheet` prüfen.

### Hotkeys
- Vorschläge: **Ctrl+Leertaste** · Parameter-Hinweis: **Ctrl+Shift+Leertaste** · Quick-Fix: **Option+Enter** · Zur Definition: **Cmd+Klick**
- Umbenennen überall: **Cmd+Shift+R** (Rename Symbol) · Suchen/Ersetzen im Projekt: **Cmd+Shift+F** (Strings + Kommentare)

### Dateien nicht gespeichert
- **Symptom:** Änderungen kommen nicht an.
- **Fix:** **Cmd+S** bzw. „Alle speichern“ vor dem Bauen.
- Dialog „changed on disk“: **Yes to All** = Version von der Platte laden.

---

## Projekte, Kits, Libraries

### Kein Kit / „No suitable kits found“
- Kit rot markiert → **Show All Kits**, Maus aufs rote Symbol → Ursache lesen. Meist Compiler fehlt (`xcode-select --install`) oder Qt-Version-Pfad falsch (Einstellungen → Kits).
- Immer die **oberste** `.pro` öffnen (bei Subdirs `Formen_Gesamt.pro`), nicht einen Unterordner.

### Lib statt App gestartet
- **Symptom:** `No executable configured in the custom run configuration`
- **Ursache:** Run-Ziel ist die Library, eine Lib kann man nicht starten.
- **Fix:** Links unten (Monitor-Symbol) Run-Ziel auf die **App** stellen. Oder Projects → Run → Run configuration.

### Lib eingebunden, geht trotzdem nicht
- **Fix:** Nach Änderung der `.pro`: **Build → qmake ausführen**, dann Cmd+B, dann Cmd+R.
- `.pro` der App:
  ```
  INCLUDEPATH += $$PWD/../MeineLib
  LIBS += -L$$PWD/../lib -lMeineLib
  ```
- `'xyz.h' file not found` → `INCLUDEPATH` falsch
- `library not found for -lXYZ` → Pfad in `LIBS` falsch oder Lib nicht gebaut
- „Library not loaded“ beim Start (Mac) → Projects → Run → Umgebung: `DYLD_LIBRARY_PATH` = Ordner der Lib

### Header-Lib vs. kompilierte Lib
- **Mein Missverständnis:** exprtk müsse ich selbst kompilieren.
- **Richtig:** Header-only (exprtk) = nur Datei ins Projekt + `#include`. Statisch/dynamisch (TinyXML2) = `INCLUDEPATH` (Compiler) + `LIBS` (Linker), bei dynamisch muss die Lib zur Laufzeit gefunden werden.

---

## UPN-Rechner

### Zeichen einzeln prüfen
- **Fehler:** `eingabe[i].isNumber()` → `12` wären zwei Zeichen.
- **Fix:** `eingabe.split(' ', Qt::SkipEmptyParts)`, dann pro Token `token.toDouble(&ok)`.

### Pop-Reihenfolge
- **Fehler:** `numStack.push(numStack.pop() - numStack.pop());` → `3 4 -` ergibt 1 statt −1; Reihenfolge in C++ nicht mal festgelegt.
- **Fix:**
  ```cpp
  double b = numStack.pop();   // zuerst b (oben)
  double a = numStack.pop();
  numStack.push(a - b);
  ```

### Keine Prüfungen
- Vor dem Rechnen `if (numStack.size() < 2)` → Fehler, sonst Absturz.
- Division: `if (b == 0)` → Fehler.
- Ungültiges Token nicht ignorieren (leere `else`) → Fehlermeldung.
- Am Ende muss `numStack.size() == 1` sein.

### int statt double
- `QStack<int>` → `7 2 /` = 3. Für Kommazahlen `QStack<double>`.

---

## Taschenrechner (exprtk)

### Leerzeichen an jede Taste angehängt
- **Fehler:** `rechnung.append("1 ");` (vom UPN übernommen) → `1 2` statt `12` → exprtk-Fehler.
- **Fix:** `rechnung.append("1");`

### chop(1)
- **Fehler:** `chop(1)` beim Auswerten → beim zweiten „=“ wird ein echtes Zeichen abgeschnitten.
- **Fix:** Ohne Leerzeichen braucht man kein `chop`.

### Ergebnis nicht übernommen
- **Fehler:** Ergebnis nur angezeigt, `rechnung` behält alte Formel.
- **Fix:** `rechnung = QString::number(ergebnis, 'g', 12);` – bei Fehler `rechnung.clear();`

### Sonstiges
- `,` vor dem Rechnen durch `.` ersetzen: `formel.replace(',', '.')`
- `×`/`÷` kennt exprtk nicht → `*` und `/` auf die Buttons.
- Division durch 0 → `std::isinf(ergebnis) || std::isnan(ergebnis)` prüfen.
- `QString::number(x, 'g', 12)`, sonst `1e+06`.

---

## XML-Reader (TinyXML2)

### QString an TinyXML
- **Fehler:** `doc.LoadFile(pfad);`
- **Fix:** `doc.LoadFile(pfad.toStdString().c_str());` (oder `pfad.toUtf8().constData()`)
- Rückweg: `QString::fromUtf8(element->Name())`

### Keine Prüfungen beim Laden
- `if (pfad.isEmpty()) return;` (Abbrechen gedrückt)
- `if (doc.LoadFile(...) != tinyxml2::XML_SUCCESS) { Fehlermeldung; return; }`

### Rekursion an falscher Stelle
- **Fehler:** Rekursiver Aufruf **nach** der Schleife → `kind` ist `nullptr` → Absturz.
- **Fix:** Rekursion **in** der Schleife, einmal pro Kind.

### while-Schleife ohne Weiterschalten
- Letzte Zeile in der Schleife: `kind = kind->NextSiblingElement();` – sonst endlos.

### for-Schleife ohne Zuweisung
- **Symptom:** Endlosschleife
- **Fehler:** `for (... a = element->FirstAttribute(); a; a->Next())`
- **Fix:** `a = a->Next()` – `Next()` **liefert** nur den nächsten Zeiger, ändert `a` nicht.

### currentItem() ohne Prüfung
- **Fehler:** `ui->treeWidget->currentItem()->...` → Absturz, wenn nichts ausgewählt (z. B. beim Neuladen).
- **Fix:** `QTreeWidgetItem *item = ui->treeWidget->currentItem(); if (!item) return;`

### qDebug zeigt Adressen
- **Symptom:** `0xab77fd0a0` bzw. `0x0`
- **Ursache:** `FirstAttribute()` liefert einen **Zeiger**. `0x0` = `nullptr` = kein Attribut.
- **Fix:** `if (a) qDebug() << a->Name() << a->Value();`

### QHash: [] statt value()
- `elemente[item]` legt einen leeren Eintrag an, wenn es den Schlüssel nicht gibt. Zum Nachschauen `elemente.value(item)`.

### Attribute vs. Inhalt
- Attribut: `name="wert"` im öffnenden Tag (`FirstAttribute()`, `->Next()`, `->Name()`, `->Value()`)
- Inhalt: Text zwischen den Tags (`GetText()`, kann `nullptr` sein)

---

## Formen (Aufgabe 5)

### Square kopiert, nicht umgebaut
- **Fehler:** In `rectangle.h` stand noch `class PLUGIN Square`, `rectanlge.cpp` hatte `#include "square.h"` und `Square::` → doppelte Definition von `Square`.
- **Fix:** Klassenname, Include, alle `Klasse::`, `new Klasse(...)` umbenennen.
- **Tippfehler im Dateinamen:** `rectanlge.cpp` → `rectangle.cpp` (auch in der `.pro`).

### Draw mit falscher Klasse
- **Fehler:** `void Square::draw(...)` in `rectangle.cpp`
- **Fix:** `void Rectangle::draw(...)`

### Form erscheint nicht in der ComboBox
- **Ursache 1:** Im Konstruktor falscher Name weitergegeben: `Trapez(...) : Form("Rectangle", ...)` → überschreibt/kollidiert mit Rectangle.
- **Ursache 2:** In `register.cpp` fehlt `#include "xyz.h"` oder `factory->registerForm(new Xyz());`
- **Ursache 3:** Dateien nicht in `.pro` unter `SOURCES`/`HEADERS`.

### Checkliste beim Kopieren einer Klasse
1. `.h`: Include-Guard, Klassenname, Basisklasse, Member, Konstruktor-Signatur
2. `.cpp`: `#include`, `Klasse::Klasse(...)`, Name + Hilfetext im `Form(...)`-Aufruf, Initialisierungsliste
3. `draw`: richtige Member, `Klasse::draw`
4. `parseForm`: richtige Feldanzahl (`d.size() == n`), `new Klasse(...)` mit allen Werten
5. `register.cpp`: Include + `registerForm(new Klasse())`
6. `.pro`: Dateien eingetragen
7. **Cmd+S**, Cmd+B, testen

### drawRect für schräge Formen
- `drawRect` nur für Rechtecke. Für Trapez, Parallelogramm, Dreieck … `QPolygon` + `drawPolygon`.

### Punkte falsch angelegt
- **Fehler:** `QPoint punkte[0] = (1,2);` – `(1,2)` ist in C++ kein Punkt.
- **Fix:**
  ```cpp
  QPolygon p;
  p << QPoint(x, y) << QPoint(x + b, y) << QPoint(x + b, y + h) << QPoint(x, y + h);
  painter.drawPolygon(p);
  ```

### Sanduhr statt Viereck
- **Ursache:** Punkte nicht **um die Form herum** angegeben (oben links → oben rechts → unten **links** → unten rechts).
- **Fix:** Reihenfolge: oben links → oben rechts → **unten rechts** → **unten links**. Mit dem Finger einmal den Rand abfahren.
- Bei **3 Punkten** ist die Reihenfolge egal.

### y-Achse
- In Qt wächst **y nach unten**. `y + h` = weiter unten. Mathe-Skizze (y nach oben) sonst auf den Kopf.
- `(x, y)` sinnvoll als linke obere Ecke der Box (wie beim Rechteck).

### Trapez-Punkte (gleichschenklig, Bu unten, Bo oben)
- P1 `(x + (Bu-Bo)/2, y)` · P2 `(x + (Bu-Bo)/2 + Bo, y)` · P3 `(x + Bu, y + h)` · P4 `(x, y + h)`

### Parallelogramm / Raute (Trigonometrie)
- Schräge Seite `b`, Winkel `α`: `h = b · sin(α)`, Versatz `L1 = b · cos(α)` (SOH-CAH-TOA)
- Punkte: `(x + L1, y)`, `(x + L1 + grundseite, y)`, `(x + grundseite, y + h)`, `(x, y + h)`
- **Bogenmaß!** `qDegreesToRadians(winkel)` bzw. `winkel * M_PI / 180.0`, `#include <QtMath>`
- `double` → `QPoint` mit `qRound(...)` (oder `QPointF`/`QPolygonF`)
- Namen klar halten: `breite` war bei mir die **schräge** Seite → besser `seite` / `grundseite`, sonst Verwechslung bei der Eingabe.

### Vererbung – kein eigenes draw nötig
- **Missverständnis:** Square, Circle, Raute, Sechseck „haben kein draw“.
- **Richtig:** Sie **erben** `draw` von Rectangle / Ellipse / Parallelogramm / RegelmaessigesPolygon. Nur Konstruktor (ruft Basiskonstruktor auf) + `parseForm`.
  ```cpp
  Square::Square(int x, int y, int seite) : Rectangle(x, y, seite, seite)
  {
      name = "Square";
      help = "Datenformat: x,y,seite";
  }
  ```
- Damit das geht: Member der Basisklasse `protected`, nicht `private`.

### Rectangle als Klassenname
- Unter Windows gibt es eine API-Funktion `Rectangle()` → mögliche Konflikte am Schul-PC. Sicherer: `Rechteck`.

---

## Mentale Modelle

- **Klasse = Bauplan, Objekt = gebautes Ding.** Methoden ruft man auf dem Objekt auf.
- **`.h` = Versprechen, `.cpp` = Erfüllung.** Beide müssen exakt übereinstimmen.
- **Compiler** prüft Deklarationen, **Linker** sucht die Körper. `Undefined symbols` = Körper fehlt oder heißt anders.
- **Jeder Zeiger kann `nullptr` sein**, bevor du `->` machst, prüfen.
- **Nach jeder Klasse sofort bauen und testen**, nicht alles schreiben und dann debuggen.
