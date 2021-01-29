#include <stdio.h>      
#include <stdlib.h> 
#include <iostream>
#include <string>
#include <ctime>
#include <ratio>
#include <chrono>
#include <time.h>
#include <any>
#include "parametryJazdy.h"
#include "samochod.h"
using namespace std;

void Samochod::jazda()
{
	//parametryJazdy moje_parametry;

	moje_parametry.losowanie_danych_samochodu();

	cout << " Aby ruszyc samochod wpisz - 'uruSiln' " << endl;
	string start;
	cin >> start;
	if (start != "uruSiln")
	{
		while (start != "uruSiln")
		{
	cout << " Ups chyba stoisz w miejsu, sprobuj jeszcze raz." << endl;
		cin.clear();
		cin >> start;
		}
	}
	if (start == "uruSiln")
	{
	cout << " Teraz mozesz wpisywac komendy, ktore powoduja zmiane zachowania samochodu." << endl;
	cout << " Twoj samochod ma 6-biegowa skrzynie biegow" << endl;
	cout << " Monituruj ilosci paliwa i oleju, aby samochod nie stanal w miejscu ani sie nie zniszczyl!" << endl;
	cout << " Mozesz wpisywac nastepujace komendy: \n\t speed \n\t slow \n\t const (jazda ze stala predkoscia) \n\t up (wrzucenie wyzszego biegu) \n\t down (wrzucenie nizszego biegu) \n\t param (pokazane zostana parametry jazdy oraz pozostale ilosci paliwa i oleju)"<<endl;
	cout << " Jesli chcesz sprawdzic spalanie w calej przebytej trasy - wpisz: spalanie ." << endl;
	cout << " Poprzednia komenda dotyczaca jazdy - speed, slow lub const - konczy sie, gdy wpiszesz nastepna, dowolna komende." << endl;
	cout << " Jesli chcesz zakonczyc jazde - wpisz: end ." << endl;

	chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
	
	while (moje_parametry.get_pozostala_ilosc_oleju()>0 && moje_parametry.get_pozostala_ilosc_paliwa()>0 && moje_parametry.get_obroty() != 0)
	{
		string f;
		cin >> f;
		chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
		try
			{
				throw f;
			}
		catch (string k)
			{
			if (k == "speed")
		{   
			std::chrono::duration<double, std::milli> time_span = t2 - t1;
			double czas = time_span.count();
			double czas_w_sekundach = czas / (1000);
			moje_parametry.dzialanie(stala, czas_w_sekundach);
			chrono::steady_clock::time_point t1 = chrono::steady_clock::now(); // zaczynam przyspieszac
			stala = 1;
		
		}
			else if (k == "slow")
		{
			std::chrono::duration<double, std::milli> time_span = t2 - t1;
			double czas = time_span.count();
			double czas_w_sekundach = czas/1000;
			moje_parametry.dzialanie(stala, czas_w_sekundach);
			chrono::steady_clock::time_point t1 = chrono::steady_clock::now(); //zaczynam hamowac
			stala = 2;
		}
			else if (k == "const")
		{
			std::chrono::duration<double, std::milli> time_span = t2 - t1;
			double czas = time_span.count();
			double czas_w_sekundach = czas / (1000);
			moje_parametry.dzialanie(stala, czas_w_sekundach);
			chrono::steady_clock::time_point t1 = chrono::steady_clock::now(); //zaczynam jechac const
			stala = 3;
		}
			else if (k == "up")
		{
			std::chrono::duration<double, std::milli> time_span = t2 - t1;
			double czas = time_span.count();
			double czas_w_sekundach = czas / (1000);
			moje_parametry.dzialanie(stala, czas_w_sekundach);
			chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
			stala = 4;
		}
			else if (k == "spalanie")
		{
			moje_parametry.monitoring_spalania();
		}
			else if (k == "down")
		{
			std::chrono::duration<double, std::milli> time_span = t2 - t1;
			double czas = time_span.count();
			double czas_w_sekundach = czas / (1000);
			moje_parametry.dzialanie(stala, czas_w_sekundach);
			chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
			stala = 5;
		}
			else if (k == "param")
		{
			cout << " Jedziesz na biegu " << moje_parametry.get_bieg() <<endl; 
			cout << " Jedziesz z predkoscia " << moje_parametry.get_predkosc()<< " km/h." << endl;
			cout << " Silnik pracuje na " << moje_parametry.get_obroty() << " obrotach." << endl;
			cout << " W Twoim samochodzie jest jeszcze "<< moje_parametry.get_pozostala_ilosc_paliwa()<<"l paliwa." << endl;
			cout << " W Twoim samochodzie jest jeszcze " << moje_parametry.get_pozostala_ilosc_oleju() << "l zdatnego do uzywania oleju." << endl; 
		}
			else if (k == "end")
		{
			if (moje_parametry.get_predkosc() < 5)
			{
				moje_parametry.koniec_jazdy();
				cout << " Zatrzymany silnik." << endl;
			}
			else 
			{
				cout << " Musisz jechac z predkoscia maksymalnie 5 km/h, aby zatrzymac silnik." << endl;
			}
		}
			else
			{
				cout << " Zly string, Twoj samochod nie umie takich rzeczy robic :/" << endl;
			}
			}

		catch (char a)
		{
			cout << " Zly char, Twoj samochod nie umie takich rzeczy robic :/" << endl;
		}
		catch (double d)
		{
			cout << " Zly double, Twoj samochod nie umie takich rzeczy robic :/" << endl;
		}
		catch (...)
		{
			cout << " To juz w ogole cos dziwnego, Twoj samochod nie umie takich rzeczy robic :/" << endl;
		}
	}
}


	if (moje_parametry.get_pozostala_ilosc_oleju() < 0)
	{
		cout << " Zatarles silnik, bo skonczyl sie olej, koniec jazdy, bo caly samochod dymi :/" << endl;
	}
	else if (moje_parametry.get_pozostala_ilosc_paliwa() < 0)
	{
		cout << " Skonczylo Ci sie paliwo, koniec jazdy :/" << endl;
	}
	else
	{
		cout << " Dzieki za bezpieczna jazde" << endl;
	}
}