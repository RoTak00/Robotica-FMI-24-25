# 1.1 Descriere

În această temă trebuie să simulați o stație de încărcare pentru un vehicul electric, folosind mai multe LED-uri și butoane. În cadrul acestui task trebuie să țineți cont de stările butonului și să folosiți debouncing, dar și să coordonați toate componentele ca într-un scenariu din viața reală.

# 1.2 Cerințe

Led-ul RGB reprezintă disponibilitatea stației. Dacă stația este liberă led-ul va fi verde, iar dacă stația este ocupată se va face roșu.

Led-urile simple reprezintă gradul de încărcare al bateriei, pe care îl vom simula printr-un loader progresiv (L1 = 25%, L2 = 50%, L3 = 75%, L4 = 100%). Loader-ul se încărca prin aprinderea succesivă a led-urilor, la un interval fix de 3s. LED-ul care semnifică procentul curent de încărcare va avea starea de clipire, LED-urile din urma lui fiind aprinse continuu, iar celelalte stinse.

Apăsarea scurtă a butonului de start va porni încărcarea. Apăsarea acestui buton în timpul încărcării nu va face nimic.

Apăsarea lungă a butonului de stop va opri încărcarea forțat și va reseta stația la starea liberă. Apăsarea acestui buton cat timp stația este liberă nu va face nimic.\

# 1.3. Structura Software

Sunt definite 3 stări posibile pentru program, care se modifică fie prin input de la butoane, fie prin trecerea unor anumite intervale de timp.

Stări posibile:

- FREE: programul așteaptă apăsarea butonului de START pentru a trece în starea CHARGING
- CHARGING: butonul START este ignorat. Se calculează la fiecare iterație timpul trecut dintre începutul CHARGING și timpul curent. Pe baza timpului trecut și intervale de timp definite (CHARGE_TIME_PER_LED, BLINK_PER_LED), se actualizează LED-ul care face blink și LED-urile care sunt pornite permanent. La finalizarea procesului pentru ultimul LED, se trece în starea ENDING. De asemenea, pe parcursul stării CHARGING, se face polling pentru starea butonului STOP. Dacă acesta a fost apăsat pentru o durată mai mare de 1 secundă (verificare prin debouncing), se trece direct în starea ENDING.
- ENDING: Prin același procedeu ca în starea CHARGING, toate becurile fac blink, iar apoi se trece înapoi în starea FREE.

### 1.3.1. Situații neașteptate

LED-ul RGB folosit diferă față de cel din simulator. Astfel, acesta are pinii de Green și Blue inversați (R - Common - B - G). De aceea, a fost necesară actualizarea #define-urilor (modificat RGB_GREEN în 4 și RGB_BLUE în 5)

# 1.4 Componente Utilizate

- x4 LED-uri albastre
- x1 LED RGB (Catod comun)
- x2 Butoane
- x7 Rezistoare 330 Ohm
- x2 Rezistoare 1 kOhm
- x1 Breadboard
- Linii legătură

# 1.5 Imagini Montaj

## 1.5.1. Montaj

<a href = "https://images.rotak.ro/github/robotica_1/Montaj.jpeg" target = "_blank"><img src = "https://images.rotak.ro/github/robotica_1/Montaj.jpeg" width = "300"></a>

## 1.5.2. Detaliu Pini

<a href = "https://images.rotak.ro/github/robotica_1/Detaliu_Pini.jpeg" target = "_blank"><img src = "https://images.rotak.ro/github/robotica_1/Detaliu_Pini.jpeg" width = "300"></a>

## 1.5.3. Detaliu LED-uri

<a href = "https://images.rotak.ro/github/robotica_1/Detaliu_LED-uri.jpeg" target = "_blank"><img src = "https://images.rotak.ro/github/robotica_1/Detaliu_LED-uri.jpeg" width = "300"></a>

## 1.5.4. Detaliu Butoane

<a href = "https://images.rotak.ro/github/robotica_1/Detaliu_Butoane.jpeg" target = "_blank"><img src = "https://images.rotak.ro/github/robotica_1/Detaliu_Butoane.jpeg" width = "300"></a>

# 1.6 Videoclip Montaj

Un videoclip YouTube Shorts care demonstrează funcționalitatea montajului poate fi vizionat la [următorul link](https://www.youtube.com/shorts/RiaUQndiVEw)

# 1.7 Schema Electrica

<a href = "https://images.rotak.ro/github/robotica_1/Model.png" target = "_blank"><img src = "https://images.rotak.ro/github/robotica_1/Model.png" width = "300"></a>

Takacs Robert
