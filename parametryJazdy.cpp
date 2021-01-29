#include "parametryJazdy.h"
#include <stdio.h>      
#include <stdlib.h> 
#include <algorithm>
#include <iostream>
#include <time.h>
#include <iterator>
#include <string>
using namespace std;

void parametryJazdy::losowanie_danych_samochodu()
{
	string imie;
	cout << " Zeby dodac do symulacji element losowosci - wpisz swoje imie." << endl;
	cin >> imie;
	if (cin.bad())
	{
		cin.clear();
		cout << " Musi byc wpisane slowo!!" << endl;
		cin >> imie;
	}
	string nazwisko;
	cout << " Wpisz swoje nazwisko." << endl;
	cin >> nazwisko;
	if (cin.bad())
	{
		cin.clear();
		cout << " Musi byc wpisane slowo!!" << endl;
		cin >> nazwisko;
	}

	int iloczyn = imie.size() * nazwisko.size();
	if (iloczyn < 25)
	{
		cout << " Jezdzisz Fiatem Punto" << endl;
		ilosc_oleju = imie.size()/2 - 0.75;
		ilosc_paliwa = nazwisko.size() * 4.;
		pozostala_ilosc_oleju = ilosc_oleju;
		pozostala_ilosc_paliwa = ilosc_paliwa;
		stala_A_do_spalania = 0.001;
		stala_B_do_spalania = 2.5;
		maksymalne_optymalne_spalanie = 2500 * stala_A_do_spalania + stala_B_do_spalania;
		zuzywanie_oleju = 0.75; //l/1000km
		przyspieszenie = 4.5; //km/h/s
		cout << " W samohodzie masz " << ilosc_paliwa << "l paliwa i " << ilosc_oleju << "l oleju." << endl;
	}
	else if (iloczyn > 24 && iloczyn < 60)
	{
		cout << " Jezdzisz Toyota Auris" << endl;
		ilosc_oleju = imie.size()/2 + 1.75;
		ilosc_paliwa = nazwisko.size() * 4.5;
		pozostala_ilosc_oleju = ilosc_oleju;
		pozostala_ilosc_paliwa = ilosc_paliwa;
		stala_A_do_spalania = 0.0025;
		stala_B_do_spalania = 1.75;
		maksymalne_optymalne_spalanie = 2500 * stala_A_do_spalania + stala_B_do_spalania;
		zuzywanie_oleju = 1; //l/1000km
		przyspieszenie = 5.7;  //km/h/s
		cout << " W samohodzie masz " << ilosc_paliwa << "l paliwa i " << ilosc_oleju << "l oleju." << endl;
	}
	else
	{
		cout << " Jezdzisz Nissanem Navara" << endl;
		ilosc_oleju = imie.size()/2 + 3.55;
		ilosc_paliwa = nazwisko.size() * 5.5;
		pozostala_ilosc_oleju = ilosc_oleju;
		pozostala_ilosc_paliwa = ilosc_paliwa;
		stala_A_do_spalania = 0.004;
		stala_B_do_spalania = 1;
		maksymalne_optymalne_spalanie = 2500 * stala_A_do_spalania + stala_B_do_spalania;
		zuzywanie_oleju = 1.25; //l/1000km
		przyspieszenie = 6.3;  //km/h/s
		cout << " W samohodzie masz " << ilosc_paliwa << "l paliwa i " << ilosc_oleju << "l oleju." << endl;
	}

	cout << " Milej jazdy!" << endl;
}

void parametryJazdy::dzialanie(int stala, double czas)
{
	if (stala == 1)
	{
		przyspieszanie(czas);
		monitoring_biegow();
	}
	else if(stala == 2)
	{
		hamowanie(czas);
		monitoring_biegow();
	}
	else if (stala == 3)
	{
		jazda_const(czas);
		monitoring_biegow();
	}
	else if (stala == 4)
	{
		zmiana_biegu_G();
		monitoring_biegow();
	}
	else if (stala == 5)
	{
		zmiana_biegu_D();
		monitoring_biegow();
	}
	else {}
}

void parametryJazdy::przyspieszanie(double czas)
{
		predkosc = predkosc + przyspieszenie*czas;
		double	obroty_poczatku = obroty;
		obroty_od_biegu(predkosc);
		double	obroty_konca = obroty;
		double czas_w_godzinach = czas / 3600;
		spalanie_od_obrotow(obroty_poczatku, obroty_konca, czas_w_godzinach);
		pozostala_ilosc_paliwa = pozostala_ilosc_paliwa - spalanie;
		zuzycie_oleju(czas_w_godzinach);
}

void parametryJazdy::hamowanie(double czas)
{
		predkosc = predkosc -(przyspieszenie-1.25) * czas;
		double obroty_poczatku = obroty;
		obroty_od_biegu(predkosc);
		double obroty_konca = obroty;
		double czas_w_godzinach = czas / 3600;
		spalanie_od_obrotow(obroty_poczatku, obroty_konca, czas_w_godzinach);
		pozostala_ilosc_paliwa = pozostala_ilosc_paliwa - spalanie;
		zuzycie_oleju(czas_w_godzinach);
}

void parametryJazdy::jazda_const(double czas)
{
	double obroty_poczatku = obroty;
	obroty_od_biegu(predkosc);
	double obroty_konca = obroty;
	double czas_w_godzinach = czas / 3600;
	spalanie_od_obrotow(obroty_poczatku, obroty_konca, czas_w_godzinach);
	pozostala_ilosc_paliwa = pozostala_ilosc_paliwa - spalanie;
	zuzycie_oleju(czas_w_godzinach);
}

void parametryJazdy::zmiana_biegu_G()
{
	bieg=+1;
	obroty_od_biegu(predkosc);
}

void parametryJazdy::zmiana_biegu_D()
{
	bieg=-1;
	obroty_od_biegu(predkosc);
}

double parametryJazdy::obroty_od_biegu(double PRedkosc)
{
	PRedkosc = predkosc; 

	if (bieg == 1)
	{
		obroty = 67.9217 * PRedkosc + 725;
	}
	else if (bieg == 2)
	{
		obroty = 43.6747 * PRedkosc + 750;
	}
	else if (bieg == 3)
	{
		obroty = 28.3133 * PRedkosc + 800;
	}
	else if (bieg == 4)
	{
		obroty = 21.3855 * PRedkosc + 8500;
	}
	else if (bieg == 5)
	{
		obroty = 18.6747 * PRedkosc + 900;
	}
	else if (bieg == 6)
	{
		obroty = 14.4578 * PRedkosc + 1000;
	}
	return obroty;
}

double parametryJazdy::spalanie_od_obrotow(double obr1, double obr2, double czass)
{
	double spalanie1=obr1 * stala_A_do_spalania + stala_B_do_spalania;
	wektor_historia_spalania.push_back(obr2);
	double spalanie2 = obr2 * stala_A_do_spalania + stala_B_do_spalania;
	double spalanie_srednie = (spalanie1 + spalanie2) / 2;
	double przejechana_droga = predkosc * czass;
	spalanie = spalanie_srednie * przejechana_droga / 100;
	pozostala_ilosc_paliwa = pozostala_ilosc_paliwa - spalanie;
	return spalanie;
}

double parametryJazdy::zuzycie_oleju(double czass)
{
	double przejechana_droga = predkosc * czass;
	double zuzycie_oleju = przejechana_droga * zuzywanie_oleju/1000;
	pozostala_ilosc_oleju = pozostala_ilosc_oleju - zuzycie_oleju;
	return pozostala_ilosc_oleju;
}

void parametryJazdy::monitoring_biegow()
{
	if (predkosc > 19 && obroty > 2015.51 && bieg==1) //1
		{
			cout << " Zmien na wyzszy bieg - na dwojke" << endl;
		}
	else
		if (35 > predkosc > 11 && obroty < 1230.42 && bieg == 2) //2
		{
			cout << " Jedziesz bardzo wolno, moze zmien na nizszy bieg - na jedynke" << endl;
		}
	else
		if (35 > predkosc > 11 && obroty > 2278.61 && bieg == 2) //3 
		{
			cout << " Zmien na wyzszy bieg - na trojke" << endl;
		}
	else 
		if (54 > predkosc > 21 && obroty < 1394.58 && bieg == 3) //4 
		{
			cout << " Zmien na nizszy bieg - na dwojke" << endl;
		}
	else 
		if (54 > predkosc > 21 && obroty > 2328.92 && bieg == 3) //5
		{
			cout << " Zmien na wyzszy bieg - na czworke" << endl;
		}
	else
		if (65 > predkosc > 41 && obroty < 1726.81 && bieg == 4) //6
		{
			cout << " Zmien na nizszy bieg - na trojke" << endl;
		}
	else
		if (65 > predkosc > 41 && obroty > 2240.06 && bieg == 4) //7 
		{
			cout << " Zmien na wyzszy bieg - na piatke" << endl;
		}
	else
		if (96 > predkosc > 56 && obroty < 1945.78 && bieg == 5) //8 
		{
			 cout << " Zmien na nizszy bieg - na czworke" << endl;
		}
	else
		if (predkosc > 68 && obroty > 2692.77 && bieg == 5) //9 
		{
			 cout << " Zmien na wyzszy bieg - na szostke - najwyzszy bieg" << endl;
		}
	else
		if (predkosc > 68 && obroty < 1983.13 && bieg == 6) //10
		{
			cout << " Zmien na nizszy bieg - na piatke" << endl;
		}
}

void parametryJazdy::monitoring_spalania()
{
	cout << "W poporzednich przedzialach czasu w pewnym momencie spalanie osiagnelo wartosci: \n";
	for (auto& i : wektor_historia_spalania)
	{
		double spalanie_w_itym_momencie = i * stala_A_do_spalania + stala_B_do_spalania;
		cout<< "\t"<< spalanie_w_itym_momencie <<endl;
	}
	
	for (vector<double>::iterator it = wektor_historia_spalania.begin(); it != wektor_historia_spalania.end(); ++it)
	{
		if (any_of(wektor_historia_spalania.begin(), wektor_historia_spalania.end(), [&](double x){return x==wysokie_spalanie(*it); } ))
			{
				ilosc++;
				cout <<  " Na "<< ilosc <<" etapie/ach jazdy jechales/as malo ekonomicznie, postaraj sie tak nie robic wiecej :/"<<endl;
			}
	}	

	std::sort(wektor_historia_spalania.begin(), wektor_historia_spalania.end());
	cout << "\n Jesli z jakiegos powodu istnieje potrzeba spojrzenia na dotychczasowe spalanie w rosnacej liscie to oto ona: \n" << endl;
	for (auto& i : wektor_historia_spalania)
	{
		double spalanie_w_itym_momencie = i * stala_A_do_spalania + stala_B_do_spalania;
		cout << "\t" << spalanie_w_itym_momencie << endl;
	}
}

bool parametryJazdy::wysokie_spalanie(double historia)
{
	double faktyczne_spalanie = historia * stala_A_do_spalania + stala_B_do_spalania;
		
	if (faktyczne_spalanie > maksymalne_optymalne_spalanie)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void parametryJazdy::koniec_jazdy()
{
	obroty = 0;
}

double parametryJazdy::get_pozostala_ilosc_paliwa()
{
	return pozostala_ilosc_paliwa;
}

double parametryJazdy::get_pozostala_ilosc_oleju()
{
	return pozostala_ilosc_oleju;
}

double parametryJazdy::get_ilosc_paliwa()
{
	return ilosc_paliwa;
}

double parametryJazdy::get_ilosc_oleju()
{
	return ilosc_oleju;
}

double parametryJazdy::get_obroty()
{
	return obroty;
}

double parametryJazdy::get_predkosc()
{
	return predkosc;
}

int parametryJazdy::get_bieg()
{
	return bieg;
}
