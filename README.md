## Platforma czujników – WDS # {#mainpage}

# Opis projektu

Celem projektu jest stworzenie aplikacji ostrzegającej o przeszkodach w otoczeniu robota mobilnego w oparciu o biblioteki Qt języka C++, czujniki ultradźwiękowe HC-SR04 oraz mikrokontroler Arduino Nano. Wizualizacja ma przypominać wizualizację danych z czujników samochodu, wyświetlaną na wewnętrznym, wbudowanym ekranie.

<div style="text-align:center"><img src="przyklad_toyota.jpg" width="30%" alt="przyklad_zastosowania_czujnikow_w_praktyce"><br>
Przykład zastosowania czujników w praktyce
</div>



Projekt jest realizowany oczywiście w mniejszej skali, a więc na platformie czujników.  

# Projekt interfejsu

Parkując samochód kierowca trzyma obie ręce na kierownicy i rozgląda się przez okna samochodu badając otoczenie. Informacje wyświetlane na ekranie mają służyć pomocą, muszą więc być automatyczne. 
           
Interfejs składa się z trzech okien, nazywanych widokami. Jest w pełni automatyczny, co oznacza, że odpowiednie widoki są włączane w zależności od czujników, które wykryją przeszkodę. Czujniki są podzielone na przednie i tylne.

<div style="text-align:center"><img src="przyklad4.png" width="15%" alt="widok_czujnikow_przednich"> <img src="przyklad5.png" width="15%" alt="widok_czujnikow_tylnych"> <img src="przyklad6.png" width="15%" alt="widok_calosciowy"><br>
Przykłady możliwych widoków
</div>

Istnieje jeszcze okno konfiguracji połączenia transmisji UART, włączane automatycznie i jednorazowo przy starcie aplikacji.

# Protokół komunikacyjny OSOS

**OSOS** -- One Sensor One Status.

Platforma czujników komunikuje się z aplikacją za pomocą UART. Gdy dane pochodzące z czujnika wskazują na zmianę statusu, mikrokontroler wysyła odpowiedni komunikat. Dane wysyłane są w postaci ramki.

<div style="text-align:center"><img src="dataframe.png" width="35%" alt="ramka_danych"><br>
Ramka protokołu komunikacji OSOS
</div>

Komunikacja jest znakowa. Ramka rozpoczyna się od znaku X. Następnie, po spacji, znajduje się numer sensora, którego komunikat dotyczy (Sn). Po kolejnej spacji następuje numer statusu (St). Na koniec, również po spacji, znajduje się suma kontrolna CRC8 w zapisie heksadecymalnym, zajmująca dwa znaki w ramce. 

# Schemat ideowy układu czujników

Utworzony schemat jest jedynie wersją wstępną. Zostanie dopracowany w dalszych etapach projektu.

<div style="text-align:center"><img src="schemat.png" width="80%" alt="schemat_ideowy"><br>
Wstępna wersja schematu ideowego
</div>