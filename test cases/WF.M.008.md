> _"Jako użytkownik chcę mieć dostęp do statystyk pokazujących czas spędzony na każdym zadaniu, sumaryczny czas pracy oraz liczbę zakończonych zadań dla każdego dnia, przedstawionych w postaci tabeli, aby łatwo śledzić moje postępy."_

---

### **1. Wyświetlanie statystyk dla wybranego dnia z zadaniami (happy path)**

**Stan początkowy aplikacji:**  
Aplikacja posiada zapisane dane pracy dla aktualnego dnia.

**Kroki testowe:**
1. (Jeśli danego dnia nie zostały jeszcze wykonane żadne zadania: przejście do zakładki ImPomo, dodanie zadania z czasem 1 minuta, odczekanie do jego zakończenia i oznaczenia jako zakończone – na szaro.)
2. Otwarcie modułu **Statystyki**.
3. Wybranie aktualnej daty w kalendarzu.
4. Sprawdzenie wyświetlonej tabeli statystyk.

**Oczekiwany rezultat testu:**  
Wyświetlana tabela zawiera:
- sumaryczny czas pracy (osobno dla ImPomo i klasycznego Pomodoro),
- liczbę zakończonych zadań tego dnia

**Rzeczywisty rezultat testu:**  
*wyswietlana tabela zawiera statystyki z danego dnia*

**Rezultat testu (zaliczony / niezaliczony):**  
*zaliczony*

**Stan końcowy aplikacji:**  
Moduł Statystyki wyświetla poprawne dane dla wybranego dnia.

---

### **2. Brak danych do wyświetlenia (scenariusz alternatywny)**

**Stan początkowy aplikacji:**  
Moduł Statystyki otwarty.

**Kroki testowe:**
1. Wybranie daty z przyszłości w kalendarzu.
2. Obserwacja tabeli statystyk.

**Oczekiwany rezultat testu:**  
Wyświetlana tabela zawiera zerowe wartości:
- czas pracy dla obu trybów: 0,
- liczba zakończonych zadań: 0.  

**Rzeczywisty rezultat testu:**  
*wyswietlana tabela ma wsystkie wartosci ustawione na 0*

**Rezultat testu (zaliczony / niezaliczony):**  
*zaliczony*

**Stan końcowy aplikacji:**  
Moduł Statystyki obsługuje poprawnie wybór przyszłej daty, prezentując "puste" dane.
