# Aufgabe 2 – UPN-Rechner (Umgekehrte Polnische Notation)

Zurück: [00 Qt Cheat-Sheets Übersicht](00%20Qt%20Cheat-Sheets%20%C3%9Cbersicht.md) · Grundlagen: [02 Qt Grundlagen und Workflow](02%20Qt%20Grundlagen%20und%20Workflow.md) · Mein Projekt: `/Users/justin/UPN_Rechner_Ueben`

**Ziel:** Eingabe wie `3 4 5 * +` (mit Leerzeichen), Button „Berechnen“, Ergebnis im Label. Fehler per MessageBox.

**Was gelernt wird:** `QStack`, `split`, `toDouble(&ok)`, range-for, Fehlerprüfung.

---

## Wie UPN funktioniert (Bild im Kopf)
- Erst die Zahlen, dann der Operator. `3 4 +` = 3 + 4.
- **Stapel (Stack) wie Teller:** Zahl → oben drauf legen (`push`). Operator → **zwei** obere Teller nehmen (`pop`), rechnen, Ergebnis wieder drauf.
- `3 4 5 * +`:
  - 3 → [3] · 4 → [3, 4] · 5 → [3, 4, 5]
  - `*` → 4·5 = 20 → [3, 20]
  - `+` → 3+20 = 23 → [23] → **Ergebnis 23**
- Am Ende muss **genau 1** Wert auf dem Stapel liegen.

---

## Ablauf

### 1. Oberfläche
- `QLineEdit` → `eingabeLe` · `QPushButton` → `pushButton` (Text „Berechnen“) · `QLabel` → `ergebnisLbl`
- Layout senkrecht. Slot: Rechtsklick Button → clicked()

### 2. Includes
```cpp
#include <QStack>
#include <QMessageBox>
```

### 3. Der ganze Slot
```cpp
void MainWindow::on_pushButton_clicked()
{
    QString eingabe = ui->eingabeLe->text();
    QStringList tokens = eingabe.split(' ', Qt::SkipEmptyParts);   // "3 4 +" → ["3","4","+"]
    QStack<double> numStack;

    for (const QString &token : tokens) {
        bool ok = false;
        double zahl = token.toDouble(&ok);          // klappt nur bei Zahlen

        if (ok) {
            numStack.push(zahl);                    // Zahl → drauflegen
        }
        else if (token == "+" || token == "-" || token == "*" || token == "/") {
            if (numStack.size() < 2) {
                QMessageBox::warning(this, "Fehler", "Zu wenige Operanden");
                return;
            }
            double b = numStack.pop();              // ZUERST b (oberster)
            double a = numStack.pop();              // DANN a

            if (token == "+")      numStack.push(a + b);
            else if (token == "-") numStack.push(a - b);
            else if (token == "*") numStack.push(a * b);
            else {
                if (b == 0) {
                    QMessageBox::warning(this, "Fehler", "Division durch 0");
                    return;
                }
                numStack.push(a / b);
            }
        }
        else {
            QMessageBox::warning(this, "Fehler", "Ungültiges Token: " + token);
            return;
        }
    }

    if (numStack.size() != 1) {
        QMessageBox::warning(this, "Fehler", "Ungültiger Ausdruck");
        return;
    }
    ui->ergebnisLbl->setText(QString::number(numStack.pop()));
}
```

---

## Wichtige Bausteine
- `text.split(' ', Qt::SkipEmptyParts)` → Liste, doppelte Leerzeichen werden ignoriert
- `token.toDouble(&ok)` → `ok` wird `true`, wenn es eine Zahl war. `&ok` = Adresse von ok (Funktion schreibt hinein)
- `for (const QString &token : tokens)` → jedes Wort einmal, ohne Kopie
- `QStack<double>`: `push`, `pop` (nimmt UND entfernt), `top` (nur ansehen), `size`, `isEmpty`
- `"-5".toDouble(&ok)` → −5, ok = true · `"-".toDouble(&ok)` → ok = false → landet im Operator-Zweig ✓

## Fallen (aus meinem Code)
- **Pop-Reihenfolge:** `numStack.push(numStack.pop() - numStack.pop());` → rechnet `b − a` (und ist in C++ nicht mal eindeutig). Immer erst `b`, dann `a` in eigene Variablen.
- **Kein Größen-Check** vor `pop` → bei `3 +` Absturz (pop auf leerem Stack).
- **Leere `else`-Zweige** → `abc` wird still ignoriert. Immer Fehlermeldung.
- **`QStack<int>`** → `7 2 /` = 3. Für Kommazahlen `double`.
- **Zeichen einzeln prüfen** (`eingabe[i].isNumber()`) → `12` wären 2 Zeichen. Lieber `split` + `toDouble`.

## Testfälle
- `3 4 5 * +` → 23
- `3 4 -` → −1
- `8 2 /` → 4 · `7 2 /` → 3.5
- `3 +` → „Zu wenige Operanden“
- `3 0 /` → „Division durch 0“
- `abc` → „Ungültiges Token“
- `3 4` → „Ungültiger Ausdruck“
- leer → „Ungültiger Ausdruck“
