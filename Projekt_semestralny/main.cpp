/**
@file main.cpp
*/

#include <iostream>
#include <vector>
#include <random>
#include "Stworzenia.h"


/**
 * Funkcja wyswietla linie dlugosci n znakow
 * @param n liczba znakow '-'
 */
void drukujLinie(int n){
    for(int i = 0; i < n; i++)
        std::cout << "-";
}

/**
 * Funkcja wyswietla menu pomocy
 */
void help(){
    drukujLinie(20);
    std::cout << "MENU POMOCY";
    drukujLinie(20);
    std::cout << "\n1.POZIOMY TRUDNOSCI\n"
    << "Latwy - 4 rundy, kazda z 4 przeciwnikami\n"
    << "Sredni - 5 rund, kazda z 5 przeciwnikami\n"
    << "Trudny - 6 rund, kazda z 6 przeciwnikami\n"
    << "2.STWORZENIA\n"
    << "Gra zawiera zestaw 18 stworzen 6 roznych typow, kazdy typ posiada okreslone moce specjalne:\n"
    << "Woda - moce specjalne Armata Wodna i Wodospad\n"
    << "Ziemia - moce specjalne Gniot i Skala\n"
    << "Ogien - moce specjalne Kula Ognia i Plomienny Okrag\n"
    << "Powietrze - moce specjalne Tornado i Podmuch\n"
    << "Lod - moce specjalne Burza Sniezna i Blok Lodu\n"
    << "Stal - moce specjalne Swider i Tarcza\n"
    << "3.AKCJE\n"
    << "W trakcie tury mozna wybrac jedna z akcji:\n"
    << "Atak - dzieli sie na atak zwykly lub specjalny. Atak zwykly zadaje cios przeciwnikowi\n"
       "i odbiera mu odpowiednia ilosc punktow. Uwaga! Przeciwnik moze uniknac takiego ataku!\n"
       "Atak specjalny pozwala wybrac jedna z dwoch mocy specjalnych - odpowidnio ofensywna i defensywna.\n"
       "Ofensywna moc odbiera przeciwnikowi 5 punktow sily do konca rundy\n"
       "Defensywna moc dodaje graczowi 5 punktow sily do kona rundy\n\n"
    << "Wymiana stworzenia - wystawione stworzenie mozna wymienic na inne ze swojej puli.\n"
       "Uwaga! nie mozna wymienic stworzenia na zemdlale\n"
    << "Ewolucja - wymaga odpowiedniej ilosci punktow EXP. Punkty te zdobywa sie za pokonanie przeciwnika.\n"
       "Przy odpowiedniej ilosci punktow mozna zwiekszyc dwa wybrane atrybuty z puli:\n"
       "sila, zrecznosc, punkty zycia, ilosc uzyc mocy specjalnej\n"
    << "4.PRZEBIEG GRY\n"
    << "Wybierz poziom trudnosci.\n"
       "Wybierz druzyne 6 stworzen. Stworzenia beda Ci towarzyszyc do konca gry\n"
       "Podczas swojej kolejki gracz wybiera jedna z akcji\n"
       "Nastepnie nastepuje ruch przeciwnika\n"
       "Gra dzieli sie na rundy, a kazda runda na tury. Tura konczy sie w momencie "
       "pokonania przeciwnkia lub przegranej gracza\n"
    << "5.DODATKOWE INFORMACJE\n"
    << "Gdy stworzenie zemdleje, nalezy je wymienic na ine ze swojej puli\n"
    << "-h lub --help wyswietla te pomoc\n"
    << std::endl;
}

/**
 * Funkcja wyswietla pule stworzen
 * @param pula zadana pula stworzen
 */
void wyswietlPule(const std::vector<Stworzenie*> &pula){
    int num = 1;
    for(Stworzenie* s : pula){
        drukujLinie(50);
        std::cout << "\n" << num << ". " << *s;
        drukujLinie(50);
        std::cout << "\n";
        num++;
    }
}

/**
 * Funkcja obsluguje wybor poziomu przez gracza
 * @param poziomTrudnosci referencja do poziomu trudnosci do zmodyfikowania
 */
void wyborPoziomu(int &poziomTrudnosci){
    bool kontrola = true;

    while(kontrola){
        std::cout << "Wybierz poziom: \n" <<
                  "1.LATWY\t" << "2. SREDNI\t" << "3. TRUDNY\n" << std::endl;
        std::cout << "Podaj numer:";

        int trudnosc;
        std::cin >> trudnosc;

        switch(trudnosc){
            case 1:
                std::cout << "Wybrano poziom LATWY\n";
                poziomTrudnosci = 4;
                kontrola = false;
                break;
            case 2:
                std::cout << "Wybrano poziom SREDNI\n";
                poziomTrudnosci = 5;
                kontrola = false;
                break;
            case 3:
                std::cout << "Wybrano poziom TRUDNY\n";
                poziomTrudnosci = 6;
                kontrola = false;
                break;
            default:
                std::cout << "Niepoprawna liczba, sprobuj ponownie" << std::endl;
                break;
        }
    }
}

/**
 *  Funkcja pozwala uzytkownikowi wybrac druzyne 6 stworzen
 * @param pula predefiniowana pula stworzen
 * @param pulaGracza pula gracza
 */
void wyborDruzyny(const std::vector<Stworzenie*> &pula, std::vector<Stworzenie*> &pulaGracza){
    std::cout << "Wybierz 6 stworzen z puli:\n";
    wyswietlPule(pula);

    int count = 0;

    while(count < 6){
        std::cout << "Podaj numer wybranego stworzenia:";
        int wybrane;
        std::cin >> wybrane;

        if(1 <= wybrane && wybrane <= 18){
            pulaGracza.push_back(new Stworzenie(*pula.at(wybrane-1)));
            count++;
        }
        else{
            std::cout << "Niepoprawny numer, sprobuj ponownie\n";
        }
    }
}

/**
 * Funkcja losuje druzyne przeciwnika, ilosc stworzen zalezy od poziomu trudnosci
 * @param poziomTrudnosci wybrany poziom trudnosci
 * @param pula predefiniowana pula stworzen
 * @param pulaPrzeciwnika pula przeciwnika, do ktorej beda dodawane stworzenia
 */
void losowaniePrzeciwnikow(int poziomTrudnosci, const std::vector<Stworzenie*> &pula, std::vector<Stworzenie*> &pulaPrzeciwnika){
    std::random_device dev;
    std::mt19937 generator(dev());
    std::uniform_int_distribution<int> dystrybutor(0, 17);

    for(int i = 0; i < poziomTrudnosci; i++){
        int wylosowana = dystrybutor(generator);
        pulaPrzeciwnika.push_back(new Stworzenie(*pula.at(wylosowana)));
    }
}

/**
 * Funkcja obsluguje wybor akcji przez gracza
 * @return numer akcji w postaci int
 */
int wyborAkcji(){
    std::cout << "Wybierz co chcesz zrobic\n";
    std::cout << "1.ATAK\t2.WYMIANA STWORZENIA\t3.EWOLUCJA STWORZENIA\n";

    int wybrana;
    do{
        std::cout << "Podaj numer wybranej akcji:";
        std::cin >> wybrana;

        if(wybrana < 1 || wybrana > 3)
            std::cout << "Podano akcje spoza listy, sprobuj ponownie\n";
    } while(wybrana < 1 || wybrana > 3);

    return wybrana;
}

/**
 * Funkcja obluguje wybor umiejetnosci specjalnej przez gracza
 * @param stworzenie aktualne stworzenie
 * @return numer umiejetnosci w postaci int
 */
int wyborUmiejetnosci(const Stworzenie *stworzenie){
    std::cout << "Wybierz umiejetnosc\n";
    std::cout << "1." << stworzenie->getMocSpecjalna()[0] << "\t2." << stworzenie->getMocSpecjalna()[1] << "\n";

    int wybrana;
    do{
        std::cout << "Podaj numer wybranej umiejetnosci:";
        std::cin >> wybrana;

        if(wybrana < 1 || wybrana > 2)
            std::cout << "Podano umiejetnosc spoza listy, sprobuj ponownie\n";
    } while(wybrana < 1 || wybrana > 2);

    return wybrana;
}

/**
 * Funkcja sluzy do zadawania ataku stworzeniu przeciwnika
 * @param stworzenieGracza stworzenie atakujace
 * @param stworzeniePrzeciwnika stworzenie atakowane
 */
void atak(Stworzenie *stworzenieGracza, Stworzenie *stworzeniePrzeciwnika){
    stworzenieGracza->atak(*stworzeniePrzeciwnika);
}

/**
 * Funkcja sluzy do zmiany atrybutu sila, w zaleznosci od wybranej mocy  graczowi lub przeciwnikowi
 * @param stworzenieGracza stworzenie atakujacego
 * @param stworzeniePrzeciwnika stworzenie atakowane
 * @param moc numer wybranej mocy specjalnej
 */
void umiejetnoscSpecjalna(Stworzenie *stworzenieGracza, Stworzenie *stworzeniePrzeciwnika, int moc){
    stworzenieGracza->umiejetnoscSpecjalna(*stworzeniePrzeciwnika, moc);
}

/**
 * Funkcja obsluguje wymiane stworzenia na wskazane
 * @param wybor wskazane stworzenie
 * @param pula pula z ktorej nastapi wymiana
 * @param stworzenie aktualne stworzenie
 */
void wymiana(int wybor, const std::vector<Stworzenie*> &pula, Stworzenie **stworzenie){
    *stworzenie = pula.at(wybor-1);
}

/**
 * Funkcja obsluguje wymiane stworzenia aktualnego na inne stworzenie z puli gracza
 * @param pula pula gracza
 * @param stworzenie aktualne stworzenie
 */
void wyborWymiana(const std::vector<Stworzenie*> &pula, Stworzenie **stworzenie){
    std::cout << "Wybierz stworzenie, na ktore chcesz wymienic:\n";
    wyswietlPule(pula);

    int wybrane;
    bool kontrola = true;

    while(kontrola){
        std::cout << "Podaj numer:";
        std::cin >> wybrane;

        if(wybrane > 6){
            std::cout << "Podano numer spoza listy (1 - 6). Sprobuj ponownie" << std::endl;
        }
        else if(!(pula.at(wybrane-1)->getWGrze()))
            std::cout << "Nie mozna wybrac stworzenia, ktore zemdlalo!\n";
        else if(*stworzenie == pula.at(wybrane-1)){
            std::cout << "To stworzenie juz jest wybrane, sprobuj ponownie\n";
        }
        else{
            wymiana(wybrane, pula, stworzenie);
            kontrola = false;
        }
    }
}

/**
 * Funkcja obsluguje ewolucje zadanego stworzenia
 * @param atrybut1 pierwszy atrybut do ewolucji
 * @param atrybut2 drugi atrybut do ewolucji
 * @param stworzenie ewoluowane stworzenie
 */
void ewolucja(int atrybut1, int atrybut2, Stworzenie *stworzenie){
    stworzenie->ewolucja(atrybut1, atrybut2);
}

/**
 * Funkcja sluzy do wybou atrybutow i ewolucji stworzenia
 * @param stworzenie ewoluowane stworzenie
 * @return powodzenie ewolucji w postaci bool
 */
bool wyborEwolucji(Stworzenie *stworzenie){
    int zebraneExp = stworzenie->getPrzyjeteExp();
    int wymaganeExp = stworzenie->getWymaganeExp();
    int atrybut1, atrybut2;
    bool kontrola = true;

    if(zebraneExp >= wymaganeExp){
        while(kontrola){
            std::cout << "Wybierz 2 atrybuty do ewolucji:\n" << std::endl;
            std::cout << "1.[SILA] 2.[ZRECZNOSC] 3.[PUNKTY ZYCIA] 4.[MOC SPECJALNA]\n" << std::endl;
            std::cout << "Podaj numery:";

            std::cin >> atrybut1;
            std::cin >> atrybut2;

            if(atrybut1 == atrybut2){
                std::cout << "Podaj dwa rozne atrybuty!" << std::endl;
                kontrola = true;
            }

            else if((1 <= atrybut1  && atrybut1 <= 4) && (1 <= atrybut2 && atrybut2 <= 4)){
                ewolucja(atrybut1, atrybut2, stworzenie);
                kontrola = false;
            }

            else{
                std::cout << "Podano atrybut spoza listy (1 - 4)" << std::endl;
                kontrola = true;
            }
        }
        return true;
    }
    else{
        std::cout << "Za malo punktow Exp" << std::endl;
        return false;
    }
}

/**
 * Funkcja zapisuje stan gry i konczy program
 */
void zapiszWyjdz(){
    std::cout << "Zapisywanie..." << std::endl;
}

/**
 * Funkcja obsluguje ruch gracza
 * @param pula pula gracza
 * @param stworzenieGracza aktualne stworzenie gracza
 * @param stworzeniePrzeciwnika aktualne stworzenie przeciwnika
 * @return powodzenie ruchu w postaci bool
 */
bool ruchGracza(std::vector<Stworzenie*> &pula, Stworzenie *&stworzenieGracza, Stworzenie *&stworzeniePrzeciwnika){
    int akcja = wyborAkcji();

    switch(akcja){
        case 1:
            std::cout << "Wybierz atak\n";
            std::cout << "1.Atak zwykly\t2.Umiejetnosc specjalna\n";

            int wybor;

            do{
                std::cout << "Wpisz numer:";
                std::cin >> wybor;

                if(wybor < 1 || wybor > 2)
                    std::cout << "Podano nieprawidlowy numer, sprobuj ponownie\n";
            } while(wybor < 1 || wybor > 2);

            if(wybor == 1)
                atak(stworzenieGracza, stworzeniePrzeciwnika);
            else if(wybor == 2){
                if(stworzenieGracza->getZuzyteMoc() > 0){
                    int moc = wyborUmiejetnosci(stworzenieGracza);
                    umiejetnoscSpecjalna(stworzenieGracza, stworzeniePrzeciwnika, moc);
                }
                else{
                    std::cout << "Brak mozliwosci uzycia mocy specjalnej" << std::endl;
                    return false;
                }
            }
            break;
        case 2:
            wyborWymiana(pula, &stworzenieGracza);
            break;
        case 3:
            bool czyEwolucja;
            czyEwolucja = wyborEwolucji(stworzenieGracza);

            if(!czyEwolucja){
                return false;
            }
            break;
        default:
            std::cout << "Wystapil niezidentyfikowany blad" << std::endl;
            return false;
    }
    return true;
}

/**
 * Funkcja obsluguje ruch przeciwnika
 * @param pula pula przeciwnika
 * @param stworzenieGracza stworzenie przeciwnika
 * @param stworzeniePrzeciwnika stworzenie gracza
 * @return powodzenie ruchu w postaci bool
 */
bool ruchPrzeciwnika(std::vector<Stworzenie*> &pula, Stworzenie *&stworzenieGracza, Stworzenie *&stworzeniePrzeciwnika){
    std::random_device dev;
    std::mt19937 generator(dev());
    std::uniform_int_distribution<int> dystrybutor(1, 3);

    int wylosowanaAkcja = dystrybutor(generator);

    switch(wylosowanaAkcja){
        case 1:
            int wybrany;
            wybrany = (int)random() % 2 + 1;

            if(wybrany == 1){
                std::cout << "Przeciwnik atakuje!\n";
                atak(stworzenieGracza, stworzeniePrzeciwnika);
            }
            else if(wybrany == 2){
                if(stworzenieGracza->getZuzyteMoc() > 0){
                    int moc = (int)random() % 2 + 1;
                    std::cout << "Przeciwnik uzywa mocy specjalnej " << stworzenieGracza->getMocSpecjalna()[moc-1] << "!\n";
                    umiejetnoscSpecjalna(stworzenieGracza, stworzeniePrzeciwnika, moc);
                }
                else
                    return false;
            }
            break;
        case 2:
            int wybrane;
            wybrane = (int)random() % pula.size() + 1;

            while(stworzenieGracza == pula.at(wybrane - 1))
                wybrane = (int)random() % pula.size() + 1;

            wymiana(wybrane, pula, &stworzenieGracza);
            std::cout << "Przeciwnik wymienia stworzenie na " << stworzenieGracza->getNazwa() << "!\n";
            break;
        case 3:
            bool czyEwolucja;
            czyEwolucja = stworzenieGracza->getPrzyjeteExp() >= stworzenieGracza->getWymaganeExp();

            if(!czyEwolucja){
                return false;
            }
            else{
                std::cout << "Przeciwnik ewoluuje stworzenie!\n";
                int atrybut1 = (int) random() % 3 + 1;
                int atrybut2 = (int) random() % 2 + 4;
                ewolucja(atrybut1, atrybut2, stworzenieGracza);
            }
            break;
        default:
            std::cout << "Wystapil niezydentyfikowany blad" << std::endl;
            return false;
    }
    return true;
}

/**
 * Funkcja sprawdza czy gra powinna sie zakonczyc
 * @param poziomTrudnosci aktualny poziom trudnosci
 * @param runda aktualna runda
 * @return zakonczenie gry w postaci bool
 */
bool koniec(const int poziomTrudnosci, const int runda){
    return runda > poziomTrudnosci;
}

/**
 * Funkcja sprawdza czy pula zawiera same zemdlale stworzenia
 * @param pula zadana pula
 * @return stan puli w postaci bool
 */
bool pustaPula(const std::vector<Stworzenie*> &pula){
    int liczba = 0;

    for(Stworzenie *s : pula){
        if(!s->getWGrze())
            liczba++;
    }
    return liczba == pula.size();
}

/**
 * Funkcja losuje stworzenie dla przeciwnika
 * @param pula pula przeciwnika
 * @param stworzenie aktualne stworzenie przeciwnika
 */
void zemdlaleLos(const std::vector<Stworzenie*> &pula, Stworzenie *&stworzenie){
    int index = 0;
    while(index < pula.size() && !pula.at(index)->getWGrze())
        index++;

    if(index < pula.size())
        stworzenie = pula.at(index);
}

/**
 * Funkcja obsluguje wybor stworzenia w przypadku zemdlalego aktualnego stworzenia
 * @param pula pula gracza
 * @param stworzenie aktualne stworzenie
 */
void zemdlaleWybor(const std::vector<Stworzenie*> &pula, Stworzenie *&stworzenie){
    std::cout << "Twoje stworzenie zemdalo!" << std::endl;
    wyborWymiana(pula, &stworzenie);
}

/**
 * Funkcja przywraca maksymalne punkty zycia stworzeniom z puli
 * @param pula pula stworzen
 */
void ulecz(std::vector<Stworzenie*> &pula){
    for(Stworzenie *s : pula)
        s->ulecz();
}

/**
 * Funkcja przywraca domyslna sile stworzeniom z puli
 * @param pula pula stworzen
 */
void przywrocSile(std::vector<Stworzenie*> &pula){
    for(Stworzenie *s : pula)
        s->przywrocSile();
}

/**
 * Funkcja dodaje punkty EXP za pokonanie przeciwnika
 * @param stworzenieGracza stworzenie gracza
 * @param stworzeniePrzeciwnika stworzenie przeciwnika
 */
void dodajExp(Stworzenie *stworzenieGracza, Stworzenie *stworzeniePrzeciwnika){
    stworzenieGracza->dodajExp(*stworzeniePrzeciwnika);
}

/**
 * Funkcja usuwa stworzenia z puli
 * @param pula zadana pula
 */
void usun(std::vector<Stworzenie*> &pula){
    pula.erase(pula.begin(), pula.end());
}

int main() {
    using namespace std;

    bool czyPrzegrana = false;
    bool koniecGry = false;
    int  poziomTrudnosci;
    int runda = 1;
    int tura = 1;
    bool udanyRuch;

    Stworzenie* aktualneStworzenie;
    Stworzenie* stworzeniePrzeciwnkika;

    vector<Stworzenie*> pulaGracza;
    vector<Stworzenie*> pulaPrzeciwnika;

    //Stworzenia wodne
    StworzenieWodne plop = StworzenieWodne("Plop");
    StworzenieWodne splash = StworzenieWodne("Splash");
    StworzenieWodne streamy = StworzenieWodne("Streamy");

    //Stworzenia ogniste
    StworzenieOgniste solar = StworzenieOgniste("Solar");
    StworzenieOgniste flamer = StworzenieOgniste("Flamer");
    StworzenieOgniste flaren = StworzenieOgniste("Flaren");

    //Stworzenia ziemne
    StworzenieZiemne rocky = StworzenieZiemne("Rocky");
    StworzenieZiemne grunt = StworzenieZiemne("Grunt");
    StworzenieZiemne muddy = StworzenieZiemne("Muddy");

    //Stworzenia powietrzne
    StworzeniePowietrzne windigo = StworzeniePowietrzne("Windigo");
    StworzeniePowietrzne featherly = StworzeniePowietrzne("Featherly");
    StworzeniePowietrzne flown = StworzeniePowietrzne("Flown");

    //Stworzenia lodowe
    StworzenieLodowe snowy = StworzenieLodowe("Snowy");
    StworzenieLodowe icey = StworzenieLodowe("Icey");
    StworzenieLodowe freezer = StworzenieLodowe("Freezer");

    //Stworzenia stalowe
    StworzenieStalowe steelker = StworzenieStalowe("Steelker");
    StworzenieStalowe gears = StworzenieStalowe("Gears");
    StworzenieStalowe drillo = StworzenieStalowe("Drillo");

    const vector<Stworzenie*> pulaStworzen {
        &plop, &splash, &streamy,
        &solar, &flamer, &flaren,
        &rocky, &grunt, &muddy,
        &windigo, &featherly, &flown,
        &snowy, &icey, &freezer,
        &steelker, &gears, &drillo
    };

    wyborPoziomu(poziomTrudnosci);
    wyborDruzyny(pulaStworzen, pulaGracza);
    aktualneStworzenie = pulaGracza.at(0);

    while(!czyPrzegrana && !koniecGry){
        losowaniePrzeciwnikow(poziomTrudnosci, pulaStworzen, pulaPrzeciwnika);
        stworzeniePrzeciwnkika = pulaPrzeciwnika.at(0);

        cout << "Twoje stworzenia:\n";
        wyswietlPule(pulaGracza);
        cout << "Stworzenia przeciwnika:\n";
        wyswietlPule(pulaPrzeciwnika);

        while(!pustaPula(pulaPrzeciwnika) && !czyPrzegrana){
            cout << "RUNDA " << runda << " TURA " << tura << endl;

            cout << "Twoje stworzenie:\n";
            cout << *aktualneStworzenie << endl;

            cout << "Stworzenie przeciwnika:\n";
            cout << *stworzeniePrzeciwnkika << endl;

            udanyRuch = false;
            while(!udanyRuch){
                udanyRuch = ruchGracza(
                        pulaGracza, aktualneStworzenie, stworzeniePrzeciwnkika);
            }

            if(pustaPula(pulaPrzeciwnika)){
                cout << "Przeciwnik pokonany!" << endl;
                if(runda == poziomTrudnosci){
                    cout << "WYGRANA!!!\nGRATULACJE!!!" << endl;
                }
                else{
                    usun(pulaPrzeciwnika);
                    ulecz(pulaGracza);
                    przywrocSile(pulaGracza);
                    dodajExp(aktualneStworzenie, stworzeniePrzeciwnkika);
                    runda++;
                }
            }

            else if(!stworzeniePrzeciwnkika->getWGrze())
                zemdlaleLos(pulaPrzeciwnika, stworzeniePrzeciwnkika);

            else{
                udanyRuch = false;
                while(!udanyRuch){
                    udanyRuch =  ruchPrzeciwnika(
                            pulaPrzeciwnika, stworzeniePrzeciwnkika, aktualneStworzenie);
                }

                if(pustaPula(pulaGracza)){
                    cout << "Przegrana" << endl;
                    czyPrzegrana = true;
                    runda = poziomTrudnosci+1;
                }

                else if(!aktualneStworzenie->getWGrze())
                    zemdlaleWybor(pulaGracza, aktualneStworzenie);

            }
            koniecGry = koniec(poziomTrudnosci, runda);
            tura++;
        }

    }
}
