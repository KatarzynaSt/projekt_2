#pragma once
#include "parametryJazdy.h"
#include <stdio.h>      
#include <stdlib.h> 
#include <iostream>
#include <string>
#include <time.h>
#include <ctime>


#ifndef SAMOCHOD_H
#define SAMOCHOD_H

class Samochod
{
public:
	Samochod()
	{};

	~Samochod() {};

	void jazda();

private:
	int stala = 0;
	parametryJazdy moje_parametry;

};

#endif // !SAMOCHOD_H
