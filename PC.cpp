#include<iostream>
#include<thread>
#include<mutex>
#include <queue>

using namespace std;

#define NUM_HILOS 5

queue<char> buffer;
const char letras[26]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
mutex flag;

int cont = 0;
class Monitor {
	public:
	void producir(int productor){
		flag.lock();	
		int aleatorio;
		aleatorio = rand() % 26;
		char producido=letras[aleatorio];
		buffer.push(producido);
		cout<<"El productor "<<productor<<" Está produciendo: "<<producido<<endl;
		flag.unlock();		
	}

			
	void consumir(int consumidor){
    flag.lock();	
    int aleatorio;
		aleatorio = rand() % 26;
		char consumido=letras[aleatorio];
		buffer.pop();
		cout<<"El consumidor "<<consumidor<<"Está consumiendo: "<<consumido<<endl;
		flag.unlock();		
	}
};

class Productor {
	private:
		Monitor* monitor;
		thread hilo;
		int nombre;
		void run_thread(){			
			for (int i=1; true; i++) {
			    monitor->producir(nombre);		
		}
      }
			
	public:
		Productor(Monitor* _monitor, int _nombre){
			nombre = _nombre;
			monitor = _monitor;
			hilo = thread(&Productor::run_thread, this);
		}
		void join_thread(){
			hilo.join();	
		}
		
};

class Consumidor {
	private:
		Monitor* monitor;
		thread hilo;
		int nombre;
		void run_thread(){			
			for (int i=1; true; i++) {
			    monitor->consumir(nombre);		
			}
		}
			
	public:
		Consumidor(Monitor* _monitor, int _nombre){
			nombre = _nombre;
			monitor = _monitor;
			hilo = thread(&Consumidor::run_thread, this);
		}
		void join_thread(){
			hilo.join();	
		}
		
};


int main() {

	Productor* productor[NUM_HILOS];
	Consumidor* consumidor[NUM_HILOS];
	Monitor* monitor;
	
	for(int i=0; i<NUM_HILOS; i++) {
		productor[i] = new Productor(monitor, i);
		consumidor[i] = new Consumidor(monitor, i);
	}
	
	for(int i=0; i<NUM_HILOS; i++) {
		productor[i]->join_thread();	//	START
	    consumidor[i]->join_thread();	//	START
	}

	return 0;
}