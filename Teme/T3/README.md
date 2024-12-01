# 1.1 Descriere

În această temă, fiecare echipă va crea un joc de reflex competitiv pentru doi jucători, în care ambii participanți vor concura pentru a obține cel mai mare punctaj, testându-și viteza de reacție. Proiectul se va realiza în echipe de câte două persoane.

Fiecare jucător va avea butoane și LED-uri proprii, iar jocul se va desfășura în mai multe runde. Scopul fiecărui jucător este să apese cât mai rapid butonul care corespunde culorii afișate pe LED-ul RGB al echipei sale. Punctajul fiecărui jucător va fi afișat pe un ecran LCD și se va actualiza pe parcursul jocului. La finalul jocului, jucătorul cu cel mai mare punctaj este declarat câștigător.

# 1.2 Cerințe

### Inițializare

Jocul pornește cu afișarea unui mesaj de bun venit pe LCD. Apăsarea unui buton declanșează startul jocului.

Pentru începerea jocului, butonul de start poate fi implementat într-un mod flexibil, rămânând la latitudinea studenților să aleagă una dintre următoarele variante:

- în această variantă, jocul pornește la apăsarea oricărui buton.
- Un buton specific începe jocul\* - se poate desemna un buton anume, clar marcat pe breadboard, pentru a porni jocul.
- Un al 7-lea buton dedicat\* – se poate adăuga un buton suplimentar destinat exclusiv pornirii jocului.

### Desfășurarea Rundelor

- Fiecare jucător are trei butoane, fiecare asociat unui LED de o culoare diferită și un al 4-lea LED RGB.
- La fiecare rundă, fiecare jucător este cel activ.
- LED-ul RGB al jucătorului activ se aprinde într-o culoare corespunzătoare unuia dintre butoanele sale. Jucătorul trebuie să apese cât mai rapid butonul care corespunde culorii LED-ului RGB, pentru a obține puncte. Cu cât reacționează mai repede, cu atât primește mai multe puncte.
- La finalul unei runde LCD-ul afișează punctajul actualizat al ambilor jucători.
- Pe tot parcursul jocului display-ul LCD va arata punctajul fiecarui jucator

### Timpul și Finalizarea Jocului

- Servomotorul se rotește pe parcursul jocului, indicând progresul. O rotație completă a servomotorului marchează sfârșitul jocului (voi decideti cat de repede se misca).
- La final, LCD-ul afișează numele câștigătorului și scorul final pentru câteva secunde, apoi revine la ecranul de start cu mesajul de bun venit.

# 1.3. Structura Software

Cele 2 plăci Arduino Uno comunică prin SPI. Plăcuța **Master** controlează flow-ul jocului, determină butonul care trebuie apăsat în fiecare rundă, calculează scorurile, controlează LCD-ul și Servomotorul. Plăcuța **Slave** prezintă butoanele care trebuie apăsate de către fiecare jucător și trimite inputul primit înapoi la Master pentru procesare.

## 1.3.1. Plăcuța Master

Programul este construit sub forma unui FSM simplu, cu trei stări: **Idle, Starting și Playing**

- **Idle**: La apăsarea butonului de start, se resetează scorurile și se trece în starea „Starting”
- **Starting**: Se afișează un countdown de 3 secunde, după care se decide care jucător începe primul și apoi se trece în starea „Playing”.
- **Playing**:

Se determină un buton random de apăsat și se contruiește o variabilă de tip _Byte_ care determină: a cărui jucător îi e rândul și care buton trebuie apăsat. Acest Byte se transmite prin SPI plăcuței Slave, după care se începe un proces de polling la fiecare 10 milisecunde. La fiecare 10 milisecunde, plăcuța Master trimite un byte dummy către Slave (ACK), până când primește înapoi o valoarea care conține SPI_SLAVE_TRANSMIT. Astfel, știe că datele din Byte-ul primit reprezintă butonul apăsat de jucător în viața reală.
Dacă valoarea trimisă de Master este egală cu valoarea primită de la Slave, înseamnă că jucătorul a apăsat butonul corect, și i se adaugă puncte pe baza vitezei de reacție. În acest moment, sau dacă nu s-a primit un mesaj după 5 secunde, se trece la jucătorul următor și se repetă procedeul.
În tot acest timp, se actualizează informațiile de pe ecranul LCD cu scorul curent, iar servo-motorul se rotește pe baza timpului trecut. Odată ce a trecut timpul limită al jocului, se trimite valoarea END către Slave, se afișează câștigătorul și scorurile pe LCD și se trece înapoi la starea „Idle”.

Codul este structurat în diverse fișiere header, pentru modularitate și ușurință de administrare a codului: Game.h, Utils.h, Variables.h

## 1.3.2. Plăcuța Slave

Plăcuța slave acționează doar la primirea datelor din interrupt-ul atașat SPI-ului. Odată ce primește un Byte de la Master, îl procesează pentru a determina care LED trebuie aprins și în ce culoare, dar și de la ce butoane să asculte input. În momentul în care este apăsat un buton (butoane care sunt multiplexate și care sunt distinse pe baza valorii din pinii de input analogic), Slave-ul actualizează variabila de transfer SPI cu valoarea butonului care a fost apăsat, pentru ca Master-ul să poată determina dacă jucătorul a apăsat butonul corect.

Odată ce se primește valoarea END de la Master, se trece în starea NOT_PLAYING în care niciun buton nu are vreun efect.

# 1.4 Componente Utilizate

- x2 LED RGB (Catod comun)
- x6 LED-uri (2 Rosii, 2 Galbene, 2 Albastre)
- x7 Butoane (2 Rosii, 2 Galbene, 2 Albastre) + 1 Buton de start
- x1 Condensator
- x1 Servomotor
- x1 Potentiometru
- x1 Ecran LCD
- x3 Breadboard-uri medii
- x1 Breadboard mic
- x2 Arduino Uno
- Linii legătură
- Rezistoare

# 1.5 Imagini Montaj

Click pentru a deschide imaginile in fullscreen

## 1.5.1 Imaginea 1 - Detaliu Slave

<a href = "https://images.roberttakacs.ro/github/robotica_3/4.jpeg" target = "_blank"><img src = "https://images.roberttakacs.ro/github/robotica_3/4.jpeg" width = "300"></a>

## 1.5.2 Imaginea 2 - Detaliu Controller

<a href = "https://images.roberttakacs.ro/github/robotica_3/5.jpeg" target = "_blank"><img src = "https://images.roberttakacs.ro/github/robotica_3/5.jpeg" width = "300"></a>

## 1.5.3 Imaginea 3 - In timpul jocului I

<a href = "https://images.roberttakacs.ro/github/robotica_3/1.jpeg" target = "_blank"><img src = "https://images.roberttakacs.ro/github/robotica_3/1.jpeg" width = "300"></a>

## 1.5.3 Imaginea 4 - In timpul jocului II

<a href = "https://images.roberttakacs.ro/github/robotica_3/2.jpeg" target = "_blank"><img src = "https://images.roberttakacs.ro/github/robotica_3/2.jpeg" width = "300"></a>

## 1.5.3 Imaginea 5 - Detaliu LCD

<a href = "https://images.roberttakacs.ro/github/robotica_3/3.jpeg" target = "_blank"><img src = "https://images.roberttakacs.ro/github/robotica_3/3.jpeg" width = "300"></a>

# 1.6 Videoclip Montaj

Un videoclip YouTube care demonstrează funcționalitatea montajului poate fi vizionat la [următorul link](https://www.youtube.com/watch?v=fU7H8QOQamY)

# 1.7 Schema Electrica

Click pentru a deschide imaginea in fullscreen

<a href = "https://images.roberttakacs.ro/github/robotica_3/schema_electrica.png" target = "_blank"><img src = "https://images.roberttakacs.ro/github/robotica_3/schema_electrica.png" width = "600"></a>

Alexandru Norina & Takacs Robert
