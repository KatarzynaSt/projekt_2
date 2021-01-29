#pragma once
#include <stdio.h>      
#include <stdlib.h> 
#include <iostream>
#include <time.h>
#include <vector>
#include <ctime>
#include <chrono>

#ifndef PARAMETRYJAZDY_H
#define PARAMETRYJAZDY_H

class parametryJazdy
{
public :
	parametryJazdy() { 
		bieg = 1;
		obroty = 725;
		predkosc = 0;
	};

	int get_bieg();
	int ilosc;
	
	void losowanie_danych_samochodu();	
	void dzialanie(int,double);
	void hamowanie(double);
	void jazda_const(double);
	void przyspieszanie(double);
	void zmiana_biegu_G();
	void zmiana_biegu_D();
	void monitoring_biegow();
	void koniec_jazdy();
	void monitoring_spalania();
	bool wysokie_spalanie(double);
	
	double spalanie_od_obrotow(double, double, double);
	double obroty_od_biegu(double);
	double zuzycie_oleju(double);
	double get_ilosc_paliwa();
	double get_ilosc_oleju();
	double get_pozostala_ilosc_paliwa();
	double get_pozostala_ilosc_oleju();
	double get_obroty();
	double get_predkosc();

	~parametryJazdy(){};

	protected:
	
	int bieg;
	int stala_B_do_spalania;

	double ilosc_paliwa;
	double stala_A_do_spalania;
	double zuzywanie_oleju;
	double maksymalne_optymalne_spalanie;
	double przyspieszenie;
	double ilosc_oleju;
	double predkosc;
	double spalanie;
	double obroty;
	double pozostala_ilosc_oleju;
	double pozostala_ilosc_paliwa;

	std::vector<double> wektor_historia_spalania;
	
};
#endif // !PARAMETRYJAZDY_H
