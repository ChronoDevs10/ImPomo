> _"Jako użytkownik chcę móc uruchomić klasyczny licznik Pomodoro z domyślnym czasem 25 minut pracy i 5 minut przerwy, aby pracować w skupieniu bez konieczności planowania zadań."_

---

### **1. Uruchomienie klasycznego Pomodoro z domyślnymi ustawieniami (happy path)**

**Stan początkowy aplikacji:**  
Tryb Pomodoro, ustawienia domyślne:
- Czas pracy: 25 minut  
- Krótka przerwa: 5 minut  
- Długa przerwa: 15 minut  

**Kroki testowe:**
1. Upewnienie się, że zegar ustawiony jest na 25 minut oraz że ustawienia są zgodne z domyślnymi.
2. Zmiana czasu pracy na 1 minutę.
3. Kliknięcie przycisku **Start** w trybie Pomodoro.
4. Oczekiwanie na zakończenie odliczania.
5. Sprawdzenie, czy aplikacja automatycznie przechodzi do 5-minutowej przerwy.

**Oczekiwany rezultat testu:**  
Aplikacja domyślnie ustawia 25 minut pracy. Po zakończeniu bloku pracy automatycznie uruchamia 5-minutową przerwę bez konieczności ingerencji użytkownika.

**Rzeczywisty rezultat testu:**  
[...]

**Rezultat testu (zaliczony / niezaliczony):**  
[...]

**Stan końcowy aplikacji:**  
Tryb: krótka przerwa, licznik ustawiony na 5:00 i aktywny.

---

### **2. Zmiana czasu trwającego bloku w trakcie jego działania (scenariusz alternatywny)**

**Stan początkowy aplikacji:**  
Tryb klasyczny Pomodoro. Użytkownik rozpoczął blok pracy – licznik odlicza (np. 17:00 z 25:00).

**Kroki testowe:**
1. Przejście do ustawień trybu Pomodoro w trakcie trwania bloku pracy.
2. Zmiana czasu pracy z 25 minut na 30 minut.
3. Zatwierdzenie zmian.
4. Obserwacja aktualizacji pozostałego czasu (powinien wynosić teraz 22:00 z 30:00).

**Oczekiwany rezultat testu:**  
Aplikacja umożliwia zmianę czasu trwającego bloku. Pozostały czas zostaje przeliczony zgodnie z nowym limitem (np. 17:00 z 25:00 → 22:00 z 30:00). Timer kontynuuje odliczanie płynnie z nowym ustawieniem.

**Rzeczywisty rezultat testu:**  
[do uzupełnienia]

**Rezultat testu (zaliczony / niezaliczony):**  
[do uzupełnienia]

**Stan końcowy aplikacji:**  
Timer działa poprawnie z nowym czasem trwania bloku.
