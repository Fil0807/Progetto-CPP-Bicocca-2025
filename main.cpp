/**
	@file main.cpp
	@brief Test implementazione della classe Queue templata
*/
#include <iostream>
#include <string>
#include <cassert>
#include "Queue.hpp"

using namespace std;


/**
	@brief Predicato per verificare se un valore è dispari

	Ritorna true se il valore passato è dispari
*/
struct isOdd {
	bool operator()(int a) const{
		return a%2 != 0;
	}
};


/**
	@brief Funtore che raddoppia un valore intero

	Ritorna il valore passato ma raddoppiato
*/
struct times2 {
	int operator()(int x) const {
		return x * 2;
	}
};


/**
	@brief Predicato che controlla due stringhe

	Ritorna true se la stringa passata corrisponde alla stringa locale 'name'
*/
struct equalToString{
	bool operator()(string s) const {
		string name = "spiaggia";
		return s == name;
	}
};


/**
	@brief Funtore che modifica una stringa

	Ritorna la stringa ricevuta ma modificata
*/
struct stringTo {
	string operator()(string s) const {
		return s = "montagna";
	}
};


/**
	@brief Struttura dati che rappresenta un veicolo
*/
struct Veicolo {
	string marca;  //!<Rappresenta la marca del veicolo
	int cv;  //!<Rappresenta i cavalli del motore del veicolo

	Veicolo() {
		marca = "";
		cv = 0;
	}

	Veicolo(string s, int c) {
		marca = s;
		cv = c;
	}

	bool operator==(const Veicolo& other) const{
		return (marca == other.marca && cv == other.cv);
	}

	friend ostream& operator<<(ostream& os, const Veicolo& v) {
		os << v.marca << " : " << v.cv;
		return os;
	}
};


/**
	@brief Funtore che modifica un veicolo

	Ritorna il veicolo con una modifica ai cv
*/
struct increasePower {
    Veicolo operator()(Veicolo v) const {
        v.cv += 50;
        return v;
    }
};


/**
	@brief Predicato controlla un veicolo 

	Ritorna true se i cv del veicolo ricevuto corrispondono a quelli cercati
*/
struct checkCV {
	bool operator()(Veicolo v) const {
		return v.cv == 250;
	}
};


/**
	@brief Test di una coda castata a <int>

	Insieme di comandi per verificare il corretto funzionamento
	della classe Queue quando castata a <int>
*/
void testInteri() {
	cout << "\n\n\n--- Test Coda<int> ---\nCreo la coda" << endl;
	Queue<int> q;
	assert(q.isEmpty());

	cout << "La coda e' vuota? " << (q.isEmpty() ? "si" : "no") << "\n" << endl;
	cout << "Aggiungo i valori da 1 a 5" << endl;
	q.enqueue(1);
	q.enqueue(2);
	q.enqueue(3);
	q.enqueue(4);
	q.enqueue(5);

	q.printQueue();

	assert(!q.isEmpty());
	assert(q.getSize() == 5);
	assert(q.frontElement() == 1);
	assert(q.backElement() == 5);

	cout << "\nRimouvo i primi 3 elementi" << endl;
	try {
        q.dequeue();
        q.dequeue();
        q.dequeue();
    } catch (const exception& e) {
        cout << "Errore: " << e.what() << endl;
    }
    q.printQueue();

    assert(q.getSize() == 2);
    assert(q.frontElement() == 4);
    assert(q.backElement() == 5);

	cout << endl;
	cout << "Aggiungo il valore 6" << endl;
	q.enqueue(6);
	cout << "Aggiungo il valore 7" << endl;
	q.enqueue(7);
	cout << "Aggiungo il valore 8" << endl;
	q.enqueue(8);

	q.printQueue();
	cout << "\nConverto i valori dispari in pari raddoppiandoli" << endl;
	transformif(q, isOdd(), times2());
	q.printQueue();

	try {
		cout << "\nStampo i valori front e back" << endl;
		cout << "\nFront: " << q.frontElement() << "\nBack: " << q.backElement() << endl;
    } catch (const exception& e) {
        cout << "Errore: " << e.what() << endl;
    }

    try {
		cout << "\nModifico i valori front e back" << endl;
		cout << "Front = 50" << endl;
		q.frontElement() = 50;
		cout << "Back = 100" << endl;
		q.backElement() = 100;
    } catch (const exception& e) {
        cout << "Errore: " << e.what() << endl;
    }

	q.printQueue();

	cout << "\nQuanti elementi ha la coda? " << q.getSize() << endl;

	cout << "\nLa coda e' vuota? " << (q.isEmpty() ? "si" : "no") << "\n" << endl;
	cout << "La coda contiene 8? " << (q.contains(8) ? "si" : "no") << "\n" << endl;
	cout << "La coda contiene 50? " << (q.contains(50) ? "si" : "no") << "\n" << endl;

	assert(!q.isEmpty());
	assert(q.getSize() == 5);
	assert(q.frontElement() == 50);
	assert(q.backElement() == 100);
}


/**
	@brief Test di una coda castata a <string>

	Insieme di comandi per verificare il corretto funzionamento
	della classe Queue quando castata a <string>
*/
void testStringhe() {
	cout << "\n\n\n--- Test Coda<string> ---\nCreo la coda" << endl;
	Queue<string> q1;

	cout << "La coda e' vuota? " << (q1.isEmpty() ? "si" : "no") << "\n" << endl;
	cout << "Aggiungo il valore 'oggi'" << endl;
	q1.enqueue("oggi");
	cout << "Aggiungo il valore 'sono'" << endl;
	q1.enqueue("sono");
	cout << "Aggiungo il valore 'andato'" << endl;
	q1.enqueue("andato");
	cout << "Aggiungo il valore 'in'" << endl;
	q1.enqueue("in");
	cout << "Aggiungo il valore 'spiaggia'" << endl;
	q1.enqueue("spiaggia");

	q1.printQueue();

	assert(!q1.isEmpty());
	assert(q1.getSize() == 5);
	assert(q1.frontElement() == "oggi");
	assert(q1.backElement() == "spiaggia");

	cout << "\nRimouvo tutti gli elementi" << endl;

	try {
        q1.dequeue();
		q1.dequeue();
		q1.dequeue();
		q1.dequeue();
		q1.dequeue();
    } catch (const exception& e) {
        cout << "Errore: " << e.what() << endl;
    }


	q1.printQueue();
	cout << "La coda e' vuota? " << (q1.isEmpty() ? "si" : "no") << "\n" << endl;


	cout << "Aggiungo il valore 'oggi'" << endl;
	q1.enqueue("oggi");
	cout << "Aggiungo il valore 'sono'" << endl;
	q1.enqueue("sono");
	cout << "Aggiungo il valore 'andato'" << endl;
	q1.enqueue("andato");
	cout << "Aggiungo il valore 'in'" << endl;
	q1.enqueue("in");
	cout << "Aggiungo il valore 'spiaggia'" << endl;
	q1.enqueue("spiaggia");

	q1.printQueue();


	cout << "\nConverto 'spiaggia' in 'montagna'" << endl;
	transformif(q1, equalToString(), stringTo());
	q1.printQueue();
	
	try {
		cout << "\nStampo i valori front e back" << endl;
		cout << "Front: " << q1.frontElement() << "\nBack: " << q1.backElement() << endl;
    } catch (const exception& e) {
        cout << "Errore: " << e.what() << endl;
    }

    try {
    	cout << "\nModifico i valori front e back" << endl;
		cout << "Front = 'io'" << endl;
		q1.frontElement() = "io";
		cout << "Back = 'spiaggia'" << endl;
		q1.backElement() = "spiaggia";
    } catch (const exception& e) {
        cout << "Errore: " << e.what() << endl;
    }

	q1.printQueue();

	cout << "\nQuanti elementi ha la coda? " << q1.getSize() << endl;

	cout << "\nLa coda e' vuota? " << (q1.isEmpty() ? "si" : "no") << "\n" << endl;
	cout << "La coda contiene 'andato'? " << (q1.contains("andato") ? "si" : "no") << "\n" << endl;
	cout << "La coda contiene 'scuola'? " << (q1.contains("scuola") ? "si" : "no") << "\n" << endl;

	assert(!q1.isEmpty());
	assert(q1.getSize() == 5);
	assert(q1.frontElement() == "io");
	assert(!(q1.backElement() == "montagna"));
}


/**
	@brief Test di una coda castata a <Veicolo>

	Insieme di comandi per verificare il corretto funzionamento
	della classe Queue quando castata ad un tipo custom <Veicolo>
*/
void testStructVeicolo() {
    cout << "\n\n\n--- Test Coda<Veicolo> ---\nCreo la coda q" << endl;
    Queue<Veicolo> q;

    cout << "La coda e' vuota? " << (q.isEmpty() ? "si" : "no") << "\n" << endl;
    
    Veicolo v1("Ford", 75);
    Veicolo v2("Fiat", 50);
    Veicolo v3("Volkswagen", 50);
    Veicolo v4("Maserati", 250);
    Veicolo v5("Lotus", 400);

    cout << "Aggiungo 5 veicoli alla coda" << endl;
    q.enqueue(v1);
    q.enqueue(v2);
    q.enqueue(v3);
    q.enqueue(v4);
    q.enqueue(v5);

    q.printQueue();

    assert(!q.isEmpty());
    assert(q.getSize() == 5);
    assert(q.frontElement() == v1);
    assert(q.backElement() == v5);

    cout << "\nRimuovo due veicoli dalla coda" << endl;
    try {
        q.dequeue();
        q.dequeue();
    } catch (const exception& e) {
        cout << "Errore: " << e.what() << endl;
    }
    q.printQueue();
    
    assert(q.getSize() == 3);
    assert(q.frontElement() == v3);
    assert(q.backElement() == v5);

    cout << "\nAggiungo un nuovo veicolo ('Ferrari': 700)" << endl;
    Veicolo v6("Ferrari", 700);
    q.enqueue(v6);
    q.printQueue();

    cout << "\nLa coda contiene 'Maserati: 250'? " << (q.contains(v4) ? "si" : "no") << "\n";
    cout << "La coda contiene 'Ford: 75'? " << (q.contains(v1) ? "si" : "no") << "\n";
    
    assert(q.contains(v4));
    assert(!q.contains(v1));

    try {
    	cout << "\nStampo i valori front e back" << endl;
    	cout << "Front: " << q.frontElement() << "\nBack: " << q.backElement() << endl;
    } catch (const exception& e) {
        cout << "Errore: " << e.what() << endl;
    }

    try {
    	cout << "\nModifico il valore di front a ('Lamborghini': 800)" << endl;
    	q.frontElement() = Veicolo("Lamborghini", 800);
    	cout << "Back = ('Porsche': 500)" << endl;
    	q.backElement() = Veicolo("Porsche", 500);
    } catch (const exception& e) {
        cout << "Errore: " << e.what() << endl;
    }

    q.printQueue();
    
    cout << "\nAumento la potenza di tutti i veicoli con 250 CV di 50 CV" << endl;
    transformif(q, checkCV(), increasePower());
    q.printQueue();

    cout << "\nQuanti elementi ha la coda? " << q.getSize() << endl;
    cout << "La coda e' vuota? " << (q.isEmpty() ? "si" : "no") << "\n" << endl;
    
    assert(!q.isEmpty());
    assert(q.getSize() == 4);

    cout << "\nSvuoto completamente la coda\n" << endl;
    try {
        while (!q.isEmpty()) {
            q.dequeue();
        }

        q.printQueue();
        cout << "Provo a rimuovere un elemento quando la coda e' vuota" << endl;
        q.dequeue(); // Questo dovrebbe generare un'eccezione
    } catch (const exception& e) {
        cout << "Errore: " << e.what() << endl;
    }
    cout << "\nLa coda e' vuota? " << (q.isEmpty() ? "si" : "no") << "\n" << endl;
    assert(q.isEmpty());
}


/**
	@brief Test sulla costruzione di una coda

	Insieme di comandi per verificare il corretto funzionamento
	dei metodi usati per la costruzione della coda
*/
void testCostruttori() {
	cout << "\n\n\n--- Test Costruttori<int> ---\nCreo la coda q" << endl;
	Queue<int> q;

	cout << "Aggiungo i valori 1, 2, 3, 4, 5" << endl;
	q.enqueue(1);
	q.enqueue(2);
	q.enqueue(3);
	q.enqueue(4);
	q.enqueue(5);

	q.printQueue();

	cout << "\n\nCreo la coda q1 usando il copy constructor" << endl;
	cout << "Queue<int> q1(q);" << endl;
	Queue<int> q1(q);

	q1.printQueue();
	cout << "\n\nCreo la coda q2 usando e usando l'operator = copio i valori da q" << endl;
	cout << "Queue<int> q2 = q;" << endl;
	Queue<int> q2 = q;

	q2.printQueue();

	cout << "\n\nCreo la coda q3 usando e usando gli iteratori per copiare da q" << endl;

	cout << "q3.enqueue(begin, end)" << endl;
	Queue<int>::const_iterator begin = q.begin();
	Queue<int>::const_iterator end = q.end();
	Queue<int> q3;
	q3.enqueue(begin, end);
	q3.printQueue();


	cout << "\n\nCreo la coda q4\nUso gli iteratori per copiare la seconda meta' di q" << endl;
	cout << "\nAggiungo altri 5 elementi a q" << endl;
	q.enqueue(6);
	q.enqueue(7);
	q.enqueue(8);
	q.enqueue(9);
	q.enqueue(10);

	cout << "Incremento L'iteratore begin di 5" << endl;
	++begin;
	++begin;
	++begin;
	++begin;
	++begin;

	cout << "q4.enqueue(begin, end)" << endl;
	Queue<int> q4;
	q4.enqueue(begin, end);
	q4.printQueue();
}


/**
	@brief Test funzionamento Iteratori

	Insieme di comandi per verificare il corretto funzionamento
	degli Iteratori della classe Queue
*/
void testIteratori() {
	cout << "\n\n\n--- Test Iteratori ---\nCreo la coda" << endl;
	Queue<int> q;

	cout << "Aggiungo il valore 1" << endl;
	q.enqueue(1);
	cout << "Aggiungo il valore 2" << endl;
	q.enqueue(2);
	cout << "Aggiungo il valore 3" << endl;
	q.enqueue(3);
	cout << "Aggiungo il valore 4" << endl;
	q.enqueue(4);
	cout << "Aggiungo il valore 5" << endl;
	q.enqueue(5);


	cout << "\nCreo l'teratore const_iterator it = q.begin()" << endl;
    Queue<int>::const_iterator it = q.begin();

    assert(*it == 1);
	cout << *it << " ";
	++it;
	assert(*it == 2);
	cout << *it << " ";
	++it;
	assert(*it == 3);
	cout << *it << " ";
	++it;
	assert(*it == 4);
	cout << *it << " ";
	++it;
	assert(*it == 5);
	cout << *it << " " << endl;
	cout << "L'iteratore scorre correttamente la coda" << endl;

	cout << "\n\nCreo l'teratore const_iterator it1 = q.begin()" << endl;
	Queue<int>::const_iterator it1 = q.begin();

	cout << "Creo l'teratore const_iterator it2 = q.begin()" << endl;
	Queue<int>::const_iterator it2 = q.begin();

	assert(*it1 == *it2);
	cout << "\nVerifico che *it1 == *it2\nIncremento it1" << endl;
	++it1;
	assert(*it1 != *it2);
	cout << "Verifico che *it1 != *it2" << endl;
}

int main() {
	testInteri();

	testStringhe();

	testStructVeicolo();

	testCostruttori();

	testIteratori();

	return 0;
}