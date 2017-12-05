//
//  TSP.cpp
//  TSP_GeneticAlgorithm
//
//  Created by Jakub Sanecki on 02.12.2017.
//  Copyright © 2017 Jakub Sanecki. All rights reserved.
//


#include "TSP.h"
#include "myClock.h"

MyClock myClock;

ProblemKomiwojazera::ProblemKomiwojazera()
{
}

ProblemKomiwojazera::ProblemKomiwojazera(int liczba_miast) :
liczba_miast_(liczba_miast),
macierz_sasiedztwa_(liczba_miast_, vector<int>(liczba_miast_, -1)),
zmienna_losujaca_(0)
{
    losujOdleglosciZPrzedzialuDoMacierzySasiedztwa(0,100);
    odbicieSymetryczneWzgledemGlownejPrzekatnej();
}

ProblemKomiwojazera::ProblemKomiwojazera(const ProblemKomiwojazera& orig)
{
}

ProblemKomiwojazera::~ProblemKomiwojazera()
{
}

//
void ProblemKomiwojazera::wyswietlMacierzSasiedztwa()
{
    cout << "Liczba miast: " << liczba_miast_ << " ;" << endl;
    cout << endl;
    
    for (auto wiersz : macierz_sasiedztwa_)
    {
        for (auto kolumna : wiersz)
        {
            cout << kolumna << '\t';
        }
        cout << endl;
    }
}

void ProblemKomiwojazera::zmienLiczbeMiast(int nowa_liczba_miast)
{
    liczba_miast_ = nowa_liczba_miast;
    macierz_sasiedztwa_.clear();
    macierz_sasiedztwa_.resize(nowa_liczba_miast, vector <int> (nowa_liczba_miast, -1));
    
    losujOdleglosciZPrzedzialuDoMacierzySasiedztwa(0,100);
    odbicieSymetryczneWzgledemGlownejPrzekatnej();
    
}

//For building tree
void ProblemKomiwojazera::losujOdleglosciZPrzedzialuDoMacierzySasiedztwa(int poczatek_przedzialu, int koniec_przedzialu)
{
    auto aktualny_czas = chrono::system_clock::now().time_since_epoch().count();
    mt19937 silnik_losujacy_liczby(aktualny_czas);
    uniform_int_distribution<int> rozklad_liczb_losowych
    (poczatek_przedzialu, koniec_przedzialu);
    
    auto generator_odleglosci = bind(rozklad_liczb_losowych, silnik_losujacy_liczby);
    
    for(unsigned wiersz = 0; wiersz < macierz_sasiedztwa_.size(); ++wiersz)
    {
        for(unsigned kolumna = wiersz + 1; kolumna < macierz_sasiedztwa_.size(); ++kolumna)
        {
            macierz_sasiedztwa_[wiersz][kolumna] = generator_odleglosci();
        }
    }
}
//For building tree
void ProblemKomiwojazera::odbicieSymetryczneWzgledemGlownejPrzekatnej()
{
    for(unsigned wiersz = 0; wiersz < macierz_sasiedztwa_.size(); ++wiersz)
    {
        for(unsigned kolumna = wiersz + 1; kolumna < macierz_sasiedztwa_.size(); ++kolumna)
        {
            macierz_sasiedztwa_[kolumna][wiersz] =
            macierz_sasiedztwa_[wiersz][kolumna];
        }
    }
}
//For initializing first path
void ProblemKomiwojazera::generowanieLosowejPermutacji(int* tablica)
{
    
    for(int index = 0; index < liczba_miast_; ++index)
    {
        tablica[index] = index;
    }
    random_shuffle(tablica,tablica+liczba_miast_);
    
}
//For initializing first path
void ProblemKomiwojazera::generowanieLosowejPermutacji(vector<int> &tablica)
{
    
    for(int index = 0; index < liczba_miast_; ++index)
    {
        tablica[index] = index;
    }
    random_shuffle(tablica.begin(),tablica.end());
    
}
//Displaying matrix
void ProblemKomiwojazera::wyswietlKombinacjeMiast(int* kombinacja_miast, int suma_odleglosci_pomiedzy_nimi)
{
    cout << endl << "Permutacja : " << endl;
    
    for (int index = 0; index < liczba_miast_ ;++index)
    {
        cout << kombinacja_miast[index] << " -> ";
    }
    
    cout << endl;
    cout << "Suma odlegosci: " << suma_odleglosci_pomiedzy_nimi << endl;
}
//Displaying matrix
void ProblemKomiwojazera::wyswietlKombinacjeMiast(vector <int> kombinacja_miast, int suma_odleglosci_pomiedzy_nimi)
{
    cout << endl << "Permutacja : " << endl;
    
    for (int index = 0; index < liczba_miast_ ;++index)
    {
        cout << kombinacja_miast[index] << " -> ";
    }
    
    cout << endl;
    cout << "Suma odlegosci: " << suma_odleglosci_pomiedzy_nimi << endl;
}
//Counting sum of distance between the cities
int ProblemKomiwojazera::sumaOdleglosciDoPokonaniaPomiedzyMiastami(int * kombinacja_miast)
{
    int sumaOdleglosci = 0;
    
    for (int i = 0; i < liczba_miast_ - 1; ++i)
    {
        sumaOdleglosci += macierz_sasiedztwa_[kombinacja_miast[i]][kombinacja_miast[i + 1]];
    }
    sumaOdleglosci += macierz_sasiedztwa_[kombinacja_miast[liczba_miast_ - 1]][kombinacja_miast[0]];
    
    return sumaOdleglosci;
}
//Counting sum of distance between the cities
int ProblemKomiwojazera::sumaOdleglosciDoPokonaniaPomiedzyMiastami(vector <int> kombinacja_miast)
{
    int sumaOdleglosci = 0;
    
    for (int i = 0; i < kombinacja_miast.size() - 1; ++i)
    {
        sumaOdleglosci += macierz_sasiedztwa_[kombinacja_miast[i]][kombinacja_miast[i + 1]];
    }
    sumaOdleglosci += macierz_sasiedztwa_[kombinacja_miast[liczba_miast_ - 1]][kombinacja_miast[0]];
    
    return sumaOdleglosci;
}

//Generating Real Number in Genetic
double ProblemKomiwojazera::generowanieLosowejLiczbyRzeczywistejZPrzedzialu(double poczatek_przedzialu, double koniec_przedzialu)
{
    auto aktualny_czas = chrono::system_clock::now().time_since_epoch().count() + zmienna_losujaca_;
    mt19937 silnik_losujacy_liczby(aktualny_czas);
    uniform_real_distribution<double> rozklad_liczb_losowych
    (poczatek_przedzialu, koniec_przedzialu);
    
    auto generator_liczby_rzeczywistej = bind(rozklad_liczb_losowych, silnik_losujacy_liczby);
    
    ++zmienna_losujaca_;
    return generator_liczby_rzeczywistej();
}

//For OX crossing
int ProblemKomiwojazera::generowanieLosowejLiczbyCalkowitejZPrzedzialu(int poczatek_przedzialu, int koniec_przedzialu)
{
    auto aktualny_czas = chrono::system_clock::now().time_since_epoch().count() + zmienna_losujaca_;
    mt19937 silnik_losujacy_liczby(aktualny_czas);
    uniform_int_distribution<int> rozklad_liczb_losowych
    (poczatek_przedzialu, koniec_przedzialu);
    
    auto generator_liczby_calkowitej = bind(rozklad_liczb_losowych, silnik_losujacy_liczby);
    
    ++zmienna_losujaca_;
    return generator_liczby_calkowitej();
}

//Creating copy of an array
void ProblemKomiwojazera::wykonanieKopiiTablicy(int* zrodlo, int* kopia)
{
    for (int index = 0; index < liczba_miast_; ++index)
    {
        kopia[index] = zrodlo[index];
    }
}


//mutation
void ProblemKomiwojazera::mutacja(vector<int> &kombinacja_miast)
{
    auto aktualny_czas = chrono::system_clock::now().time_since_epoch().count() + zmienna_losujaca_;
    mt19937 silnik_losujacy_liczby(aktualny_czas);
    uniform_int_distribution<int> rozklad_liczb_losowych
    (0, liczba_miast_ - 1);
    
    auto generator_indeksu = bind(rozklad_liczb_losowych, silnik_losujacy_liczby);
    
    int pierwszy_losowy_indeks, drugi_losowy_indeks;
    
    pierwszy_losowy_indeks = generator_indeksu();
    
    do
    {
        drugi_losowy_indeks = generator_indeksu();
    }
    while(pierwszy_losowy_indeks == drugi_losowy_indeks);
    
    swap(kombinacja_miast[pierwszy_losowy_indeks], kombinacja_miast[drugi_losowy_indeks]);
    
    ++zmienna_losujaca_;
}

void ProblemKomiwojazera::krzyzowanieOX(vector<int> rodzic1, vector<int> rodzic2
                                        ,vector<int> &dziecko1, vector<int> &dziecko2)
{
    int punkt_krzyzowania1 = -1;
    int punkt_krzyzowania2 = -1;
    int tmp = 0;
    while (punkt_krzyzowania1 == punkt_krzyzowania2)
    {
        punkt_krzyzowania1 = generowanieLosowejLiczbyCalkowitejZPrzedzialu(0, liczba_miast_-1);
        punkt_krzyzowania2 = generowanieLosowejLiczbyCalkowitejZPrzedzialu(0, liczba_miast_-1);
        
    }
    
    if (punkt_krzyzowania1 > punkt_krzyzowania2)
        swap(punkt_krzyzowania1, punkt_krzyzowania2);
    
    for (int i = punkt_krzyzowania1; i < punkt_krzyzowania2; ++i)
    {
        dziecko1[i] = rodzic2[i];
        rodzic2[i] = -1;
        dziecko2[i] = rodzic1[i];
        rodzic1[i] = -1;
    }
    
    for (int i = punkt_krzyzowania2; i < liczba_miast_; ++i)
    {
        while (rodzic2[tmp] == -1)
            ++tmp;
        
        dziecko1[i] = rodzic2[tmp];
        dziecko2[i] = rodzic1[tmp];
        ++tmp;
    }
    for (int i = 0; i < punkt_krzyzowania1; ++i)
    {
        while (rodzic2[tmp] == -1)
            ++tmp;
        
        dziecko1[i] = rodzic2[tmp];
        dziecko2[i] = rodzic1[tmp];
        ++tmp;
    }
}

vector<Osobnik> ProblemKomiwojazera::Selekcja(vector<Osobnik> populacja, int liczba_osobnikow)
{
    vector<Osobnik> wyselekcjonowana_populacja(liczba_osobnikow);
    
    sort(populacja.begin(),populacja.end());
    
    for (int i=0; i < wyselekcjonowana_populacja.size();++i)
    {
        wyselekcjonowana_populacja[i] = populacja[i];
    }
    
    return wyselekcjonowana_populacja;
}

void ProblemKomiwojazera::AlgorytmGenetyczny(int liczba_osobnikow, int liczba_iteracji)
{
    
    myClock.start();
    vector<Osobnik> populacja(liczba_osobnikow);
    vector<int> dziecko1(liczba_miast_);
    vector<int> dziecko2(liczba_miast_);
    
    //Generujemy populację początkową Każdy osobnik ma ptzypisana sciezke i wartosc funkcji celu.
    for (int i=0; i< populacja.size(); ++i)
    {
        populacja[i].sciezka = vector<int>(liczba_miast_);
        generowanieLosowejPermutacji(populacja[i].sciezka);
        populacja[i].wartosc_funkcji_celu = sumaOdleglosciDoPokonaniaPomiedzyMiastami(populacja[i].sciezka);
    }
    //from user input
    for (int i =0; i < liczba_iteracji;++i)
    {
        random_shuffle(populacja.begin(),populacja.end());
        
        for (int i=0; i < liczba_osobnikow; i +=2)
        {
            if(generowanieLosowejLiczbyRzeczywistejZPrzedzialu(0.0,1.0) < generowanieLosowejLiczbyRzeczywistejZPrzedzialu(0.2,0.5))
            {
                krzyzowanieOX(populacja[i].sciezka, populacja[i+1].sciezka,dziecko1, dziecko2);
                Osobnik tymczasowy;
                tymczasowy.sciezka = dziecko1;
                tymczasowy.wartosc_funkcji_celu = sumaOdleglosciDoPokonaniaPomiedzyMiastami(dziecko1);
                populacja.push_back(tymczasowy);
                tymczasowy.sciezka = dziecko2;
                tymczasowy.wartosc_funkcji_celu = sumaOdleglosciDoPokonaniaPomiedzyMiastami(dziecko2);
                populacja.push_back(tymczasowy);
            }
        }
        
        for (int i=0; i < populacja.size(); ++i)
        {
            if(generowanieLosowejLiczbyRzeczywistejZPrzedzialu(0.0,1.0) < generowanieLosowejLiczbyRzeczywistejZPrzedzialu(0.0,0.01))
            {
                mutacja(populacja[i].sciezka);
                populacja[i].wartosc_funkcji_celu = sumaOdleglosciDoPokonaniaPomiedzyMiastami(populacja[i].sciezka);
            }
        }
        
        populacja = Selekcja(populacja, liczba_osobnikow);
        
    }
    myClock.stop();
    wyswietlKombinacjeMiast(populacja[0].sciezka, populacja[0].wartosc_funkcji_celu);
    cout << endl << "Czas trwania algorytmu : " << myClock.getTime() << " sekund ." << endl;
}
