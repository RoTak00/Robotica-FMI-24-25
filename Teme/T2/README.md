# 1.1 Descriere

În această temă veți crea un joc asemanator cu [TypeRacer](https://play.typeracer.com/).

# 1.2 Cerințe

### LED RGB - Indicator de stare:

- În starea de repaus, LED-ul va avea culoarea albă.
- La apăsarea butonului de start, LED-ul va clipi timp de 3 secunde, indicând o numărătoare inversă până la începerea rundei.
- În timpul unei runde: LED-ul va fi verde dacă textul introdus este corect și va deveni roșu în caz de greșeală.

### Butonul Start/Stop:

- Modul de repaus: Dacă jocul este oprit, apăsarea butonului inițiază o nouă rundă după o numărătoare inversă de 3 secunde.
- În timpul unei runde: Dacă runda este activă, apăsarea butonului o va opri imediat.

### Butonul de dificultate:

- Butonul de dificultate controlează viteza cu care apar cuvintele și poate fi folosit doar în starea de repaus.
- La fiecare apăsare, dificultatea se schimbă ciclind între: (Easy, Medium, Hard).
- La schimbarea dificultății, se trimite un mesaj prin serial: “Easy/Medium/Hard mode on!”.

# 1.3. Structura Software

Sunt definite 3 stări posibile pentru program, care se modifică fie prin input de la butoane, fie prin trecerea unor anumite intervale de timp.

Stări posibile:

- IDLE: programul așteaptă apăsarea butonului de START pentru a trece în starea STARTING. Pe durata IDLE, butonul de change difficulty poate fi apasat pentru a trece dintr-o dificultate in alta
- STARTING: butonul de dificultate este ignorat. Se calculează la fiecare iterație timpul trecut dintre începutul STARTING și timpul curent. Pe baza timpului trecut și intervale de timp definite, se actualizează LED-ul care face blink. Dupa 3 secunde, se trece in starea RUNNING. In tot acest timp, poate fi apasat din nou butonul de START pentru a sari inapoi in IDLE
- RUNNING: Apare un cuvant in Serial, si prin SerialEvent() se citeste input de la tastatura intr-un input buffer. La fiecare ciclu de ceas se proceseaza un caracter din buffer si se adauga la "guessedWord". Cat timp guessedWord este prefix al cuvantului din terminal, LED-ul ramane verde. Daca nu mai este prefix, se transforma in rosu (utilizatorul poate introduce backspace pentru a corecta). Odata ce cuvantul este identic cu chosenWord, se adauga 1 la un contor de cuvinte tastate corect. Totodata, daca se tasteaza corect cuvantul sau trece timpul alocat pe cuvant, se reseteaza buffer-ul, guessedWord, led-ul, si apare un nou cuvant in consola. Dupa 30 de secunde, se afiseaza nr. de cuvinte tastate corect si se trece inapoi in IDLE.

# 1.4 Componente Utilizate

- x1 LED RGB (Catod comun)
- x2 Butoane
- x3 Rezistoare 330 Ohm
- x2 Rezistoare 1 kOhm
- x1 Breadboard
- Linii legătură

# 1.5 Imagini Montaj

## 1.5.1. Montaj

<a href = "https://images.rotak.ro/github/robotica_2/real_1.jpeg" target = "_blank"><img src = "https://images.rotak.ro/github/robotica_2/real_1.jpeg" width = "300"></a>

## 1.5.2. Montaj

<a href = "https://images.rotak.ro/github/robotica_2/real_2.jpeg" target = "_blank"><img src = "https://images.rotak.ro/github/robotica_2/real_2.jpeg" width = "300"></a>

# 1.6 Videoclip Montaj

(TODO)

# 1.7 Schema Electrica

<a href = "https://images.rotak.ro/github/robotica_2/digital.png" target = "_blank"><img src = "https://images.rotak.ro/github/robotica_2/digital.png" width = "300"></a>

Takacs Robert
