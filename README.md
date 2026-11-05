# POS 5 – Qt/C++ Übungen + Cheat-Sheets

Meine Übungen aus POS (Qt 6, qmake, macOS) und die Cheat-Sheets für die praktische Arbeit.

## Schnellstart in der PA
1. **Fehlermeldung?** → [Fehlerliste](cheatsheets/08%20Fehlerliste.md) (Cmd+F mit dem Wortlaut)
2. **Wie ging nochmal …?** → [Übersicht](cheatsheets/00%20Qt%20Cheat-Sheets%20%C3%9Cbersicht.md) → passende Aufgabe
3. **Konzept unklar** (Pointer, Referenz, Vererbung …) → [Konzepte](cheatsheets/01%20Konzepte%20C%2B%2B%20einfach%20erkl%C3%A4rt.md)
4. **Grundgerüst, Slots, Layouts, Libraries** → [Qt Grundlagen](cheatsheets/02%20Qt%20Grundlagen%20und%20Workflow.md)

## Aufgaben
- **01 TicTacToe** – Grid-Layout, Auto-Connect, 2D-Array, Gewinnprüfung, PC-Gegner
  [Cheat-Sheet](cheatsheets/03%20TicTacToe.md) · Code: `01_TicTacToe/TicTacToe_Ueben`
- **02 UPN-Rechner** – QStack, split, toDouble(&ok)
  [Cheat-Sheet](cheatsheets/04%20UPN-Rechner.md) · Code: `02_UPN-Rechner/UPN_Rechner_Ueben`
- **03 Taschenrechner** – exprtk in eigener statischer Library
  [Cheat-Sheet](cheatsheets/05%20Taschenrechner%20mit%20Library.md) · Code: `03_Taschenrechner/` (App + `calcLib`)
- **04 XML-Reader** – QFileDialog, QTreeWidget, Rekursion, TinyXML2 dynamisch + statisch
  [Cheat-Sheet](cheatsheets/06%20XML-Reader%20mit%20TinyXML2.md) · Code: `04_XML-Reader/` (`XML-Reader` + `TinyXML2` + `TinyXML2_Static`, zweiter Durchgang: `XML_Reader_Ueben2` + `TinyXML2_StatLib_Ueben2`)
- **05 Formen** – abstrakte Klasse, Vererbung, Factory, QPainter, UML, Libraries statt Plugin
  [Cheat-Sheet](cheatsheets/07%20Formen%20Factory%20und%20Vererbung.md) · Code: `05_Formen/Formen_Lib_Version` (Referenz mit allen draws: `Loesung_zum_Nachschauen`)

Testdateien für den XML-Reader: `testdateien/bibliothek.xml`, `testdateien/schule.xml`

## Projekte öffnen
- In Qt Creator immer die `.pro` öffnen. Bei Formen die **oberste** `Formen_Gesamt.pro`.
- Projekte mit Library (03, 04, 05): **zuerst die Library bauen**, dann die App. Run-Ziel links unten = **App**.
- Die `LIBS`-Pfade zeigen auf `build/Qt_6_11_2_for_macOS_Debug/`. Bei anderem Kit/Build-Ordner Pfad in der `.pro` anpassen, danach **Build → qmake ausführen**.
- Dynamische Lib wird beim Start nicht gefunden → Projekte → Run → Umgebung → `DYLD_LIBRARY_PATH` auf den Ordner der Lib.

## Kommentare im Code
Kommentiert sind nur die Stellen, die schwer oder leicht falsch zu machen sind (Pop-Reihenfolge, Rekursion, verkettete Listen, QString ↔ C-String, Vererbung ohne eigenes draw). Wo mein Code noch Schwächen hat, steht ein Hinweis direkt dabei (z. B. rekursiver PC-Zug bei TicTacToe, fehlender Inhalt beim XML-Reader).
