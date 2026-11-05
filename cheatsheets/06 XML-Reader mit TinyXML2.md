# Aufgabe 4 – XML-Explorer mit TinyXML2 (dynamisch + statisch)

Zurück: [00 Qt Cheat-Sheets Übersicht](00%20Qt%20Cheat-Sheets%20%C3%9Cbersicht.md) · Grundlagen: [02 Qt Grundlagen und Workflow](02%20Qt%20Grundlagen%20und%20Workflow.md) · Konzepte: [01 Konzepte C++ einfach erklärt](01%20Konzepte%20C%2B%2B%20einfach%20erkl%C3%A4rt.md)
Meine Projekte: App `/Users/justin/XML-Reader` · DLL `/Users/justin/TinyXML2` · statisch `/Users/justin/TinyXML2_Static`

**Ziel:** Button „Öffnen“ → Datei-Dialog → XML laden → als Baum im **QTreeWidget** anzeigen. Klick auf ein Element → daneben im Textfeld **Attribute und Inhalt**. TinyXML2 einmal als **dynamische** und einmal als **statische** Library gebaut.

**Was gelernt wird:** Library aus fremdem Code bauen, `QFileDialog`, Rekursion, Pointer-Ketten, `QTreeWidgetItem`, `QHash`, QString ↔ C-String.

---

## Bild im Kopf
- XML = verschachtelte Tags = **Baum**. Ein Tag = ein `XMLElement`. Ein Tag = eine Zeile im Baum (`QTreeWidgetItem`).
- `<preis waehrung="EUR">29.90</preis>`
  - `preis` → Name (`Name()`)
  - `waehrung="EUR"` → **Attribut** (`FirstAttribute()`, `Name()`, `Value()`)
  - `29.90` → **Inhalt** (`GetText()`)
- TinyXML spricht **C-Strings** (`const char*`), Qt spricht **QString** → an der Grenze immer umwandeln.

---

## Teil A – TinyXML2 als Library bauen

### Dynamisch (Shared Library)
1. Von GitHub `leethomason/tinyxml2` nur **`tinyxml2.h`** und **`tinyxml2.cpp`** holen
2. **Neues Projekt → Library → C++ Library**, qmake, Typ **Shared Library**, Name `TinyXML2`
3. Die generierte Klasse (`tinyxml2.h/.cpp` von Qt) **ersetzen** durch die zwei Original-Dateien (Rechtsklick → Vorhandene Dateien hinzufügen, alte entfernen)
4. Cmd+B → `libTinyXML2.dylib` im Build-Ordner
- `.pro` sieht dann so aus:
```
QT -= gui
TEMPLATE = lib
DEFINES += TINYXML2_LIBRARY
SOURCES += tinyxml2.cpp
HEADERS += TinyXML2_global.h tinyxml2.h
```

### Statisch
1. **Neues Projekt → Library → C++ Library**, Typ **Statically Linked Library**, Name `TinyXML2_Static`
2. Inhalt von `tinyxml2.h`/`.cpp` in die generierten Dateien kopieren (bei mir heißen sie `tinyxml2_static.h`/`.cpp` → in der `.cpp` den `#include` auf `"tinyxml2_static.h"` anpassen)
3. `.pro` hat `CONFIG += staticlib` → Cmd+B → `libTinyXML2_Static.a`

### Unterschied für den Test
- **Statisch (`.a`):** Code wird beim Linken **in die App kopiert**. App läuft allein. Lib geändert → App neu bauen.
- **Dynamisch (`.dylib`):** App lädt die Lib **beim Start**. Muss gefunden werden → `DYLD_LIBRARY_PATH` setzen (Projekte → Run → Umgebung) oder Lib neben die App.

---

## Teil B – App `XML-Reader`

### 1. Oberfläche
- `QPushButton` → `pushButton` (Text „XML öffnen“)
- **Tree Widget** (Item Widgets) → `treeWidget` (Doppelklick → Spaltenname „Element“)
- `QTextEdit` → `textEdit` (readOnly)
- Layout waagrecht (Baum links, Text rechts), Button darüber

### 2. Library einbinden (`.pro`)
- Rechtsklick App → **Bibliothek hinzufügen → Externe Bibliothek** → `.a` oder `.dylib` wählen
```
LIBS += -L$$PWD/../TinyXML2_Static/build/Qt_6_11_2_for_macOS_Debug/ -lTinyXML2_Static
INCLUDEPATH += $$PWD/../TinyXML2_Static
DEPENDPATH += $$PWD/../TinyXML2_Static
```
- Für die DLL-Variante: Pfade auf `TinyXML2` und `-lTinyXML2`, Include `tinyxml2.h`
- Danach qmake ausführen

### 3. `mainwindow.h`
```cpp
#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QHash>
#include "tinyxml2_static.h"          // bzw. "tinyxml2.h"

private slots:
    void on_pushButton_clicked();
    void on_treeWidget_itemSelectionChanged();

private:
    Ui::MainWindow *ui;
    tinyxml2::XMLDocument doc;                                   // MEMBER, nicht lokal!
    QHash<QTreeWidgetItem*, tinyxml2::XMLElement*> elemente;     // Zeile → XML-Element
    void fuelleBaum(tinyxml2::XMLElement *element, QTreeWidgetItem *item);
```
- **Warum `doc` Member?** Die `XMLElement*` gehören dem `doc`. Lokal im Slot → nach dem Slot weg → alle Zeiger zeigen ins Leere.
- **Warum `QHash`?** Das Baum-Item kennt keine Attribute. Die Tabelle merkt sich, welches XML-Element zu welcher Zeile gehört.

### 4. Öffnen-Slot
```cpp
#include <QFileDialog>
#include <QMessageBox>

void MainWindow::on_pushButton_clicked()
{
    QString pfad = QFileDialog::getOpenFileName(this, "XML-Datei öffnen", QDir::homePath(),
                                                "XML-Dateien (*.xml);;Alle Dateien (*)");
    if (pfad.isEmpty()) return;                                         // abgebrochen

    if (doc.LoadFile(pfad.toStdString().c_str()) != tinyxml2::XML_SUCCESS) {   // QString → C-String
        QMessageBox::warning(this, "Fehler", "Datei konnte nicht gelesen werden");
        return;
    }
    tinyxml2::XMLElement *wurzel = doc.RootElement();                   // oberstes Tag
    if (!wurzel) return;

    ui->treeWidget->clear();
    elemente.clear();
    fuelleBaum(wurzel, new QTreeWidgetItem(ui->treeWidget));           // Item mit Widget als Eltern = oberste Zeile
    ui->treeWidget->expandAll();
}
```

### 5. Rekursion – Baum füllen (while-Version, wie bei mir)
```cpp
void MainWindow::fuelleBaum(tinyxml2::XMLElement *element, QTreeWidgetItem *item)
{
    item->setText(0, QString::fromUtf8(element->Name()));    // Zeile beschriften
    elemente[item] = element;                                  // Zeile → Element merken

    tinyxml2::XMLElement *kind = element->FirstChildElement(); // erstes Kind
    while (kind != nullptr) {
        fuelleBaum(kind, new QTreeWidgetItem(item));           // Kind-Zeile unter dieser Zeile, rekursiv
        kind = kind->NextSiblingElement();                     // nächstes Geschwister – LETZTE Zeile!
    }
}
```
- **for-Version** (gleich):
```cpp
for (tinyxml2::XMLElement *kind = element->FirstChildElement(); kind; kind = kind->NextSiblingElement())
    fuelleBaum(kind, new QTreeWidgetItem(item));
```
- `new QTreeWidgetItem(item)` → neue Zeile **unter** `item`. Kein `delete` nötig (Eltern räumen auf).
- Rekursion endet von allein: Element ohne Kinder → Schleife läuft 0-mal.

### 6. Auswahl-Slot – Attribute + Inhalt anzeigen
```cpp
void MainWindow::on_treeWidget_itemSelectionChanged()
{
    QTreeWidgetItem *item = ui->treeWidget->currentItem();
    if (!item) return;                                          // nichts ausgewählt (z. B. beim Neuladen)
    tinyxml2::XMLElement *element = elemente.value(item);       // .value() → nullptr wenn nicht da
    if (!element) return;

    QString ausgabe;
    for (const tinyxml2::XMLAttribute *a = element->FirstAttribute(); a; a = a->Next()) {
        ausgabe += QString::fromUtf8(a->Name()) + " = " + QString::fromUtf8(a->Value()) + "\n";
    }
    if (ausgabe.isEmpty()) ausgabe = "Keine Attribute vorhanden\n";

    const char *text = element->GetText();                      // Inhalt, kann nullptr sein
    if (text) ausgabe += "Inhalt: " + QString::fromUtf8(text);

    ui->textEdit->setText(ausgabe);
}
```

---

## Erweiterung (falls verlangt): Attribut ändern und speichern
```cpp
element->SetAttribute("name", neuerWert.toStdString().c_str());   // QString → C-String
doc.SaveFile(pfad.toStdString().c_str());                          // pfad als Member merken
```

---

## TinyXML2 Funktionen auf einen Blick
- `doc.LoadFile(cstr)` → `XML_SUCCESS` wenn ok · `doc.SaveFile(cstr)` · `doc.RootElement()`
- `el->Name()` Tag-Name · `el->GetText()` Inhalt oder `nullptr`
- `el->FirstChildElement()` erstes Kind · `el->NextSiblingElement()` nächstes auf gleicher Ebene
- `el->FirstAttribute()` erstes Attribut · `a->Next()` nächstes · `a->Name()` · `a->Value()`
- `el->Attribute("id")` Wert eines bestimmten Attributs oder `nullptr` · `el->SetAttribute("id", "5")`

## QTreeWidget auf einen Blick
- `new QTreeWidgetItem(ui->treeWidget)` → oberste Zeile
- `new QTreeWidgetItem(elternItem)` → Unterzeile
- `item->setText(0, "Text")` (Spalte 0) · `item->text(0)`
- `ui->treeWidget->clear()` · `expandAll()` · `currentItem()` (kann `nullptr` sein)

## Umwandlungen (TinyXML ↔ Qt)
- **Qt → TinyXML:** `pfad.toStdString().c_str()` oder `pfad.toUtf8().constData()` (sicherer bei Umlauten)
- **TinyXML → Qt:** `QString::fromUtf8(el->Name())` → sonst Zeichensalat bei Umlauten

---

## Fallen (aus meinem Code)
- **`doc.LoadFile(pfad)`** mit QString → Typfehler. `.toStdString().c_str()`.
- **Kein `isEmpty()`-Check** nach dem Dialog und **kein Prüfen von `LoadFile`** (in meinem Projekt noch drin – nachrüsten).
- **`fuellebaum` statt `MainWindow::fuelleBaum`** → Linker `Undefined symbols`.
- **Rekursion nach der Schleife** statt darin → `kind` ist `nullptr` → Absturz.
- **`a->Next()` ohne `a =`** → Endlosschleife.
- **`currentItem()->…` ohne Prüfung** → Absturz, wenn nichts ausgewählt.
- **`qDebug() << el->FirstAttribute()`** zeigt Adressen (`0x…`, `0x0` = keins). Mit `->Name()`/`->Value()` öffnen.
- **`elemente[item]` zum Nachschauen** legt leere Einträge an → `elemente.value(item)`.
- **Inhalt (`GetText()`) fehlt** in meinem Projekt – Aufgabe verlangt „Attribute und falls vorhanden Inhalt“.
- Statische Lib geändert, App nicht neu gebaut → alte Version läuft.

## Testdateien
- `bibliothek.xml` und `schule.xml` (6 Ebenen, Umlaute, `&amp;`, leere Tags, Kommentar) liegen im Vault unter `testdateien/ (im Repo)`
- Bei `schule.xml` prüfen: Umlaute korrekt? `noten` von Lukas → kein Absturz? Kommentar nicht im Baum?
