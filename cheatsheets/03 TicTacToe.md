# Aufgabe 1 – TicTacToe

Zurück: [00 Qt Cheat-Sheets Übersicht](00%20Qt%20Cheat-Sheets%20%C3%9Cbersicht.md) · Grundlagen: [02 Qt Grundlagen und Workflow](02%20Qt%20Grundlagen%20und%20Workflow.md) · Mein Projekt: `/Users/justin/TicTacToe_Ueben`

**Ziel:** 3×3-Feld aus Buttons, zwei ComboBoxen (Mensch/PC), Start-Button, abwechselnd X und O, Gewinner/Unentschieden per MessageBox, PC macht Zufallszüge.

**Was gelernt wird:** Designer + Grid-Layout, Auto-Connect, 2D-Arrays, Pointer-Array auf Buttons, Zufall, Gewinnprüfung.

---

## Ablauf in 7 Schritten

### 1. Oberfläche
- 9 Buttons: objectNames `btn00` bis `btn22` (Zeile, Spalte)
- Alle 9 markieren → **Objekte tabellarisch anordnen**, sizePolicy `Expanding`, minimumSize 80×80
- `btnStart` (Text „Start“), `cmbSpieler1`, `cmbSpieler2` mit Einträgen „Mensch“, „PC“
- Ganzes Fenster: Layout senkrecht/waagrecht

### 2. Header – Spielzustand
```cpp
#include <QPushButton>

private slots:
    void on_btnStart_clicked();
    void on_btn00_clicked();   // … bis on_btn22_clicked (per Rechtsklick anlegen)

private:
    Ui::MainWindow *ui;
    QPushButton *buttons[3][3];   // 9 Zeiger auf die Buttons
    int feld[3][3];               // 0 = leer, 1 = Spieler 1, 2 = Spieler 2
    int currentPlayer;            // 1 oder 2 – INT, nicht bool!
    bool gameRunning;
    void spielzug(int z, int s);
    int pruefeGewinner();
    bool istPC(int spieler);
    void pcZug();
```

### 3. Konstruktor – Buttons ins Array
```cpp
ui->setupUi(this);
buttons[0][0] = ui->btn00; buttons[0][1] = ui->btn01; buttons[0][2] = ui->btn02;
buttons[1][0] = ui->btn10; buttons[1][1] = ui->btn11; buttons[1][2] = ui->btn12;
buttons[2][0] = ui->btn20; buttons[2][1] = ui->btn21; buttons[2][2] = ui->btn22;
gameRunning = false;
```
- **Warum Konstruktor?** Sonst zeigen die Zeiger ins Leere, wenn jemand vor „Start“ klickt → Absturz.

### 4. Start-Slot – Feld leeren, Startspieler würfeln
```cpp
void MainWindow::on_btnStart_clicked()
{
    for (int z = 0; z < 3; z++)
        for (int s = 0; s < 3; s++) {
            feld[z][s] = 0;
            buttons[z][s]->setText("");
        }
    currentPlayer = QRandomGenerator::global()->bounded(1, 3);   // 1 oder 2
    gameRunning = true;
    if (istPC(currentPlayer)) pcZug();                            // PC beginnt?
}
```

### 5. Spielzug – setzen, prüfen, wechseln
```cpp
void MainWindow::spielzug(int z, int s)
{
    if (!gameRunning || feld[z][s] != 0) return;      // ungültig

    feld[z][s] = currentPlayer;
    buttons[z][s]->setText(currentPlayer == 1 ? "X" : "O");

    int ergebnis = pruefeGewinner();
    if (ergebnis != 0) {
        gameRunning = false;
        if (ergebnis == 3)
            QMessageBox::information(this, "Spielende", "Unentschieden!");
        else
            QMessageBox::information(this, "Spielende", QString("Spieler %1 gewinnt!").arg(ergebnis));
        return;
    }
    currentPlayer = (currentPlayer == 1) ? 2 : 1;     // wechseln
    if (istPC(currentPlayer)) pcZug();                // PC antwortet automatisch
}
```
- `bedingung ? a : b` = Kurz-if: wenn wahr `a`, sonst `b`.

### 6. Gewinnprüfung (0 = weiter, 1/2 = Gewinner, 3 = unentschieden)
```cpp
int MainWindow::pruefeGewinner()
{
    for (int i = 0; i < 3; i++) {
        if (feld[i][0] != 0 && feld[i][0] == feld[i][1] && feld[i][1] == feld[i][2]) return feld[i][0]; // Zeile
        if (feld[0][i] != 0 && feld[0][i] == feld[1][i] && feld[1][i] == feld[2][i]) return feld[0][i]; // Spalte
    }
    if (feld[1][1] != 0) {
        if (feld[0][0] == feld[1][1] && feld[1][1] == feld[2][2]) return feld[1][1];   // Diagonale links oben -> rechts unten
        if (feld[0][2] == feld[1][1] && feld[1][1] == feld[2][0]) return feld[1][1];   // Diagonale rechts oben -> links unten
    }
    for (int z = 0; z < 3; z++)
        for (int s = 0; s < 3; s++)
            if (feld[z][s] == 0) return 0;     // noch was frei → weiter
    return 3;                                  // voll, keiner gewonnen
}
```
- **Reihenfolge wichtig:** erst Gewinner, dann „voll“. Sonst wäre ein Sieg im letzten Zug ein Unentschieden.

### 7. PC-Gegner (zufälliges freies Feld)
```cpp
bool MainWindow::istPC(int spieler)
{
    QComboBox *box = (spieler == 1) ? ui->cmbSpieler1 : ui->cmbSpieler2;
    return box->currentText() == "PC";
}

void MainWindow::pcZug()
{
    QList<QPoint> frei;                                  // alle freien Felder sammeln
    for (int z = 0; z < 3; z++)
        for (int s = 0; s < 3; s++)
            if (feld[z][s] == 0) frei.append(QPoint(z, s));
    if (frei.isEmpty()) return;                          // nichts frei → nichts tun

    QPoint p = frei[QRandomGenerator::global()->bounded(frei.size())];
    spielzug(p.x(), p.y());
}
```
- `#include <QComboBox>` und `#include <QPoint>` falls nötig.

### Die 9 Button-Slots
```cpp
void MainWindow::on_btn00_clicked() { if (!istPC(currentPlayer)) spielzug(0, 0); }
// … gleiches Muster bis on_btn22_clicked mit (2, 2)
```
- `!istPC(...)` → während der PC dran ist, darf der Mensch nicht klicken.

---

## Wichtige Funktionen
- `QRandomGenerator::global()->bounded(a, b)` → Zufall von a bis **b−1**
- `ui->cmbX->currentText()` / `currentIndex()`
- `button->setText("X")`, `button->text()`
- `QMessageBox::information(this, "Titel", "Text")`
- `QString("…%1…").arg(zahl)`

## Fallen (aus meinem Code)
- **`currentPlayer` als `bool`** → wird nie 2 → immer X.
- **Buttons im Start-Slot zuweisen** statt im Konstruktor → Absturz bei Klick vor Start.
- **`gameRunning` nie geprüft / nicht initialisiert.**
- **`"Spieler " + currentPlayer`** → Zeigerarithmetik. `.arg()` benutzen.
- **MessageBox mit nur 2 Parametern** → Titel fehlt.
- **Mein alter PC-Zug war rekursiv** (`robotplays()` ruft sich selbst, bis ein Feld frei ist) → wenn **kein Feld frei** ist, ruft er sich endlos auf → **Absturz**. Lösung oben: freie Felder sammeln.
- **Mein alter Code ließ den PC nach jedem Klick ziehen**, auch wenn der Klick ungültig war (besetztes Feld) oder das Spiel schon vorbei war → PC zieht doppelt. Lösung oben: PC-Zug am Ende von `spielzug`, nur wenn gültig.
- **`if/else` doppelt geschrieben** (einmal für X, einmal für O) → mit `? :` und einem Block zusammenfassen.

## Test-Checkliste
- Mensch/Mensch: X und O wechseln sich ab
- Klick auf besetztes Feld → nichts passiert
- Klick vor Start → nichts passiert
- Zeile, Spalte, beide Diagonalen gewinnen
- Volles Feld ohne Sieger → Unentschieden
- PC/Mensch und Mensch/PC: PC antwortet sofort, zieht nur auf freie Felder
- PC/PC: Spiel läuft nach Start allein durch
