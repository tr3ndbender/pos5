# Qt Cheat-Sheets – Übersicht für die praktische Arbeit

Alles, um jede Übung nur mit diesen Notizen nachzuprogrammieren (Mac, Qt 6.11.2, qmake).

## Zuerst lesen
- [01 Konzepte C++ einfach erklärt](01%20Konzepte%20C%2B%2B%20einfach%20erkl%C3%A4rt.md) – Pointer, Referenz, const, Klasse/Objekt, Vererbung, Schleifen, Rekursion
- [02 Qt Grundlagen und Workflow](02%20Qt%20Grundlagen%20und%20Workflow.md) – Projekt anlegen, Designer, Layouts, Slots, QString, QMessageBox, Libraries, Hotkeys
- [08 Fehlerliste](08%20Fehlerliste.md) – alle meine Fehler mit Fehlermeldung, Ursache, Fix

## Aufgaben
1. [03 TicTacToe](03%20TicTacToe.md) – Grid, Auto-Connect, 2D-Array, Gewinnprüfung, PC-Gegner
2. [04 UPN-Rechner](04%20UPN-Rechner.md) – QStack, split, toDouble(&ok)
3. [05 Taschenrechner mit Library](05%20Taschenrechner%20mit%20Library.md) – exprtk, eigene statische Library calcLib
4. [06 XML-Reader mit TinyXML2](06%20XML-Reader%20mit%20TinyXML2.md) – QFileDialog, QTreeWidget, Rekursion, TinyXML2 dynamisch + statisch
5. [07 Formen Factory und Vererbung](07%20Formen%20Factory%20und%20Vererbung.md) – abstrakte Klasse, Vererbung, Factory, QPainter, UML

## Was suche ich wo? (Stichwort → Note)
- Fehlermeldung → [08 Fehlerliste](08%20Fehlerliste.md) (Cmd+F mit dem Wortlaut)
- `MainWindow::`, `.` vs `->` vs `::`, `const &` → [01 Konzepte C++ einfach erklärt](01%20Konzepte%20C%2B%2B%20einfach%20erkl%C3%A4rt.md)
- Button-Klick, Slot, `sender()`, Layout → [02 Qt Grundlagen und Workflow](02%20Qt%20Grundlagen%20und%20Workflow.md)
- Library einbinden, `LIBS`, `INCLUDEPATH`, `DYLD_LIBRARY_PATH` → [02 Qt Grundlagen und Workflow](02%20Qt%20Grundlagen%20und%20Workflow.md) Abschnitt 6
- Zufall, 2D-Array, `? :` → [03 TicTacToe](03%20TicTacToe.md)
- Stack, Text zerlegen, Text → Zahl → [04 UPN-Rechner](04%20UPN-Rechner.md)
- Formel auswerten, exprtk → [05 Taschenrechner mit Library](05%20Taschenrechner%20mit%20Library.md)
- Datei öffnen, Baum, Rekursion, verkettete Liste, QHash → [06 XML-Reader mit TinyXML2](06%20XML-Reader%20mit%20TinyXML2.md)
- Vererbung, `virtual`, `drawPolygon`, sin/cos, UML → [07 Formen Factory und Vererbung](07%20Formen%20Factory%20und%20Vererbung.md)

## Test-Routine (immer gleich)
1. Angabe lesen → in **kleine Schritte** zerlegen (welche Widgets, welche Slots, welche Daten)
2. Projekt anlegen (qmake, MainWindow mit Form) → Oberfläche + objectNames + Layout
3. Header: Member + Hilfsfunktionen unter `private:`, Slots per Rechtsklick
4. **Ein Schritt → Cmd+B → Cmd+R → testen**
5. Fehler? Erste Meldung lesen → [08 Fehlerliste](08%20Fehlerliste.md)
6. Fehlerfälle abfangen (leer, nullptr, Division durch 0, falsche Eingabe)
7. Am Ende: Test-Checkliste der Aufgabe durchgehen

## Meine 5 Wiederholungsfehler
1. `MainWindow::` / `Klasse::` vergessen
2. Kopierte Klasse nur halb umbenannt
3. Header und `.cpp` passen nicht zusammen
4. Zeiger in Schleifen nicht weitergeschaltet (`a = a->Next()`)
5. Nach `.pro`-Änderung nicht qmake ausgeführt

## Projekte auf dem Mac
- TicTacToe: `/Users/justin/TicTacToe_Ueben`
- UPN: `/Users/justin/UPN_Rechner_Ueben`
- Taschenrechner: `/Users/justin/Taschenrechner_UE3_Ueben` + `/Users/justin/calcLib`
- XML: `/Users/justin/XML-Reader` + `/Users/justin/TinyXML2` + `/Users/justin/TinyXML2_Static`
- Formen: `/Users/justin/Downloads/Formen_Lib_Version` (Referenz: `Loesung_zum_Nachschauen`)

Verwandt: Qt Notizen · QT Einführung TicTacToe
