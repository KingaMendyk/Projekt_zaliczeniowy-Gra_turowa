//
// Created by kinga on 16.06.2022.
//

#ifndef PROJEKT_STWORZENIA_H
#define PROJEKT_STWORZENIA_H

#include "Stworzenie.h"

class StworzenieWodne : public Stworzenie {
    std::map<Typ, double> mapa{
            {WODA, 0.75},
            {ZIEMIA, 1.25},
            {POWIETRZE, 1},
            {OGIEN, 1.25},
            {LOD, 1},
            {STAL, 1}
    };
public:
    explicit StworzenieWodne(std::string nazwa);
    double modyfikator(Stworzenie &stworzenie) override;
};

class StworzenieZiemne : public Stworzenie {
    std::map<Typ, double> mapa{
            {WODA, 1},
            {ZIEMIA, 1},
            {POWIETRZE, 0.75},
            {OGIEN, 1.25},
            {LOD, 1.25},
            {STAL, 1.25}
    };
public:
    explicit StworzenieZiemne(std::string nazwa);
    double modyfikator(Stworzenie &stworzenie) override;
};

class StworzenieOgniste : public Stworzenie{
    std::map<Typ, double> mapa{
            {WODA, 0.75},
            {ZIEMIA, 0.75},
            {POWIETRZE, 1},
            {OGIEN, 0.75},
            {LOD, 1.25},
            {STAL, 1.25}
    };
public:
    explicit StworzenieOgniste(std::string nazwa);
    double modyfikator(Stworzenie &stworzenie) override;
};

class StworzeniePowietrzne : public Stworzenie{
    std::map<Typ, double> mapa{
            {WODA, 1},
            {ZIEMIA, 0.75},
            {POWIETRZE, 1},
            {OGIEN, 1},
            {LOD, 1.25},
            {STAL, 0.75}
    };
public:
    explicit StworzeniePowietrzne(std::string nazwa);
    double modyfikator(Stworzenie &stworzenie) override;
};

class StworzenieLodowe : public Stworzenie{
    std::map<Typ, double> mapa{
            {WODA, 0.75},
            {ZIEMIA, 1.25},
            {POWIETRZE, 1},
            {OGIEN, 0.75},
            {LOD, 0.75},
            {STAL, 1}
    };
public:
    explicit StworzenieLodowe(std::string nazwa);
    double modyfikator(Stworzenie &stworzenie) override;
};

class StworzenieStalowe : public Stworzenie{
    std::map<Typ, double> mapa{
            {WODA, 1.25},
            {ZIEMIA, 1},
            {POWIETRZE, 1.25},
            {OGIEN, 0.75},
            {LOD, 1},
            {STAL, 0.75}
    };
public:
    explicit StworzenieStalowe(std::string nazwa);
    double modyfikator(Stworzenie &stworzenie) override;
};

#endif //PROJEKT_STWORZENIA_H
