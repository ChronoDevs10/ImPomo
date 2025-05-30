> _"Jako użytkownik chcę otrzymywać powiadomienia dźwiękowe, aby wiedzieć, kiedy zrobić przerwę lub wznowić pracę."_

---

### **1. Powiadomienia dźwiękowe włączone (happy path)**

**Stan początkowy aplikacji:**  
Powiadomienia dźwiękowe są włączone w ustawieniach, aplikacja jest w trybie Pomodoro ustawionym na 1 minutę czasu pracy i 1 minutę przerwy.

**Kroki testowe:**  
1. Uruchomienie timera Pomodoro.  
2. Oczekiwanie na zakończenie odliczania czasu pracy i przejście do przerwy.  
3. Sprawdzenie, czy odtwarzany jest dźwięk powiadomienia informujący o rozpoczęciu przerwy.  
4. Oczekiwanie na zakończenie przerwy i przejście do kolejnego bloku pracy.  
5. Sprawdzenie, czy odtwarzany jest dźwięk powiadomienia informujący o wznowieniu pracy.

**Oczekiwany rezultat testu:**  
Powiadomienia dźwiękowe odtwarzają się w momentach przejścia między czasem pracy a przerwą i odwrotnie.  
Dopuszczalne lekkie opóźnienie przy pierwszym odtworzeniu dźwięku.

**Rzeczywisty rezultat testu:**  
[...]

**Rezultat testu (zaliczony / niezaliczony):**  
[...]

**Stan końcowy aplikacji:**  
Timer działa dalej, powiadomienia dźwiękowe poprawnie odtwarzają się przy zmianie trybu.

---

### **2. Dźwięk wyłączony systemowo (scenariusz alternatywny)**

**Stan początkowy aplikacji:**  
Powiadomienia dźwiękowe są włączone w ustawieniach, aplikacja jest w trybie Pomodoro ustawionym na 1 minutę czasu pracy i 1 minutę przerwy.

**Kroki testowe:**  
1. Uruchomienie timera Pomodoro.  
2. Oczekiwanie na zakończenie odliczania czasu pracy i przejście do przerwy.  
3. Sprawdzenie, czy odtwarzany jest dźwięk powiadomienia informujący o rozpoczęciu przerwy.  
4. Oczekiwanie na zakończenie przerwy i przejście do kolejnego bloku pracy.  
5. Sprawdzenie, czy odtwarzany jest dźwięk powiadomienia informujący o wznowieniu pracy.

**Oczekiwany rezultat testu:**  
Powiadomienia dźwiękowe nie odtwarzają się.

**Rzeczywisty rezultat testu:**  
[...]

**Rezultat testu (zaliczony / niezaliczony):**  
[...]

**Stan końcowy aplikacji:**  
Sesja trwa dalej, ale bez dźwięku powiadomień.
