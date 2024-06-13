//
// Created by kinga on 16.06.2022.
//

#include "Stworzenia.h"

//Stworzenie wodne
StworzenieWodne::StworzenieWodne(std::string nazwa) : Stworzenie(nazwa) {
    punktyZycia = 60;
    maxPunktyZycia = 60;
    silaPodstawowa = 15;
    sila = silaPodstawowa;
    zrecznosc = 0.2;
    iloscMocS = 2;
    zuzyteMoc = iloscMocS;
    exp = 10;
    przyjeteExp = 0;
    wymaganeExp = 20;
    mocSpecjalna[0] = "Armata wodna";
    mocSpecjalna[1] = "Wodospad";
    typ = WODA;
    wGrze = true;
}

double StworzenieWodne::modyfikator(Stworzenie &stworzenie) {
    return mapa[stworzenie.getTyp()];
}


//Stworzenie ziemne
StworzenieZiemne::StworzenieZiemne(std::string nazwa) : Stworzenie(nazwa) {
    punktyZycia = 60;
    maxPunktyZycia = 60;
    silaPodstawowa = 10;
    sila = silaPodstawowa;
    zrecznosc = 0.2;
    iloscMocS = 2;
    zuzyteMoc = iloscMocS;
    exp = 20;
    przyjeteExp = 0;
    wymaganeExp = 25;
    mocSpecjalna[0] = "Gniot";
    mocSpecjalna[1] = "Skala";
    typ = ZIEMIA;
    wGrze = true;
}

double StworzenieZiemne::modyfikator(Stworzenie &stworzenie) {
    return mapa[stworzenie.getTyp()];
}


//Stworzenie ogniste
StworzenieOgniste::StworzenieOgniste(std::string nazwa) : Stworzenie(nazwa) {
    punktyZycia = 60;
    maxPunktyZycia = 60;
    silaPodstawowa = 15;
    sila = silaPodstawowa;
    zrecznosc = 0.3;
    iloscMocS = 2;
    zuzyteMoc = iloscMocS;
    exp = 10;
    przyjeteExp = 0;
    wymaganeExp = 20;
    mocSpecjalna[0] = "Kula ognia";
    mocSpecjalna[1] = "Ognisty krag";
    typ = OGIEN;
    wGrze = true;
}

double StworzenieOgniste::modyfikator(Stworzenie &stworzenie) {
    return mapa[stworzenie.getTyp()];
}


//Stworzenie powietrzne
StworzeniePowietrzne::StworzeniePowietrzne(std::string nazwa) : Stworzenie(nazwa) {
    punktyZycia = 60;
    maxPunktyZycia = 60;
    silaPodstawowa = 10;
    sila = silaPodstawowa;
    zrecznosc = 0.3;
    iloscMocS = 2;
    zuzyteMoc = iloscMocS;
    exp = 15;
    przyjeteExp = 0;
    wymaganeExp = 15;
    mocSpecjalna[0] = "Tornado";
    mocSpecjalna[1] = "Podmuch";
    typ = POWIETRZE;
    wGrze = true;
}

double StworzeniePowietrzne::modyfikator(Stworzenie &stworzenie) {
    return mapa[stworzenie.getTyp()];
}


//Stworzenie lodowe
StworzenieLodowe::StworzenieLodowe(std::string nazwa) : Stworzenie(nazwa) {
    punktyZycia = 60;
    maxPunktyZycia = 60;
    silaPodstawowa = 20;
    sila = silaPodstawowa;
    zrecznosc = 0.1;
    iloscMocS = 2;
    zuzyteMoc = iloscMocS;
    exp = 15;
    przyjeteExp = 0;
    wymaganeExp = 25;
    mocSpecjalna[0] = "Burza sniezna";
    mocSpecjalna[1] = "Tafla lodu";
    typ = LOD;
    wGrze = true;
}

double StworzenieLodowe::modyfikator(Stworzenie &stworzenie) {
    return mapa[stworzenie.getTyp()];
}


//Stworzenie stalowe
StworzenieStalowe::StworzenieStalowe(std::string nazwa) : Stworzenie(nazwa) {
    punktyZycia = 60;
    maxPunktyZycia = 60;
    silaPodstawowa = 20;
    sila = silaPodstawowa;
    zrecznosc = 0.1;
    iloscMocS = 2;
    zuzyteMoc = iloscMocS;
    exp = 15;
    przyjeteExp = 0;
    wymaganeExp = 20;
    mocSpecjalna[0] = "Swider";
    mocSpecjalna[1] = "Tarcza";
    typ = STAL;
    wGrze = true;
}

double StworzenieStalowe::modyfikator(Stworzenie &stworzenie) {
    return mapa[stworzenie.getTyp()];
}