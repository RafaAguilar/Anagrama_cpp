/*
 * main.cpp
 *
 *  Created on: 07/09/2012
 *      Author: rafa
 */


#include <iostream>
#include "master.h"

int main(void)
{
	master *m= new master("teologia");
	m->inicio();
	delete m;
}
