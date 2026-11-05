# Qt Grundlagen und Workflow

Zurück zur Übersicht: [00 Qt Cheat-Sheets Übersicht](00%20Qt%20Cheat-Sheets%20%C3%9Cbersicht.md) · Konzepte: [01 Konzepte C++ einfach erklärt](01%20Konzepte%20C%2B%2B%20einfach%20erkl%C3%A4rt.md)

---

## 1. Neues Projekt anlegen (immer gleich)
1. **Datei → Neues Projekt → Application (Qt) → Qt Widgets Application**
2. Name ohne Leerzeichen, z. B. `TicTacToe`. Ort: `/Users/justin/`
3. **Build System: qmake** (nicht CMake)
4. Klasse: `MainWindow`, Basis `QMainWindow`, **„Generate form“ angehakt**
5. Kit: **Qt 6.11.2 for macOS** anhaken → Fertig

Du bekommst: `.pro`, `main.cpp`, `mainwindow.h`, `mainwindow.cpp`, `mainwindow.ui`. **`main.cpp` nie anfassen.**

## 2. Designer (`mainwindow.ui` doppelklicken)
- Widgets links aus der Widget-Box ziehen
- **objectName** rechts oben sofort sinnvoll setzen (`btnStart`, `eingabeLe`, `treeWidget`). Der Name ist später `ui->name`.
- Präfix-Idee: `btn…` Button · `le…`/`…Le` LineEdit · `lbl…` Label · `cmb…` ComboBox

### Layouts (Pflicht in den Aufgaben)
- Widgets markieren → Rechtsklick → **Layout**:
  - **Objekte tabellarisch anordnen** (Cmd+G) = Raster/Grid
  - **Objekte waagrecht anordnen** = nebeneinander
  - **Objekte senkrecht anordnen** = untereinander
- Ganzes Fenster: auf leere Fläche (oder `centralwidget` im Objekt-Inspektor) → Layout wählen → alles skaliert mit
- Buttons zu flach → markieren → **sizePolicy** beide `Expanding`, **minimumSize** z. B. 80×80
- Rückgängig: Cmd+Z, „Layout auflösen“

### ComboBox befüllen
- Doppelklick auf die ComboBox → Einträge mit `+` hinzufügen (z. B. „Mensch“, „PC“)
- Im Code: `ui->cmbSpieler1->currentText()` oder `currentIndex()`

## 3. Slots – auf Klicks reagieren

### Auto-Connect (Standard)
1. Rechtsklick auf den Button → **Slot anzeigen… → clicked()**
2. Qt Creator legt **automatisch** an:
   - in der `.h` unter `private slots:` → `void on_btnStart_clicked();`
   - in der `.cpp` → `void MainWindow::on_btnStart_clicked() { }`
3. Name-Schema: `on_<objectName>_<signal>()` – wenn du den objectName danach änderst, funktioniert es **nicht mehr**.

### Wichtige Signale
- `QPushButton` → `clicked()`
- `QTreeWidget` → `itemSelectionChanged()` (oder `itemClicked(QTreeWidgetItem*, int)`)
- `QComboBox` → `currentTextChanged(const QString &)`
- `QLineEdit` → `returnPressed()`, `textChanged(const QString &)`

### Ein Slot für viele Buttons (`sender()`)
```cpp
// .h unter private slots:
void tasteGedrueckt();

// Konstruktor nach setupUi:
connect(ui->btn1, &QPushButton::clicked, this, &MainWindow::tasteGedrueckt);
connect(ui->btn2, &QPushButton::clicked, this, &MainWindow::tasteGedrueckt);

// .cpp
void MainWindow::tasteGedrueckt()
{
    QPushButton *taste = qobject_cast<QPushButton*>(sender());   // wer hat geklickt?
    if (!taste) return;
    rechnung.append(taste->text());
}
```
- Alle Buttons automatisch: `for (QPushButton *t : findChildren<QPushButton*>()) connect(...);`
- **Achtung:** Nicht zusätzlich Auto-Connect-Namen verwenden, sonst doppelt ausgelöst.

## 4. Grundgerüst `.h` – wohin gehört was?
```cpp
#include <QMainWindow>
#include <QPushButton>        // Typen, die du im Header benutzt

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:                 // NUR Slot-Funktionen
    void on_btnStart_clicked();

private:                       // Variablen + Hilfsfunktionen
    Ui::MainWindow *ui;
    int feld[3][3];
    void spielzug(int z, int s);
};
```
- **Falle:** Variable unter `private slots:` → `Not a signal or slot declaration`.
- Initialisierung (Startwerte, Arrays mit `ui->...` füllen) → im **Konstruktor nach `ui->setupUi(this);`**

## 5. Die wichtigsten Qt-Bausteine

### Text lesen / schreiben
```cpp
QString t = ui->eingabeLe->text();          // QLineEdit lesen
ui->eingabeLe->setText("...");              // schreiben
ui->ergebnisLbl->setText("...");            // QLabel
ui->textEdit->setText("...");               // QTextEdit ersetzen
ui->textEdit->append("Zeile");              // QTextEdit anhängen
ui->textEdit->clear();
ui->btn00->setText("X");                    // Button-Beschriftung
```

### QMessageBox (`#include <QMessageBox>`)
```cpp
QMessageBox::information(this, "Titel", "Text");
QMessageBox::warning(this, "Fehler", "Text");
QMessageBox::critical(this, "Fehler", "Text");
```
- **Immer drei Teile:** `this`, Titel, Text.

### QString – was du brauchst
```cpp
s.append("x");                 // anhängen (ändert s)
s.isEmpty();                   // leer?
s.length();                    // Länge
s.clear();                     // leeren
s.split(' ', Qt::SkipEmptyParts);   // → QStringList
s.replace(',', '.');           // ersetzen (ändert s)
s.chop(1);                     // letztes Zeichen weg (ändert s!)
s.trimmed();                   // Leerzeichen vorne/hinten weg (neuer String)
s.toInt(&ok); s.toDouble(&ok); // Text → Zahl, ok sagt ob es geklappt hat
QString::number(3.5);          // Zahl → Text
QString("Spieler %1 hat %2").arg(spieler).arg(punkte);
```

### Zufall (`#include <QRandomGenerator>`)
```cpp
int r = QRandomGenerator::global()->bounded(1, 3);   // 1 oder 2 (obere Grenze exklusiv)
int i = QRandomGenerator::global()->bounded(9);      // 0 bis 8
```

### Stack (`#include <QStack>`)
```cpp
QStack<double> st;
st.push(5);  double x = st.pop();  st.top();  st.size();  st.isEmpty();
```

### Liste / Map
```cpp
QList<Form*> formen;  formen.append(f);  for (Form *f : formen) {...}
QHash<QTreeWidgetItem*, XMLElement*> map;  map[key] = wert;  map.value(key);  map.clear();
```
- `map.value(key)` → gibt `nullptr` zurück, wenn nicht da. `map[key]` legt einen leeren Eintrag an.

### Debug-Ausgabe (`#include <QDebug>`)
```cpp
qDebug() << "Wert:" << x;     // erscheint unten in „Anwendungsausgabe“
```

### Datei-Dialog (`#include <QFileDialog>`)
```cpp
QString pfad = QFileDialog::getOpenFileName(this, "XML öffnen", QDir::homePath(),
                                            "XML-Dateien (*.xml);;Alle Dateien (*)");
if (pfad.isEmpty()) return;    // Abbrechen gedrückt
```
- `tr("...")` aus der Doku = Übersetzung, brauchst du nicht.

## 6. Libraries einbinden (allgemein)

### Drei Arten
- **Header-only** (exprtk): Datei ins Projekt, `#include` → fertig. Wird mitkompiliert.
- **Statisch** (`CONFIG += staticlib`, `.a`): wird **beim Linken in die App kopiert**. Nach Lib-Änderung App neu bauen.
- **Dynamisch** (`.dylib` auf Mac, `.dll` Windows): wird **zur Laufzeit geladen**. Muss beim Start gefunden werden.

### Library-Projekt anlegen
- **Neues Projekt → Library → C++ Library** → qmake → Typ: *Shared Library* (dynamisch) oder *Statically Linked Library*
- Dynamisch: Qt erzeugt `xyz_global.h` mit `XYZ_EXPORT` → vor die Klasse schreiben: `class XYZ_EXPORT CalcLib`
- Lib bauen: Cmd+B (eine Lib kann man **nicht starten**)

### In der App einbinden (einfachster Weg)
- Rechtsklick auf App-Projekt → **Bibliothek hinzufügen… → Externe Bibliothek** → Datei der Lib wählen → Qt schreibt `LIBS` + `INCLUDEPATH` in die `.pro`
- Oder von Hand in der App-`.pro`:
```
INCLUDEPATH += $$PWD/../calcLib
LIBS += -L$$PWD/../calcLib/build/Qt_6_11_2_for_macOS_Debug/ -lcalcLib
```
- `-L` = Ordner, `-l` = Name **ohne** `lib` und **ohne** Endung
- Danach: **Build → qmake ausführen** → Cmd+B → Cmd+R

### Mac: dynamische Lib wird beim Start nicht gefunden
- Fehler „Library not loaded“ → **Projekte → Run → Umgebung** → `DYLD_LIBRARY_PATH` = Ordner mit der `.dylib`

### Fehlerbilder
- `'xyz.h' file not found` → `INCLUDEPATH` falsch
- `library not found for -lxyz` → `-L`-Pfad falsch oder Lib nicht gebaut
- `Undefined symbols` → Lib nicht in `LIBS`, oder Funktion nicht exportiert
- `No executable configured` → Run-Ziel ist die Lib → links unten auf die **App** umstellen

## 7. Ablauf beim Programmieren (Test-Routine)
1. Oberfläche bauen, objectNames setzen, Layout
2. Slots per Rechtsklick anlegen
3. **Kleinster Schritt → Cmd+B → Cmd+R → testen** → nächster Schritt
4. Bei Fehler: **erste** Meldung in „Probleme“ lesen, nicht die zehnte
5. Nach `.pro`-Änderung: qmake ausführen
6. Cmd+S nicht vergessen

## 8. Hotkeys (Mac)
- **Cmd+B** bauen · **Cmd+R** starten · **Cmd+S** speichern
- **Ctrl+Leertaste** Vorschläge · **Ctrl+Shift+Leertaste** Parameter-Hinweis
- **Option+Enter** Quick-Fix (z. B. Definition in `.cpp` erzeugen)
- **Cmd+Klick** zur Definition · **F4** zwischen `.h` und `.cpp` wechseln
- **Cmd+Shift+R** Symbol überall umbenennen · **Cmd+Shift+F** im Projekt suchen/ersetzen
- **Cmd+G** im Designer: Raster-Layout
