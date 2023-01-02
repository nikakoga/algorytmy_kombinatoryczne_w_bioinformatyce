1. filtruje wierzcholki majace mniej niz 4 sasiadow
2. dla kazdego wierzcholka biorę sąsiadów
3. tworzę kombinacje bez powtórzeń długości 4 z sąsiadów
4. dla każdej kombinacji tworzę słownik zawierający jako klucze wierzcholek i jego sąsiadów zainicjalizowane na dlugosc 1<br/>
n.p 1->2 3 4 5 ==> {1:1,2:1,3:1,4:1,5:1}
5. dla kazdego elementu kombinacji biorę sąsiadów
6. dla kazdego z tych sąsiadów jezeli istnieje jako klucz w w.w. słowniku to inkrementuje liczbe mu odpowiadajaca
7. jezeli kazdy element slownika ma wartosc 5 zwracam go jako posortowaną krotkę (aby obslugiwal to hashset), w przeciwnym wypadku null
8. jezeli wartosc != null - dodaje do setu