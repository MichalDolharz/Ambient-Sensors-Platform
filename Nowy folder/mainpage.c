/*! \mainpage Platforma czujników
 *
 * \section opis_sec Opis projektu
 *
 * Celem projektu jest stworzenie aplikacji ostrzegającej o przeszkodach w otoczeniu robota mobilnego w oparciu o biblioteki Qt języka C++, czujniki ultradźwiękowe HC-SR04 oraz mikrokontroler Arduino Nano. Wizualizacja ma przypominać wizualizację danych z czujników samochodu, wyświetlaną na wewnętrznym, wbudowanym ekranie.
 *
 * \image html przyklad_toyota.jpg "Przykład zastosowania czujników w praktyce" width=35%
 * 
 * Projekt jest realizowany oczywiście w mniejszej skali, a więc na platformie czujników.  
 * 
 * \section interfejs_sec Projekt interfejsu
 *
 * Parkując samochód kierowca trzyma obie ręce na kierownicy i rozgląda się przez okna samochodu badając otoczenie. Informacje wyświetlane na ekranie mają służyć pomocą, muszą więc być automatyczne. 
 *            
 * Interfejs składa się z trzech okien, nazywanych widokami. Jest w pełni automatyczny, co oznacza, że odpowiednie widoki są włączane w zależności od czujników, które wykryją przeszkodę. Czujniki są podzielone na przednie i tylne.
 * 
 * \image html przyklad4.png "Widok przednich czujników" width=15%
 * 
 * \image html przyklad5.png "Widok tylnych czujników" width=15%
 * 
 * \image html przyklad6.png "Widok całościowy" width=15%
 * 
 * Istnieje jeszcze okno konfiguracji połączenia transmisji UART, włączane automatycznie i jednorazowo przy starcie aplikacji.
 *
 * \section osos_sec Protokół komunikacyjny OSOS
 * 
 * \b OSOS -- One Sensor One Status.
 * 
 * Platforma czujników komunikuje się z aplikacją za pomocą UART. Gdy dane pochodzące z czujnika wskazują na zmianę statusu, mikrokontroler wysyła odpowiedni komunikat. Dane wysyłane są w postaci ramki.
 * 
 * \image html dataframe.png "Ramka transmisji protokołu OSOS" width=35%
 * 
 *  Komunikacja jest znakowa. Ramka rozpoczyna się od znaku X. Następnie, po spacji, znajduje się numer sensora, którego komunikat dotyczy (Sn). Po kolejnej spacji następuje numer statusu (St). Na koniec, również po spacji, znajduje się suma kontrolna CRC8 w zapisie heksadecymalnym, zajmująca dwa znaki w ramce. 
 *
 * \section schemat_sec Schemat ideowy układu czujników
 * 
 * Utworzony schemat jest jedynie wersją wstępną. Zostanie dopracowany w dalszych etapach projektu.
 * 
 * \image html schemat.png "Wstępna wersja schematu ideowego" width=80%
 * 
 */