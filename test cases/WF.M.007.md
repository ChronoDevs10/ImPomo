> _"Jako użytkownik chcę, aby aplikacja automatycznie przechodziła od czasu pracy do przerwy i na odwrót, abym nie musiał ręcznie ustawiać timera."_

---

### **1. Automatyczne przejście od pracy do przerwy i z powrotem (happy path)**

**Stan początkowy aplikacji:**  
Sesja klasycznego pomodoro nie została jeszcze rozpoczęta.

**Kroki testowe:**
1. Ustawienie 1 min dla czasu pracy oraz obu przerw.
2. Uruchomienie timera.
3. Oczekiwanie na zakończenie pierwszego bloku pracy.
4. Oczekiwanie na zakończenie pierwszej przerwy.
5. Obserwacja rozpoczęcia drugiego bloku pracy.

**Oczekiwany rezultat testu:**  
Timer automatycznie przełącza się z pracy na przerwę po upływie czasu pracy.  
Po zakończeniu przerwy automatycznie rozpoczyna się kolejny blok pracy.  
Nie jest wymagana interwencja użytkownika.

**Rzeczywisty rezultat testu:**  
[...]

**Rezultat testu (zaliczony / niezaliczony):**  
[...]

**Stan końcowy aplikacji:**  
Timer jest aktywny, odlicza drugi blok pracy.

---

### **2. Przerwanie sesji przez reset Pomodoro (scenariusz alternatywny)**

**Stan początkowy aplikacji:**  
Timer klasycznego Pomodoro aktywny, trwa odliczanie.

**Kroki testowe:**
1. Kliknięcie przycisku „Reset Pomodoro” w trakcie odliczania.
2. Sprawdzenie, czy timer zatrzymuje się i zeruje do wartości początkowej.
3. Ponowne uruchomienie timera.
4. Obserwacja, czy timer odlicza blok pracy od początku.

**Oczekiwany rezultat testu:**  
Po kliknięciu przycisku „Reset” timer natychmiast zatrzymuje się, przechodzi na początek fazy pracy i zeruje się do ustawionej wartości czasu pracy.  
Po ponownym uruchomieniu timer działa normalnie i automatycznie przechodzi między blokami pracy i przerwy.

**Rzeczywisty rezultat testu:**  
[...]

**Rezultat testu (zaliczony / niezaliczony):**  
[...]

**Stan końcowy aplikacji:**  
Timer poprawnie odmierza sesję od początku.
