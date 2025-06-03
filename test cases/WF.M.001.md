> _"Jako użytkownik chcę móc ustawić dla każdego zadania indywidualny czas, aby lepiej dostosować metodę do mojego stylu pracy."_

---

### **1. Ustawienie czasu dla nowego zadania przed startem timera (happy path)**

**Stan początkowy aplikacji:**  
Tryb ImPomo uruchomiony, brak zadań na liście. Timer nie został jeszcze uruchomiony.

**Kroki testowe:**
1. Dodanie nowego zadania.
2. Ustawienie czasu trwania tego zadania na np. 20 minut.
3. Sprawdzenie, czy czas został zapisany przy zadaniu.
4. Uruchomienie odliczania.

**Oczekiwany rezultat testu:**  
Dodane zadanie adanie jest pierwszym na liście, a timer pokazuje **20:00** i zaczyna odliczać po uruchomieniu.

**Rzeczywisty rezultat testu:**  
*dodane zadanie jest pierwsze na liscie, timer pokazuje 20min i zaczyna odliczac po uruchomieniu*

**Rezultat testu (zaliczony / niezaliczony):**  
*zaliczony*

**Stan końcowy aplikacji:**  
Timer aktywny, odlicza 20 minut. Zadanie widoczne na liście z przypisanym czasem.

---

### **2. Próba zmiany czasu trwającego zadania (scenariusz alternatywny)**

**Stan początkowy aplikacji:**  
Tryb ImPomo, jedno zadanie na liście, ustawione na 50 minut. Timer uruchomiony.

**Kroki testowe:**
1. Próba edycji czasu trwania zadania „Kodowanie” w trakcie jego wykonywania.

**Oczekiwany rezultat testu:**  
Aplikacja nie pozwala na zmianę czasu trwającego zadania.

**Rzeczywisty rezultat testu:**  
*aplikacja nie pozwala na zmianę czasu trwającego zadania*

**Rezultat testu (zaliczony / niezaliczony):**  
*zaliczony*

**Stan końcowy aplikacji:**  
Timer nadal odlicza 50 minut. Zadanie w toku.

---

### **3. Próba ustawienia ujemnego czasu dla zadania (scenariusz alternatywny)**

**Stan początkowy aplikacji:**  
Lista zadań w ImPomo jest pusta.

**Kroki testowe:**
1. Dodanie nowego zadania.
2. Wprowadzenie czasu trwania **-15 minut**.
3. Próba zapisania zadania.

**Oczekiwany rezultat testu:**  
Aplikacja odrzuca wartość ujemną.

**Rzeczywisty rezultat testu:**  
*aplikacja odrzuca wartosc ujemna*

**Rezultat testu (zaliczony / niezaliczony):**  
*zaliczony*

**Stan końcowy aplikacji:**  
Zadanie ma przypisany czas taki, jak przed próbą zmiany.
