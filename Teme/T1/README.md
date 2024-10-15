# 1.1 Descriere

În această temă trebuie să simulați o stație de încărcare pentru un vehicul electric, folosind mai multe LED-uri și butoane. În cadrul acestui task trebuie să țineți cont de stările butonului și să folosiți debouncing, dar și să coordonați toate componentele ca într-un scenariu din viața reală.

# 1.2 Cerințe

Led-ul RGB reprezintă disponibilitatea stației. Dacă stația este liberă led-ul va fi verde, iar dacă stația este ocupată se va face roșu.

Led-urile simple reprezintă gradul de încărcare al bateriei, pe care îl vom simula printr-un loader progresiv (L1 = 25%, L2 = 50%, L3 = 75%, L4 = 100%). Loader-ul se încărca prin aprinderea succesivă a led-urilor, la un interval fix de 3s. LED-ul care semnifică procentul curent de încărcare va avea starea de clipire, LED-urile din urma lui fiind aprinse continuu, iar celelalte stinse.

Apăsarea scurtă a butonului de start va porni încărcarea. Apăsarea acestui buton în timpul încărcării nu va face nimic.

Apăsarea lungă a butonului de stop va opri încărcarea forțat și va reseta stația la starea liberă. Apăsarea acestui buton cat timp stația este liberă nu va face nimic.

# 1.3 Componente Utilizate

- x4 LED-uri albastre
- x1 LED RGB (Catod comun)
- x2 Butoane
- x7 Rezistoare 330 Ohm
- x2 Rezistoare 1 kOhm
- x1 Breadboard
- Linii legătură

# 1.4 Imagini Montaj

## 1.4.1. Montaj

![Montajul EV Charger](https://images.rotak.ro/github/robotica_1/Montaj.jpeg)

## 1.4.2. Detaliu Pini

![Detaliu Pini](https://images.rotak.ro/github/robotica_1/Detaliu_Pini.jpeg)

## 1.4.3. Detaliu LED-uri

![Detaliu LED-uri](https://images.rotak.ro/github/robotica_1/Detaliu_LED-uri.jpeg)

## 1.4.4. Detaliu Butoane

![Detaliu Butoane](https://images.rotak.ro/github/robotica_1/Detaliu_Butoane.jpeg)

# 1.5 Videoclip Montaj

Un videoclip YouTube Shorts care demonstrează funcționalitatea montajului poate fi vizionat la [următorul link](https://www.youtube.com/shorts/RiaUQndiVEw)

# 1.6 Schema Electrica

![Schema electrica a montajului](https://images.rotak.ro/github/robotica_1/Model.png)

Takacs Robert
