//
//  TSP.hpp
//  TSP_GeneticAlgorithm
//
//  Created by Jakub Sanecki on 02.12.2017.
//  Copyright © 2017 Jakub Sanecki. All rights reserved.
//


#ifndef PROBLEMKOMIWOJAZERA_H
#define    PROBLEMKOMIWOJAZERA_H

//#define STALA_EULERA 2.71828182845904523536

#include <algorithm>
#include <chrono>
#include <ctime>
#include <cmath>
#include <functional>
#include <fstream>
#include <iostream>
#include <limits>
#include <random>
#include <string>
#include <vector>

using namespace std;

struct Osobnik
{
    vector<int> sciezka;
    int wartosc_funkcji_celu;
    
    bool operator<(const Osobnik &o) const
    {
        return wartosc_funkcji_celu < o.wartosc_funkcji_celu;
    }
};

class ProblemKomiwojazera
{
public:
    ProblemKomiwojazera();
    ProblemKomiwojazera(int liczba_miast);
    ProblemKomiwojazera(const ProblemKomiwojazera& orig);
    virtual ~ProblemKomiwojazera();
    
    void AlgorytmGenetyczny(int liczba_osobnikow, int liczba_iteracji);
    
    vector<Osobnik> Selekcja(vector<Osobnik> populacja, int liczba_osobnikow);
    
    void mutacja(vector<int> &kombinacja_miast);
    void wyswietlMacierzSasiedztwa();
    void zmienLiczbeMiast(int nowa_liczba_miast);
    int pobierzLiczbeMiast() { return liczba_miast_;}
    void krzyzowanieOX(vector<int> rodzic1, vector<int> rodzic2,
                       vector<int> &dziecko1, vector<int> &dziecko2);
    
    
private:
    
    void odbicieSymetryczneWzgledemGlownejPrzekatnej();
    void losujOdleglosciZPrzedzialuDoMacierzySasiedztwa(int poczatek_przedzialu, int koniec_przedzialu);
    void generowanieLosowejPermutacji (int * tablica);
    void generowanieLosowejPermutacji(vector<int> &tablica);
    void wyswietlKombinacjeMiast(int * kombinacja_miast, int suma_odleglosci_pomiedzy_nimi);
    void wyswietlKombinacjeMiast(vector <int> kombinacja_miast,
                                 int suma_odleglosci_pomiedzy_nimi);
    int sumaOdleglosciDoPokonaniaPomiedzyMiastami(int * kombinacja_miast);
    int sumaOdleglosciDoPokonaniaPomiedzyMiastami(vector <int> kombinacja_miast);
    double generowanieLosowejLiczbyRzeczywistejZPrzedzialu(double poczatek_przedzialu, double koniec_przedzialu);
    int generowanieLosowejLiczbyCalkowitejZPrzedzialu(int poczatek_przedzialu, int koniec_przedzialu);
    void wykonanieKopiiTablicy(int * zrodlo, int * kopia);
    void inicjalizacjaTablicyJejNumeremIndexu (int * tablica);
    
    unsigned int zmienna_losujaca_;
    int liczba_miast_;
    vector<vector <int>> macierz_sasiedztwa_;
};

#endif    /* PROBLEMKOMIWOJAZERA_H */

