Ruby Ships - gra wieloosobowa
=======

Ruby Ships jest to gra polegająca na walce przeciwko sobie statków sterowanych przez skrypt napisany w języku Ruby.
Każdy z graczy przed rozpoczęciem gry pisze własny kod sterujący statek, po czym po uruchomieniu gry nie ma już
wpływu na to w jaki sposób się zachowuje. Statki mogą poruszać się po planszy, wystrzeliwać pociski oraz wykrywać 
przeciwników za pomocą lunety. Wygrywa ten gracz który zostanie jako ostatni na polu bitwy.


##Zasady gry:

Pole gry jest prostokątem którego krawędzie zatrzymują statki i niszczą kule.
Wszystkie statki posiadają równą pulę wytrzymałości na początku gry. Gdy spadnie ona do zera to statek zostaje zatopiony
i tym samym obiekt ten przestaje istnieć. Wytrzymałość zmniejsza się gdy: 

- kula armatnia zderza się ze statkiem 
- statek wystrzeliwuje kulę

Każdy statek może wystrzeliwać kule o różnej wadze - od tego zależy jak dużo obrażeń zadaje pocisk oraz ile 
wytrzymałości zostaje odjęte przy wystrzale. Standardowo wystrzelenie każdej kuli kosztuje 1/10 jej wagi. Strzelać można 
nie częściej niż co liczbę tur ustaloną w ustawieniach gry.

Można przeszukiwać pole bitwy za pomocą lunety umieszczonej na środku statku - gdy luneta zauważy przeciwnika to wysyła 
powiadomienie o jego wytrzymałości, szybkości, kierunku w którym się porusza oraz o odległości dzielącej wrogi statek 
i lunetę. Podobne powiadomienie pojawia się w przypadku zderzenia dwóch statków, natomiast przy zderzeniu pocisku z 
innym obiektem podawane są bardziej lakoniczne informacje.

Statek porusza się na okresloną odległość z podaną przez gracza maksymalną szybkością we wskazanym kierunku.
Zatrzymuje się w zderzeniu ze ścianą lub innym statkiem. Armata oraz luneta obracają się niezależnie i mogą obracać się
w ustalonej przez użytkownika prędkości nieprzekraczającej wartości maksymalnej zawartej w ustawieniach gry.


##Uruchomienie:

W katalogu src, po skompilowaniu projektu, należy uruchomić program wraz z argumentami będącymi nazwami statków.
Zależnie od ilości nazw zostanie utworzona odpowiednia ilość statków.

Skrypt do obsługi statku powinien znaleźć się w katalogu *ships* głównego folderu projektu. Ustawienia gry można zmienić
w pliku battle_settings.h w katalogu sources.
