//
//  main.cpp
//  TSP_GeneticAlgorithm
//
//  Created by Jakub Sanecki on 02.12.2017.
//  Copyright © 2017 Jakub Sanecki. All rights reserved.
//


#include <iostream>
#include <memory>
#include <cstdlib>
#include "TSP.h"
//#include "tabooQueue.h"

bool isNumber( const string&);

int main(int argc, char** argv)
{
    unique_ptr <ProblemKomiwojazera> instancjaProblemu;
    string opcja_liczba_miast;
    string opcja_menu;
    string opcja_podmenu;
    string nazwa_pliku;
    
    while (true)
    {
        cout << "Prosze podaj liczbe miast wieksza od 2: " << endl;
        getline(cin, opcja_liczba_miast);
        
        if(isNumber(opcja_liczba_miast))
        {
            int liczba_miast = atoi(opcja_liczba_miast.c_str());
            if (liczba_miast > 2)
            {
                instancjaProblemu = unique_ptr<ProblemKomiwojazera>
                (new ProblemKomiwojazera(liczba_miast));
                break;
            }
            else
            {
                cout << "Zle dane ! "<< endl;
                system("pause");
                system("cls");
                continue;
            }
        }
        else
        {
            cout << "Zle dane ! "<< endl;
            system("pause");
            system("cls");
        }
    }
    system("cls");
    
    while (true)
    {
        if(opcja_menu[0] == 'd')
        {
            cout << "Program zakonczony!" << endl;
            system("pause");
            break;
        }
        
        cout << "Wybrano "
        << instancjaProblemu->pobierzLiczbeMiast() << " miast." <<endl;
        cout << endl;
        cout << "MENU:" <<endl;
        cout << "a) Wygeneruj nowa instancje problemu;" <<endl;//to
        cout << "b) Wyswietl macierz sasiedztwa;" << endl; //to
        cout << "c) Algorytm Genetyczny;" << endl; //to
        cout << "d) Wyjscie." << endl; //to
        
        
        cout << endl << "Podaj opcje: ";
        getline(cin, opcja_menu);
        cout << endl;
        
        switch(opcja_menu[0])
        {
            case 'a':
            {
                cout << "Prosze podaj liczbe miast wieksza od 2: ";
                getline(cin, opcja_liczba_miast);
                
                if(isNumber(opcja_liczba_miast))
                {
                    int liczba_miast = atoi(opcja_liczba_miast.c_str());
                    
                    if (liczba_miast > 2)
                    {
                        instancjaProblemu = unique_ptr<ProblemKomiwojazera>
                        (new ProblemKomiwojazera(liczba_miast));
                        cout << "Wygenerowano nowa instancje" << endl;
                        system("pause");
                        system("cls");
                        break;
                    }
                    else
                    {
                        cout << "Zle dane ! "<< endl;
                        system("pause");
                        system("cls");
                        break;
                    }
                    
                }
                else
                {
                    cout << "Zle dane ! "<< endl;
                    system("pause");
                    system("cls");
                }
                break;
            }
            case 'b':
            {
                instancjaProblemu->wyswietlMacierzSasiedztwa();
                system("pause");
                system("cls");
                break;
            }
            case 'c':
            {
                int liczba_osobnikow_populacji, liczba_iteracji;
                cout << "Algorytm genetyczny :" << endl;
                cout << "Podaj liczbe osobnikow populacji: ";
                cin >> liczba_osobnikow_populacji;
                cout << endl;
                cout << "Podaj liczbe iteracji: ";
                cin >> liczba_iteracji;
                cout << endl;
                instancjaProblemu->AlgorytmGenetyczny(liczba_osobnikow_populacji, liczba_iteracji);
                system("pause");
                system("cls");
                break;
            }
            case 'd':
            {
                system("cls");
                break;
            }
            default:
            {
                cout << "Zla opcja ! "<< endl;
                system("pause");
                system("cls");
                break;
            }
                
        }
        
    }
    return 0;
}

bool isNumber( const string& wzorzec )
{
    
    for( char znak : wzorzec )
    {
        if( !isdigit( znak ) )
            return 0 ;
    }
    return 1 ;
}
