> _"Jako użytkownik chcę, aby w obu trybach Pomodoro aplikacja wyświetlała czas pozostały do zakończenia zadania, aby łatwo śledzić postęp."_

---

### **1. Wyświetlanie czasu pozostałego do zakończenia zadania (happy path)** 

**Stan początkowy aplikacji:**  
Uruchomiony tryb ImPomo, jest co najmniej jedno zadanie do odliczania.

**Kroki testowe:**  
1. Uruchomienie timera.  
2. Obserwacja, czy na ekranie widoczny jest licznik pokazujący czas pozostały do zakończenia bieżącego zadania.  
3. Po zakończeniu zadania timer zatrzymuje się lub przechodzi do kolejnego zadania, w zależności od sytuacji na liście.

**Oczekiwany rezultat testu:**  
Czas pozostały jest widoczny i aktualizowany co sekundę.  
Wyświetlana wartość jest zgodna z ustawionym czasem zadania.  
Timer poprawnie odlicza do zera.

**Rzeczywisty rezultat testu:**  
[...]

**Rezultat testu (zaliczony / niezaliczony):**  
[...]

**Stan końcowy aplikacji:**  
Timer odlicza czas zgodnie z aktualną sytuacją, wyświetlacz czasu pozostaje widoczny.

---

### **2. Włączenie obu trybów jednocześnie (ImPomo + klasyczne Pomodoro) (scenariusz alternatywny)**

**Stan początkowy aplikacji:**  
Oba tryby nieuruchomione, ImPomo zawiera kilka zadań do odliczenia.

**Kroki testowe:**  
1. Uruchomienie timera ImPomo, a następnie uruchomienie od razu timera Pomodoro.  
2. Przechodzenie między zakładkami w celu sprawdzenia poprawności odmierzania czasu.

**Oczekiwany rezultat testu:**  
Aplikacja poprawnie pokazuje czas pozostały dla obu trybów, brak pomyłek w licznikach lub nadpisania widoku.

**Rzeczywisty rezultat testu:**  
[...]

**Rezultat testu (zaliczony / niezaliczony):**  
[...]

**Stan końcowy aplikacji:**  
Aplikacja poprawnie pokazuje niezależne timery.
