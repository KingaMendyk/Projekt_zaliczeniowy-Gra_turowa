//
// Created by kinga
//

#ifndef PROJEKT_STWORZENIE_H
#define PROJEKT_STWORZENIE_H

#include <iostream>
#include <random>
#include <map>

class Stworzenie {
public:
    enum Typ{NONE, WODA, ZIEMIA, OGIEN, POWIETRZE, LOD, STAL};
protected:
    std::string nazwa;
    double punktyZycia;
    int maxPunktyZycia;
    double silaPodstawowa;
    double sila;
    int iloscMocS;
    int zuzyteMoc;
    std::string mocSpecjalna[2];
    int exp;
    int przyjeteExp;
    int wymaganeExp;
    double zrecznosc;
    Typ typ;
    bool wGrze;
public:
    explicit Stworzenie(std::string &nazwa);
    Stworzenie(const Stworzenie &s);

    //gettery
    const std::string &getNazwa() const;

    Typ getTyp() const;
    int getPrzyjeteExp() const;
    bool getWGrze() const;
    int getWymaganeExp() const;
    const std::string *getMocSpecjalna() const;
    int getZuzyteMoc() const;

    virtual double modyfikator(Stworzenie &stworzenie);

    void atak(Stworzenie &stworzenie);
    void umiejetnoscSpecjalna(Stworzenie &stworzenie, int moc);
    void ewolucja(int atrybut1, int atrybut2);

    void zwiekszenieAtrybutu(int atrybut);
    static bool czyUnik(double zrecznosc);
    void przywrocSile();
    void ulecz();
    void dodajExp(Stworzenie &stworzenie);

    friend std::ostream &operator<<(std::ostream &os, const Stworzenie &stworzenie);
};


#endif //PROJEKT_STWORZENIE_H
