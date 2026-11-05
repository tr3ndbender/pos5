# C++ Konzepte – einfach erklärt

Zurück zur Übersicht: [00 Qt Cheat-Sheets Übersicht](00%20Qt%20Cheat-Sheets%20%C3%9Cbersicht.md)

Jedes Konzept: **Bild im Kopf → Regel → Beispiel → Falle**.

---

## 1. Variable, Pointer, Referenz

### Variable
- **Bild:** Eine Schachtel mit einem Wert drin.
- `int a = 5;` → Schachtel `a`, Inhalt 5.

### Pointer (Zeiger) `*`
- **Bild:** Ein Zettel mit der **Adresse** einer Schachtel. Nicht der Wert, sondern *wo* der Wert liegt.
- `&a` = „Adresse von a“
- `*p` = „geh zur Adresse und nimm den Wert“
```cpp
int a = 5;
int *p = &a;     // p zeigt auf a
*p = 10;         // a ist jetzt 10
qDebug() << p;   // gibt eine ADRESSE aus (0x16b…)
qDebug() << *p;  // gibt 10 aus
```
- Bei Objekten: `p->methode()` statt `(*p).methode()`
- **`nullptr`** = Zettel ist leer, zeigt nirgendwohin. Darauf `->` → **Absturz**.
- **Regel:** Bevor du `->` machst, frag dich: kann das `nullptr` sein? Dann `if (!p) return;`
- **Falle:** `qDebug() << zeiger` zeigt `0x…` statt Text. `0x0` = nullptr.

### Wo kommen Pointer in Qt vor?
- `ui->btn00` ist ein Pointer auf den Button → deshalb `->setText(...)`
- `QPushButton *buttons[3][3];` = Array aus 9 Zetteln, die auf Buttons zeigen
- `new QTreeWidgetItem(...)` liefert einen Pointer
- TinyXML: `XMLElement *`, `XMLAttribute *`

### Referenz `&` (bei Parametern)
- **Bild:** Ein **zweiter Name** für dieselbe Schachtel. Kein Zettel, keine Kopie.
```cpp
void verdoppeln(int &x) { x = x * 2; }
int a = 5;
verdoppeln(a);   // a ist jetzt 10
```

### Die drei Parameter-Varianten
- `void f(QString s)` → **Kopie**. Änderungen bleiben in der Funktion. Original unberührt.
- `void f(const QString &s)` → **keine Kopie, nur lesen**. Ändern verboten (Compilerfehler). **Standard für Objekte**.
- `void f(QString &s)` → **keine Kopie, darf ändern**. Änderung wirkt **auch draußen**.
```cpp
void lesen(const QString &t)  { qDebug() << t; }       // ok
void kaputt(const QString &t) { t.append("x"); }       // FEHLER: const
void aendern(QString &t)      { t = t.toUpper(); }     // ok, Original wird groß
```
- **Regel:** Objekte (`QString`, `QList`, eigene Klassen) → `const Typ &`. Einfache Typen (`int`, `double`, `bool`) → einfach als Wert.
- **Falle:** Header und `.cpp` müssen exakt gleich sein. `const QString &` in der `.h`, `QString` in der `.cpp` → `does not match any declaration`.
- **Falle:** Eine `QString &` (ohne const) kann man nicht mit einem Literal aufrufen: `calc.calculate("1+2")` geht nicht, nur mit einer Variable.

### `&` hat zwei Bedeutungen
- In einer **Deklaration** (`int &x`, `const QString &s`) → Referenz
- Vor einer **Variable im Code** (`&a`, `toDouble(&ok)`) → „Adresse von“ → ergibt einen Pointer
- Beispiel `toDouble(&ok)`: Die Funktion bekommt die Adresse von `ok` und schreibt `true`/`false` hinein.

---

## 2. Speicher: Stack, Heap, new, delete

- **Stack:** normale Variablen (`int a;`, `QString s;`). Verschwinden automatisch am Ende des `{ }`-Blocks.
- **Heap:** mit `new` angelegt. Bleiben, bis jemand `delete` macht.
```cpp
QString *s = new QString("Hallo");
delete s;          // sonst Speicherleck
```
- **Qt-Regel (Parent-Ownership):** Ein Qt-Objekt mit **Eltern** wird vom Eltern-Objekt gelöscht. Deshalb kein `delete` bei:
  - `new QTreeWidgetItem(ui->treeWidget)` → gehört dem Widget
  - `new QTreeWidgetItem(item)` → gehört dem Eltern-Item
- `delete ui;` im Destruktor steht schon im Template, nicht anfassen.
- **Falle (Dangling Pointer):** Zeiger auf etwas, das schon weg ist. Beispiel: `tinyxml2::XMLDocument doc;` lokal im Slot → nach dem Slot ist `doc` weg, alle `XMLElement*` zeigen ins Leere. Deshalb `doc` als **Member** im Header.

---

## 3. Klasse und Objekt

- **Bild:** Klasse = **Bauplan**. Objekt = **gebautes Haus**.
- `class CalcLib { ... };` → Bauplan
- `CalcLib calc;` → ein gebautes Objekt
- **Methode aufrufen = auf dem Objekt:** `calc.calculate(text);`

### `.` vs `->` vs `::`
- `objekt.methode()` → normales Objekt (`calc.calculate()`, `text.toUpper()`)
- `zeiger->methode()` → Pointer (`ui->btn00->setText()`, `element->Name()`)
- `Klasse::methode` → nur
  - beim **Definieren** in der `.cpp`: `double CalcLib::calculate(...) { }`
  - bei **static**-Funktionen: `QString::number(5)`, `QFileDialog::getOpenFileName(...)`, `QMessageBox::warning(...)`
- **Falle:** `CalcLib::calculate(x)` → `Call to non-static member function without an object argument`. Lösung: Objekt anlegen, `calc.calculate(x)`.

### static
- `static` = gehört zur **Klasse**, nicht zu einem Objekt. Braucht kein Objekt.
```cpp
class Mathe { public: static int quadrat(int x) { return x * x; } };
int q = Mathe::quadrat(4);   // kein Objekt nötig
```

### public / private / protected
- `public` → alle dürfen zugreifen
- `private` → nur die Klasse selbst
- `protected` → die Klasse **und ihre Kinder** (abgeleitete Klassen)
- In Formen: `name`, `help`, `x`, `y` sind `protected` → `Rectangle`, `Square` usw. dürfen sie benutzen.

### Header `.h` vs `.cpp`
- **Bild:** `.h` = **Versprechen** („diese Funktion gibt es“). `.cpp` = **Erfüllung** (der Code).
```cpp
// mainwindow.h
private:
    void spielzug(int z, int s);          // Versprechen, mit ;

// mainwindow.cpp
void MainWindow::spielzug(int z, int s)   // Erfüllung, mit MainWindow::
{
    ...
}
```
- **Regel:** Alles, was in `class MainWindow` steht, beginnt in der `.cpp` mit `MainWindow::`.
- **Trick:** Cursor auf die Deklaration in der `.h` → **Option+Enter** → „Definition hinzufügen“.

### Compiler vs Linker
- **Compiler:** prüft jede `.cpp` einzeln, kennt Funktionen aus den Headern.
- **Linker:** sucht danach den echten Code (aus `.cpp` oder Library).
- `Use of undeclared identifier` → **Compiler** kennt den Namen nicht (fehlendes `MainWindow::`, Tippfehler, fehlender `#include`).
- `Undefined symbols … ld` → **Linker** findet den Code nicht (Name in `.h` und `.cpp` unterschiedlich, `MainWindow::` vergessen, Library nicht in `LIBS`).

---

## 4. Konstruktor und Initialisierungsliste

- **Konstruktor** = Funktion mit **genau dem Klassennamen**, läuft beim Erzeugen.
```cpp
class Rechteck : public Form {
protected:
    int breite;
    int hoehe;
public:
    Rechteck(int x = 0, int y = 0, int breite = 0, int hoehe = 0);   // .h
};

// .cpp
Rechteck::Rechteck(int x, int y, int breite, int hoehe)
    : Form("Rechteck", "Datenformat: x,y,breite,hoehe", x, y),   // 1. Basiskonstruktor
      breite(breite), hoehe(hoehe)                                // 2. Member setzen
{
}
```
- Nach dem `:` kommt die **Initialisierungsliste**: erst die Basisklasse, dann Member.
- `breite(breite)` heißt: Member `breite` = Parameter `breite`.
- **Standardwerte** (`= 0`) **nur in der `.h`** und nur **am Ende** (nach einem Default müssen alle weiteren auch einen haben).
- **Falle:** `Rechteck::rechteck` (klein) → falsch, Konstruktor heißt exakt wie die Klasse.

---

## 5. Vererbung

- **Bild:** Ein Kind bekommt alles von den Eltern und kann Dinge **dazubauen** oder **anders machen**.
- „Ein Quadrat **ist ein** Rechteck mit gleichen Seiten“ → `class Quadrat : public Rechteck`
```cpp
class Quadrat : public Rechteck {
public:
    Quadrat(int x = 0, int y = 0, int seite = 0);
    Form *parseForm(const QString &data);
};

Quadrat::Quadrat(int x, int y, int seite)
    : Rechteck(x, y, seite, seite)       // Eltern bauen lassen, Breite = Höhe
{
    name = "Quadrat";                    // protected → darf ich ändern
    help = "Datenformat: x,y,seite";
}
```
- Quadrat hat **kein eigenes `draw`** → es benutzt das von `Rechteck`. Das ist der Sinn: kein doppelter Code.
- **„Ist ein“-Test:** Quadrat ist ein Rechteck ✓ · Kreis ist eine Ellipse ✓ · Raute ist ein Parallelogramm ✓ · Sechseck ist ein regelmäßiges Polygon ✓

### virtual, override, abstrakt
- `virtual` = „Kinder dürfen diese Funktion **ersetzen**“. Beim Aufruf über einen Eltern-Pointer wird trotzdem die Kind-Version genommen.
- `= 0` = **rein virtuell** = „Kinder **müssen** sie schreiben“. Klasse wird **abstrakt** → kein Objekt davon möglich.
```cpp
class Form {
public:
    virtual void draw(QPainter &painter) = 0;          // jede Form MUSS draw haben
    virtual Form *parseForm(const QString &data) = 0;
};
```
- `new Form(...)` → Fehler, Form ist abstrakt. `new Rechteck(...)` → ok.

### Polymorphie
- **Bild:** Fernbedienung „Form zeichnen“ – jedes Gerät reagiert auf seine Art.
```cpp
QList<Form*> formen;
formen.append(new Rechteck(10, 10, 50, 30));
formen.append(new Kreis(100, 100, 20));
for (Form *f : formen)
    f->draw(painter);        // ruft je nach Objekt Rechteck::draw oder Ellipse::draw
```
- Die App kennt **keine einzige konkrete Form**, nur `Form*`. Neue Formen → App bleibt gleich.

### Virtueller Destruktor
- Wenn man über `Form*` löscht: `virtual ~Form() = default;` in der Basisklasse, sonst wird nur der Form-Teil aufgeräumt.

---

## 6. Schleifen

### Klassische for-Schleife (Zähler)
```cpp
for (int i = 0; i < 3; i++) { ... }          // i = 0, 1, 2
```
- Teil 1: Start · Teil 2: Bedingung (solange wahr) · Teil 3: Schritt

### Verschachtelt (2D-Feld, TicTacToe)
```cpp
for (int z = 0; z < 3; z++)
    for (int s = 0; s < 3; s++)
        feld[z][s] = 0;
```

### Range-for (über eine Liste)
```cpp
for (const QString &token : tokens) { ... }   // jedes Element der Liste
for (Form *f : formen) { ... }
```
- `const &` → keine Kopie, nicht ändern.

### Pointer-Kette (TinyXML: verkettete Liste)
```cpp
for (XMLElement *kind = root->FirstChildElement(); kind != nullptr; kind = kind->NextSiblingElement()) { ... }
for (const XMLAttribute *a = el->FirstAttribute(); a; a = a->Next()) { ... }
```
- **Falle:** `a->Next()` ohne `a =` → `a` ändert sich nie → **Endlosschleife**.

### while
```cpp
XMLElement *kind = root->FirstChildElement();
while (kind != nullptr) {
    ...
    kind = kind->NextSiblingElement();   // LETZTE Zeile, sonst endlos
}
```
- `for` = Weiterschalten im Kopf, `while` = Weiterschalten musst du selbst schreiben.

### break / continue / return
- `break` → Schleife sofort verlassen
- `continue` → diesen Durchlauf überspringen, nächster
- `return` → ganze Funktion verlassen (oft als Abbruch bei Fehler: `if (!item) return;`)

---

## 7. Rekursion

- **Bild:** Eine Funktion, die sich selbst für einen **kleineren Teil** aufruft. Wie russische Puppen.
- Braucht eine Stelle, an der sie **aufhört** (bei XML: Element hat keine Kinder → Schleife läuft nicht → fertig).
```cpp
void MainWindow::fuelleBaum(XMLElement *element, QTreeWidgetItem *item)
{
    item->setText(0, element->Name());
    for (XMLElement *kind = element->FirstChildElement(); kind; kind = kind->NextSiblingElement())
        fuelleBaum(kind, new QTreeWidgetItem(item));   // für jedes Kind: dasselbe nochmal
}
```
- **Falle:** Rekursiver Aufruf **nach** der Schleife statt **in** der Schleife → `kind` ist dann `nullptr` → Absturz.
- **Falle:** Rekursion ohne Ende (z. B. Zufalls-Zug, wenn kein Feld mehr frei ist) → Stack Overflow / Absturz.

---

## 8. Typen und Umwandlungen

- `int` ganze Zahl · `double` Kommazahl · `bool` true/false · `QString` Text · `const char*` C-Text
- `int / int` → **ganzzahlig**: `7 / 2 = 3`. Für Kommaergebnis: `7 / 2.0` oder `double`.
- `bool` speichert nur 0/1: `bool b = 2;` → `true` (=1). Deshalb Spieler als `int`.
- Zahl → Text: `QString::number(x)` · `QString::number(x, 'g', 12)` · `QString::number(x, 'f', 2)` (2 Nachkommastellen)
- Text → Zahl: `s.toInt(&ok)` · `s.toDouble(&ok)`
- QString → C-String (TinyXML): `s.toStdString().c_str()`
- C-String → QString: `QString::fromUtf8(text)`
- double → int (runden): `qRound(x)`
- Text zusammenbauen: `QString("Spieler %1 gewinnt").arg(spieler)` – **nicht** `"Spieler " + spieler` (Zeigerarithmetik!)

---

## 9. Merksätze

1. **`.h` = Versprechen, `.cpp` = Erfüllung** → beide exakt gleich.
2. **`MainWindow::`** vor jeder Methode in der `.cpp`.
3. **Pointer → vorher auf `nullptr` prüfen.**
4. **Objekte als `const &` übergeben**, ändern nur mit `&` ohne const.
5. **Methode auf Objekt (`.`), `::` nur beim Definieren oder bei static.**
6. **Kind ruft Eltern-Konstruktor in der Initialisierungsliste auf.**
7. **Schleife über Zeiger: immer `p = p->next()`.**
