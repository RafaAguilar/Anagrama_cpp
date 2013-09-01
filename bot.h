/*
 * bot.h
 *
 *  Created on: 06/09/2012
 *      Author: rafa
 */

#ifndef BOT_H_
#define BOT_H_
#include <iostream>
#include <string>
#include <vector>
#include <pthread.h>

using namespace std;
typedef std::vector<string>::iterator vec_iter;
class bot {
private:
	string Nombre;
	vec_iter inicio;
	vec_iter fin;
	vector<string>* dicc;
	vector<string>* intentos;
	pthread_mutex_t* consola;
	pthread_mutex_t* diccIntentos;
	void enviarMsj(string msj);
public:
	bot();
	bot(string n, vector<string> *dicc, vector<string> *inten, pthread_mutex_t* c,pthread_mutex_t* di);
	void inicializar(string n, vector<string> *dicc, vector<string> *inten, pthread_mutex_t* c,pthread_mutex_t* di);
	bot(string n, vector<string> *dicc,  vec_iter inicio, vec_iter fin, pthread_mutex_t* c,pthread_mutex_t* di);
	void inicializar(string n, vector<string> *dicc, vec_iter inicio, vec_iter fin, pthread_mutex_t* c,pthread_mutex_t* di);
	void buscar();
	void buscarAlt();
	bool comparar(int k);
	virtual ~bot();
};
#include "bot.cpp"
#endif /* BOT_H_ */

