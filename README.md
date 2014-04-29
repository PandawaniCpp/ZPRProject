[ZPR] #TITLE

Autorzy:
- Domański Kacper
- Kaczyński Paweł
- Siadkowski Andrzej

##################
INSTALACJA [LINUX]
##################

Jeżeli aplikacja będzie uruchamiana na Ubuntu/Debian (dostępny będzie apt-get), wystarczy po rozpakowaniu uruchomić skrypt 'install.sh'. W przeciwnym razie konieczne będzie zainstalowanie z dostępnych repozytoriów bibliotek:
 -   libsfml-dev
 -   libbox2d-dev
oraz uruchomienie Makefile'a poleceniem make. Binarny projekt wykonywalny nazywa się "Project.o". W celu wyczyszczenia plików pośrednich kompilacji, należy wykonać polecenie 'make clean'. Aby usunąć projekt wykonywalny, należy wykonać 'make del'.

Uwaga techniczna: dzisiejsze sprawdzenie poprawności na świeżo zainstalowanym Ubuntu wykazało, że do poprawnego uruchomienia programu wymagany jest OpenGL w wersji przynajmniej 3.0 (najnowszy stabilny to 4.4).

###########
O PROJEKCIE
###########

Sam projekt (póki co) prezentuje nastepujące elementy: poruszanie się gracza i animacja, proceduralne generowanie terenu (nałożenie tekstur, animacja wody, gradientowe przechodznie między rodzajami terenu) oraz rozmieszczanie obiektów w świecie (póki co, jako kwadraty). 

Wersja Windowsowa oczywiście też działa, ale instalacja projektu i bibliotek na systemie Linux jest o niebo prostsza.

Po uruchomieniu się projektu, należy 'obudzić' gracza naciskając enter. Poruszanie się: WSAD, myszka obsługuje kąt i odległość widzenia.

Dodatkowo przyciskiem F1 uruchamiana jest konsola z danymi o graczu oraz dostępnych trybach wyświetlania (rozdzielczościach).
CTRL + F  włącza i wyłącza tryb pełnoekranowy
CTRL + "-"  oraz  CTRL + "+"  odpowiednio zmniejsza i zwiększa aktualną rozdzielczość i zaznacza to kolorem żółtym w konsoli.
ESCAPE - wyjście.