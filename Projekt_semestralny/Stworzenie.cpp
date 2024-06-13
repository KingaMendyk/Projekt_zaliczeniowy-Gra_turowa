//
// Created by kinga
//

#include "Stworzenie.h"

/**
 * Konstruktor domyslny klasy Stworzenie
 * @param nazwa przyjmowana nazwa
 */
Stworzenie::Stworzenie(std::string &nazwa) {
    Stworzenie::nazwa = nazwa;
    punktyZycia = 0;
    maxPunktyZycia = 0;
    silaPodstawowa = 0;
    sila = silaPodstawowa;
    zrecznosc = 0;
    iloscMocS = 0;
    zuzyteMoc = iloscMocS;
    exp = 0;
    przyjeteExp = 0;
    wymaganeExp = 0;
    mocSpecjalna[0] = "";
    mocSpecjalna[1] = "";
    wGrze = true;
    typ = NONE;
}

/**
 * Konstruktor kopiujacy
 * @param s kopiowane stworzenie
 */
Stworzenie::Stworzenie(const Stworzenie &s) {
    nazwa = s.nazwa;
    punktyZycia = s.punktyZycia;
    maxPunktyZycia = s.maxPunktyZycia;
    silaPodstawowa = s.silaPodstawowa;
    sila = s.sila;
    zrecznosc = s.zrecznosc;
    iloscMocS = s.iloscMocS;
    zuzyteMoc = s.zuzyteMoc;
    exp = s.exp;
    przyjeteExp = s.przyjeteExp;
    wymaganeExp = s.wymaganeExp;
    mocSpecjalna[0] = s.mocSpecjalna[0];
    mocSpecjalna[1] = s.mocSpecjalna[1];
    wGrze = s.wGrze;
    typ = s.typ;
}

/**
 * Funkcja przywraca domyslna sile stworzenia
 */
void Stworzenie::przywrocSile(){
    sila = silaPodstawowa;
}

/**
 * Modyfikator dla ataku stworzenia
 * @param stworzenie atakowane stworzenie
 * @return wartosc double modyfikatora, domyslnie 1
 */
double Stworzenie::modyfikator(Stworzenie &stworzenie){
    return 1;
}

/**
 * Funkcja sprawdza, czy stworzenie przeciwnika uniknelo ataku
 * @param zrecznosc zrecznosc przeciwnika
 * @return czy uniknieto ataku w postaci bool
 */
bool Stworzenie::czyUnik(double zrecznosc){
    std::random_device dev;
    std::mt19937 generator(dev());
    std::uniform_int_distribution<int> dystrybutor(0, 100);

    int szansa = dystrybutor(generator);

    if(szansa <= zrecznosc*100)
        return true;
    return false;
}

/**
 * Funkcja obsluguje uzycie umiejetnosci specjalnej przez stworzenie
 * @param stworzenie stworzenie przeciwnika
 * @param moc numer mocy specjalnej
 */
void Stworzenie::umiejetnoscSpecjalna(Stworzenie &stworzenie, int moc){
    switch(moc){
        case 1:
            zuzyteMoc -= 1;
            std::cout << "Wybrano moc ofensywna " << mocSpecjalna[0]
            << "\nZwiekszono sile ataku o 5"
            <<"\nPozostala liczba uzyc mocy specjalnej: " <<
                zuzyteMoc << std::endl;
            sila += 5 * modyfikator(stworzenie);
            break;
        case 2:
            zuzyteMoc -= 1;
            std::cout << "Wybrano moc defensywna " << mocSpecjalna[1]
            << "\nZmniejszono sile ataku przeciwnika o 5"
            << "\nPozostala liczba uzyc mocy specjalnej: " <<
                zuzyteMoc << std::endl;
            stworzenie.sila -= 5 * modyfikator(stworzenie);
            break;
        default:
            std::cout << "Wystapil niezydentyfikowany blad" << std::endl;
            break;
    }
}

/**
 * Funkcja obsluguje zadawanie ataku stworzeniu przeciwnika
 * @param stworzenie stworzenie przeciwnika
 */
void Stworzenie::atak(Stworzenie &stworzenie){
    if(czyUnik(stworzenie.zrecznosc))
        std::cout << stworzenie.nazwa << " uniknal ataku!\n" << std::endl;
    else{
        double silaAtaku = sila * modyfikator(stworzenie);

        std::cout << "Zadano " << silaAtaku << " punktow obrazen!\n" << std::endl;

        stworzenie.punktyZycia -= silaAtaku;

        if(stworzenie.punktyZycia <= 0)
            stworzenie.wGrze = false;
    }
}

/**
 * Funkcja zwieksza dany atrybut dla danego stworzenia
 * @param atrybut zwiekszany atrybut
 */
void Stworzenie::zwiekszenieAtrybutu(int atrybut){
    using std::cout, std::endl;

    switch(atrybut){
        case 1:
            silaPodstawowa +=  5;
            sila += 5;
            cout << "Zwiekszono sile o 5, obecna sila: " << silaPodstawowa << endl;
            break;
        case 2:
            zrecznosc += 0.1;
            cout << "Zwiekszono zrecznosc o 10%, obecna zrecznosc: " << zrecznosc << endl;
            break;
        case 3:
            maxPunktyZycia += 10;
            cout << "Zwiekszono punkty zycia o 10, obecne punkty zycia: " << maxPunktyZycia << endl;
            break;
        case 4:
            iloscMocS += 1;
            cout << "Zwiekszono ilosc uzyc mocy specjalnej o 1, obecna ilosc: " << iloscMocS << endl;
            break;
        default:
            cout << "Wystapil niezidentyfikowany blad" << endl;
            break;
    }
}

/**
 * Funkcja obsluguje modyfikacje 2 wybranych atrybutow podczas ewolucji
 * @param atrybut1 pierwszy atrybut do ewolucji
 * @param atrybut2 drugi atrybut do ewolucji
 */
void Stworzenie::ewolucja(int atrybut1, int atrybut2) {
    zwiekszenieAtrybutu(atrybut1);
    zwiekszenieAtrybutu(atrybut2);
    przyjeteExp -= wymaganeExp;
}

/**
 * Funkcja przywraca wartosci domyslne dla punktow zycia i ilosci uzyc mocy
 */
void Stworzenie::ulecz(){
    punktyZycia = maxPunktyZycia;
    zuzyteMoc = iloscMocS;
    wGrze = true;
}

/**
 * Funkcja dodaje zdobyte punkty EXP do puli przyjetych punktow
 * @param stworzenie pokonane stworzenie
 */
void Stworzenie::dodajExp(Stworzenie &stworzenie){
    przyjeteExp += stworzenie.exp;
}

/**
 * Przeciazenie operatora do wyswietlania informacji o stworzeniu
 * @param os strumien
 * @param stworzenie stworzenie do wyswietlenia
 * @return ostream
 */
std::ostream &operator<<(std::ostream &os, const Stworzenie &stworzenie) {
    const std::string nazwaTypu[7] = {"NONE","WODA", "ZIEMIA", "OGIEN", "POWIETRZE",
                                "LOD", "STAL"};
    os << (stworzenie.wGrze ? "" : "[STWORZENIE ZEMDLALE]")
        << stworzenie.nazwa
        << "\nTyp: " << nazwaTypu[stworzenie.typ]
        << "\nPunkty zycia: " << stworzenie.punktyZycia
        << "\nSila: " << stworzenie.sila
        << "\nZrecznosc: " << stworzenie.zrecznosc
        << "\nIlosc uzyc mocy specjalnej: " << stworzenie.iloscMocS
        << "\nPunkty EXP: " << stworzenie.exp
        << "\nMoce specjalne: " << stworzenie.mocSpecjalna[0] << " | " << stworzenie.mocSpecjalna[1] << "\n";
    return os;
}

//gettery
int Stworzenie::getPrzyjeteExp() const {
    return przyjeteExp;
}

bool Stworzenie::getWGrze() const {
    return wGrze;
}

Stworzenie::Typ Stworzenie::getTyp() const{
    return typ;
}

int Stworzenie::getWymaganeExp() const {
    return wymaganeExp;
}

const std::string *Stworzenie::getMocSpecjalna() const {
    return mocSpecjalna;
}

int Stworzenie::getZuzyteMoc() const {
    return zuzyteMoc;
}

const std::string &Stworzenie::getNazwa() const {
    return nazwa;
}





