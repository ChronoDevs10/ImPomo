> _"Jako użytkownik chcę mieć możliwość zmiany kolejności zadań na liście w trakcie pracy, aby móc dostosować mój plan do nowych priorytetów."_

---

### **1. Zmiana kolejności niewykonanych i nieodliczanych zadań podczas pracy (happy path)**

**Stan początkowy aplikacji:**  
Tryb ImPomo jest nieuruchomiony, zadania na liście kolejno A, B, C, D, każde z czasem np. 1 min.

**Kroki testowe:**  
1. Uruchomienie timera.  
2. Przed zakończeniem odliczania przesunięcie zadania D na drugą pozycję na liście.  
3. Następnie przesunięcie zadania B na koniec listy.

**Oczekiwany rezultat testu:**  
Lista zadań została zaktualizowana zgodnie z przesunięciami.  
Timer odlicza nadal zadanie A bez przerwania.

**Rzeczywisty rezultat testu:**  
[...]

**Rezultat testu (zaliczony / niezaliczony):**  
[...]

**Stan końcowy aplikacji:**  
Timer odlicza zadanie A.  
Lista zadań ma nową kolejność: A, D, C, B.

---

### **2. Próba zmiany kolejności zadania zakończonego lub aktualnie odliczanego (scenariusz alternatywny)**

**Stan początkowy aplikacji:**  
Tryb ImPomo jest nieuruchomiony, zadania na liście kolejno A, B, C każde z czasem np. 1 min.

**Kroki testowe:**  
1. Uruchomienie timera.
2. Odczekanie do zakończenia odliczania zadania A i rozpoczęcia zadania B.  
3. Próba przesunięcia zadania A na niższą pozycję na liście.  
4. Próba przesunięcia zadania B na wyższą/niższą pozycję na liście.  
5. Próba przesunięcia zadania C na samą górę listy.

**Oczekiwany rezultat testu:**  
Zmiana kolejności zadania aktualnie odliczanego i zakończonego jest zablokowana.  
Timer odlicza dalej zadanie B bez zakłóceń.

**Rzeczywisty rezultat testu:**  
[...]

**Rezultat testu (zaliczony / niezaliczony):**  
[...]

**Stan końcowy aplikacji:**  
Timer odlicza zadanie B.  
Lista zadań ma kolejność A, B, C
