/*
 * bot.cpp
 *
 *  Created on: 06/09/2012
 *      Author: rafa
 */


#include <sstream>

bot::bot(){

}

void bot::inicializar(string n, vector<string> *dicc, vector<string> *inten, pthread_mutex_t* c,pthread_mutex_t* di){
	this->Nombre=n;
	this->dicc=dicc;
	this->intentos=inten;
	this->consola=c;
	this->consola=di;
}
void bot::inicializar(string n, vector<string> *dicc, vec_iter inicio, vec_iter fin, pthread_mutex_t* c,pthread_mutex_t* di){
	this->Nombre=n;
	this->dicc=dicc;
	this->inicio=inicio;
	this->fin=fin;

	this->consola=c;
	this->consola=di;

}
bot::bot(string n, vector<string> *dicc,  vector<string> *inten, pthread_mutex_t* c,pthread_mutex_t* di) {
	this->inicializar(n,dicc,inten,c,di);
}
bot::bot(string n, vector<string> *dicc, vec_iter inicio, vec_iter fin, pthread_mutex_t* c,pthread_mutex_t* di) {
	this->inicializar(n,dicc,inicio,fin,c,di);
}
void bot::buscarAlt(){
	std::stringstream sstm;

	for(std::vector<string>::iterator intento = this->intentos->begin(); intento != this->intentos->end(); ++intento){

		for(std::vector<string>::iterator palabra = this->dicc->begin(); palabra != this->dicc->end(); ++palabra){

			//this->enviarMsj(*intento+":"+*palabra);
			if(*intento == *palabra)
			{
				//std::cout<<this->Nombre<<":Anagrama: "<<this->intentos->at(k)<<std::endl;

				sstm <<this->Nombre<<": Anagrama-> "<<*intento<<"\n";
				this->enviarMsj(sstm.str());
				//this->enviarMsj("consiguio");
				sstm.str("");
			}

		}

	}

	//this->enviarMsj(this->Nombre + ": Finalize");

}
void bot::buscar(){
	std::stringstream sstm;
	//this->enviarMsj(*this->inicio+":");
	for (vec_iter intento = this->inicio; intento != (this->fin - 1); ++intento){

		for(std::vector<string>::iterator palabra = this->dicc->begin(); palabra != this->dicc->end(); ++palabra){

			//this->enviarMsj(*intento+":"+*palabra);
			if(*intento == *palabra)
			{
				//std::cout<<this->Nombre<<":Anagrama: "<<this->intentos->at(k)<<std::endl;

				sstm <<this->Nombre<<": Anagrama-> "<<*intento<<"\n";
				this->enviarMsj(sstm.str());
				//this->enviarMsj("consiguio");
				sstm.str("");
			}

		}

	}

	this->enviarMsj(this->Nombre + ": Finalize");

}

bool bot::comparar(int k)
{
	bool r;
	pthread_mutex_lock(this->diccIntentos);
	if(this->intentos->at(k)==this->dicc->at(k)){
		r=true;
		pthread_mutex_unlock(this->diccIntentos);
		return r;
	}
	else{
		r= false;
		pthread_mutex_unlock(this->diccIntentos);
		return r;
	}
}
void bot::enviarMsj(string msj){
	pthread_mutex_lock(this->consola);
	std::cout<<msj<<std::endl;
	pthread_mutex_unlock(this->consola);
}
bot::~bot() {
	// TODO Auto-generated destructor stub
}

