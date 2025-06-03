> _"Jako użytkownik chcę mieć możliwość ręcznego zatrzymywania i wznawiania odliczania czasu dla każdego zadania, aby dostosować go do zmieniających się warunków pracy."_

---

### **1. Zatrzymanie i wznowienie pojedynczego zadania (happy path)**

**Stan początkowy aplikacji:**  
Na liście znajduje się jedno zadanie z przypisanym czasem (np. 1 min).

**Kroki testowe:**
1. Uruchomienie timera.
2. Odczekanie kilku sekund.
3. Naciśnięcie przycisku **Pauza**.
4. Naciśnięcie przycisku **Start**.
5. Odczekanie do zakończenia odliczania czasu.

**Oczekiwany rezultat testu:**  
Po naciśnięciu pauzy timer zatrzymuje odliczanie, które po naciśnięciu start zostaje wznowione. Zadanie poprawnie odlicza się do końca.

**Rzeczywisty rezultat testu:**  
*taki jak oczekiwany*

**Rezultat testu (zaliczony / niezaliczony):**  
*zaliczony*

**Stan końcowy aplikacji:**  
Zadanie zostało zakończone i oznaczone na szaro. Etykieta wskazuje na zakończenie wszystkich zadań, timer jest wyzerowany.

---

### **2. Próba pauzy przed uruchomieniem timera (scenariusz alternatywny)**

**Stan początkowy aplikacji:**  
Jedno zadanie na liście.

**Kroki testowe:**
1. Kliknięcie przycisku **Pauza** przed uruchomieniem timera.

**Oczekiwany rezultat testu:**  
Aplikacja ignoruje komendę pauzy.

**Rzeczywisty rezultat testu:**  
*nic sie nie stalo*

**Rezultat testu (zaliczony / niezaliczony):**  
*zaliczony*

**Stan końcowy aplikacji:**  
Timer nadal nieuruchomiony, brak zmian na liście.
