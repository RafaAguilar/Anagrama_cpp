/*
 * master.cpp
 *
 *  Created on: 06/09/2012
 *      Author: rafa
 */


#include "bot.h"



typedef std::vector<string>::iterator vec_iter;

master::master(string b) {

	this->K=4; //Cantidad de cpu's/Bots
	this->base=b;
	this->consola= new pthread_mutex_t();
	//TODO : Inicializar bien el mutex
	//*this->consola = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_unlock(this->consola);
	this->diccIntentos= new pthread_mutex_t();
	pthread_mutex_unlock(this->diccIntentos);
	//this->dicc=new vector<string>();
	//this->procesarDicc(this->dicc);

	//char * conjunto[] =  base.c_str();
	//std::cout<<this->base<<"\n";

	char conjunto[]= "teologia";
	//char conjunto[]= "roma";
	size_t card =strlen(base.c_str());
	//std::cout<<*conjunto<<"\n";
	this->intentos=new vector<string>;
	this->permutaciones(conjunto,card,0,this->intentos);

	//std::cout<<"intentos"<<"\n";
	/*for(std::vector<string>::iterator it = this->intentos->begin(); it != this->intentos->end(); ++it)
	{
		std::cout<<*it<<"\n";
	}*/		//this->permutaciones(this->base.)
	//std::cout<<"termina\n";
	//TODO : Falta probar si se crea el diccionario

	this->dicc=new vector<string>;
	this->procesarDicc(this->dicc);
	//std::cout<<"diccionario"<<"\n";
	/*for(std::vector<string>::iterator it = this->dicc->begin(); it != this->dicc->end(); ++it)
	{
		std::cout<<*it<<"\n";
	};*/
}
void master::procesarDicc(vector<string>* d){
	//ifstream in("alternativo"); // Abriendo modo lectura
	ifstream in("diccionario_venezuela"); // Abriendo modo lectura
	string palabra;
	while(getline(in, palabra)) // Discards newline char
		d->push_back(palabra);

}
void master::permutaciones(char conjunto[], size_t card, size_t elem, vector<string> *v)
{

   if (card > 1){


      permutaciones(conjunto, card - 1, elem + 1,v);

      for (int i= 1; i < card; i++){
         char temp;

         temp = conjunto[elem + i];
         memmove(conjunto + elem + 1, conjunto + elem, i);
         conjunto[elem] = temp;

         permutaciones(conjunto, card - 1, elem + 1,v);

         memmove(conjunto + elem, conjunto + elem + 1, i);
         conjunto[elem + i] = temp;
      }
   }else
   {
	   //puts(conjunto);
   	   v->push_back(conjunto);
   }

}

vector<string>* sliceVector(vec_iter first, vec_iter last) {
	vector<string>* salida=new vector<string>;
    for (vec_iter cur = first; cur != last; ++cur) {
        salida->push_back(*cur);
    }
    salida->push_back(*last);
    /*
    std::cout<<"despedazando : "<<*first<<":"<<*last<<"\n";
    vec_iter inicio= salida->begin();
    vec_iter fin= salida->begin()+(salida->size()-1);
    std::cout<<"despedazando : "<<*inicio<<":"<<*fin<<"\n";
    */
    return salida;
}
void print( bot b )
	   {
			//b.buscarAlt();
			b.buscar();
	   };
void master::inicio(){
	boost::timer::auto_cpu_timer t;
	//TODO : probar todo!
	//TODO : threads http://www.yolinux.com/TUTORIALS/LinuxTutorialPosixThreads.html
	//TODO : medir tiempo de calculo
	//std::cout<<"inicia\n";
	clock_t t_ini, t_fin;
	double secs;
	t_ini = clock();
	boost::thread_group Gt;
	//int fin = this->K-1;
	vector<bot> b(4);
	std::stringstream nombre;
	int iret=0;
	char *message1 = "Thread";
	pthread_t thread[this->K];
	int inicio,fin;
	vec_iter vInicio,vFin;
	for (int i=0; i<this->K;i++)
	{
		nombre<<"bot"<<i;
		inicio=(i*(this->intentos->size()/(this->K)));
		fin=(((i+1)*(this->intentos->size()/(this->K))))-1;
		//std::cout<<"inicio : "<<inicio<<" - "<<"fin : "<<fin<<"\n";
		vInicio=(this->intentos->begin()+inicio);
		vFin = (this->intentos->begin()+fin);
		//std::cout<<*vInicio<<":"<<*vFin<<"\n";
		//b[i].inicializar(nombre.str(),this->dicc,sliceVector((this->intentos->begin()+inicio),(this->intentos->begin()+fin)),this->consola,this->diccIntentos);

		b[i].inicializar(nombre.str(),this->dicc,(this->intentos->begin()+inicio),(this->intentos->begin()+fin),this->consola,this->diccIntentos);

		//iret= pthread_create(&thread[i],NULL,b[i].buscarAlt,(void*) message1);
		//Gt.create_thread(b[i].buscarAlt());
		Gt.create_thread(boost::bind(print,b[i]));
		//pthread_join( thread[i], NULL);
		nombre.str("");
	}
	Gt.join_all();

	t_fin = clock();
	secs = (double)(t_fin - t_ini) / CLOCKS_PER_SEC;
	printf("%.16g segundos\n", secs);

}


//int main(void)
//{
//   char conjunto[] = "abc";
//   size_t card = sizeof conjunto - 1;
//
//   permutaciones(conjunto, card, 0);
//
//   return EXIT_SUCCESS;
//}
master::~master() {
	// TODO Auto-generated destructor stub
	delete this->consola;
	delete this->dicc;
	delete this->intentos;
}

