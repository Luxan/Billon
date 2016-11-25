# Billon
Napisać aplikacje w języku C++, która odczyta z listy argumentów pliki na których wykona następujące czynności:
- odwróci słowa w zdaniu,
- posortuje słowa po odwróceniu w zdaniu w kolejności odwrotnej do leksograficznej (od Z do A),
Pliki zawierają tylko i wyłącznie znaki z zakresu ASCII. Przez zdanie rozumiemy ciąg słów który zamyka się w przedziale od początku linii lub końca poprzedniego zdania do kropki. Słowa składają się ze znaków w przedziale [a-zA-Z] i [0-9]. W zdaniu mogą występować przecinki. Przecinki nie stanowią części słowa i muszą w wynikowym zdaniu zostać za indeksem słowa, za którym go znaleziono.
Przykład: ab baa, cc. -> cc ba, aab.
Wyjaśnienie: ab ma indeks 0, baa ma indeks 1, cc to 2. Przecinek był za słowem o indeksie 1 i tam też pozostaje po zmianach.
Pozostałe znaki takie jak myślniki (-), średniki (;) etc. muszą zostać usunięte z tekstu.

Program powinien przyjąc dowolną ilość argumentów. Przykład:
$ program plik1 plik2 plik3 [...]

Powinien przetworzyć każdy z plików i zapisać wynik pod nazwą pliku dodając rozszerzenie: .wynik.

Pliki mogą być podzielone na mniejsze fragmenty (jako że mogą być bardzo duże). Kolejne części plików mają dodatkowo rozszerzenie .N gdzie N jest 1 < N < 256. Zdania mogą nachodzić na kolejne pliki (tylko kropka oznacza koniec zdania, nie koniec pliku):
Przykład pliku podzielonego na części:
plik1
plik1.2
plik1.3
plik1.4
Wynik działania:
plik1.wynik
plik1.2.wynik
plik1.3.wynik
plik1.4.wynik

Program powinien prawidłowo rozpoznawać, że plik jest podzielony na części. Dodatkowo jeśli jako argument zostanie podany, któraś z kolejnych części pliku, program powinien zacząć od pierwszej części:
Przykład:
$ program plik1.4
Program powinien zacząć od pliku plik1 i przetworzyć kolejne części plików (plik1.2, plik1.3, plik1.4).

Nie należy zakładać poprawności danych wejściowych.
