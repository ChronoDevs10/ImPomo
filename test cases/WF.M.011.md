> _"Jako użytkownik chcę mieć opcję wyciszenia powiadomień w czasie pracy, aby nie być rozpraszanym podczas pracy."_

---

### **1. Wyciszenie powiadomień podczas pracy (happy path)**

**Stan początkowy aplikacji:**  
Powiadomienia dźwiękowe są włączone, na liście w trybie ImPomo są dodane zadania (z czasem np. 1 minuta) umożliwiające rozpoczęcie sesji.

**Kroki testowe:**  
1. Uruchomienie timera, odliczanie pierwszego zadanie.  
2. Po zakończeniu czasu pracy słychać powiadomienie, rozpoczyna się odliczanie kolejnego zadania.  
3. Wyłączenie powiadomień dźwiękowych przed zakończeniem odliczania.

**Oczekiwany rezultat testu:**  
Powiadomienia dźwiękowe są wyciszone, nie sygnalizują zakończenia zadania.  

**Rzeczywisty rezultat testu:**  
*test nieprzeprowadzony ze wzgledu na niezaliczenie testu 9.1*

**Rezultat testu (zaliczony / niezaliczony):**  
[...]

**Stan końcowy aplikacji:**  
Ustawienie wyciszenia powiadomień podczas pracy pozostaje aktywne do czasu ponownej jego zmiany.
