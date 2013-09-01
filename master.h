/*
 * master.h
 *
 *  Created on: 06/09/2012
 *      Author: rafa
 */

#ifndef MASTER_H_
#define MASTER_H_
#include <pthread.h>
#include <vector>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/timer/timer.hpp>
using namespace std;
class master {
private:
	string base; //Palabra base a buscar sus anagramas
	int K; //Cantidade hilos a usar
	vector<string>* dicc;
	vector<string>* intentos;
	pthread_mutex_t* consola;
	pthread_mutex_t* diccIntentos;
public:
	master(string b);
	void inicio();
	void procesarDicc(vector<string>* d);
	void permutaciones(char conjunto[], size_t card, size_t elem, vector<string> *v);
	virtual ~master();
};
#include "master.cpp"
#endif /* MASTER_H_ */
