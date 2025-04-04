/**
    @file Queue.hpp
    
    @brief File header della classe Queue

    Contiene definizioni e dichiarazioni relative alla classe Queue
*/
#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <iterator>
#include <cassert>
#include <stdexcept>

using namespace std;


/**
    @brief Classe coda FIFO

    Implementazione generica di una classe di tipo FIFO.
    L'ordinamento segue la logia first in first out
*/
template <typename T>
class Queue {
private:

    /**
        @brief Struttura Nodo

        Struttura dati sulla quale si basa la coda
    */
    struct Node {
        T value;  //!<Valore di tipo T
        Node* next;  //!<Puntatore di tipo T


        /**
            @brief Costruttore della struttura Node

            @param v valore da assegnare a value

            @post value == v
            @post next == nullptr 
        */
        Node(const T& v) : value(v), next(nullptr) {}
    };

    Node* front;  //!<Puntatore di tipo T al primo elemento della coda
    Node* back;  //!<Puntatore di tipo T all'ultimo elemento della coda

    size_t size;  //!<numero di elementi della coda


    /**
        @brief Funzione globale usata per modificare la coda
        
        Friend permette di accedere ai dati e metodi privati della classe

        @param q Reference alla coda da modificare
        @param p Predicato con cui valutare gli elementi della coda
        @param f Funtore da applicare agli elementi della coda
    */
    template <typename Q, typename P, typename F>
    friend void transformif(Queue<Q>& q, P p, F f);


    /**
        @brief Funzione usata per svuotale la coda

        Richiama ricorsivamente il metodo dequeue() fino a quando isEmpty() ritorna true
    */
    void clearQueue(){
        while (!isEmpty()) {
            dequeue();
        }
    }  

public:

    /**
        @brief Costruttore della classe Queue

        @post front == nullptr
        @post back == nullptr
        @post size == 0
    */
    Queue() : front(nullptr), back(nullptr), size(0) {}


    /**
        @brief Costruttore Copia della classe Queue

        @param other Reference ad un'altra coda da copiare
    */
    Queue(const Queue& other) : front(nullptr), back(nullptr), size(0) {
        Node* current = other.front;

        while (current != nullptr) {
            enqueue(current->value);
            current = current->next;
        }
    }


    /**
        @brief Operatore di assegnamento

        Permette di copiare una lista passata come parametro

        @param other Reference alla lista da copiare

        @return Reference alla coda assegnata
    */
    Queue& operator=(const Queue& other) {
        if (this != &other) {
            clearQueue();
            Node* current = other.front;

            while (current != nullptr) {
                enqueue(current->value);
                current = current->next;
            }

            return *this;
        }
    }


    /**
        @brief Distruttore della classe Queue
    */
    ~Queue(){
        clearQueue();
    }


    /**
        @brief Funzione per aggiungere un elemento alla coda

        Prende in input un valore, crea un nuovo nodo e lo aggiunge in coda

        @param value Valore da inserire nella coda

        @post size == size+1
    */
    void enqueue(const T& value) {
        Node* newNode = new Node(value);

        if (isEmpty()) {
            front = back = newNode;
        } else {
            back->next = newNode;
            back = newNode;
        }

        //delete newNode;
        ++size;
    }


    /**
        @brief Funzione per aggiungere elementi alla coda  

        Riceve due iteratori per navigare la lista da copiare

        @param begin iteratore di inizio
        @param end iteratore di fine
    */
    template <typename const_iterator>
    void enqueue(const_iterator begin, const_iterator end) {
        for (const_iterator it = begin; it != end; ++it) {
            enqueue(*it);
        }
    }


    /**
        @brief Funzione di rimozione

        Funzione che permette di rimuovere il primo elemento della coda

        @post size == size-1
    */
    void dequeue() {
        if (isEmpty()){
            throw out_of_range("La coda e' vuota");
        }

        Node* temp = front;
        front = front->next;
        delete temp;
        --size;

        if (front == nullptr)
            back = nullptr;
    }


    /**
       @brief Funzione per accedere al primo elemento della coda(scrittura e lettura)
    */
    T& frontElement() {
        if(isEmpty())
            throw out_of_range("Errore, Coda vuota!");
        return front->value;
    }


    /**
       @brief Funzione per accedere al primo elemento della coda(solo lettura)
    */
    const T& frontElement() const {
        if(isEmpty())
            throw out_of_range("Errore, Coda vuota!");
        return front->value;
    }


    /**
       @brief Funzione per accedere all'ultimo elemento della coda(scrittura e lettura)
    */
    T& backElement() {
        if(isEmpty())
            throw out_of_range("Errore, Coda vuota!");
        return back->value;
    }


    /**
       @brief Funzione per accedere all'ultimo elemento della coda(solo lettura)
    */
    const T& backElement() const {
        if(isEmpty())
            throw out_of_range("Errore, Coda vuota!");
        return back->value;
    }


    /**
       @brief Funzione per verificare se la coda contiene un elemento specifico

       @param value valore da controllare se presente

       @return true se la coda contiene value
    */
    bool contains(const T& value) const {
        if(isEmpty()) {
            cout << "La coda e' vuota!" << endl;
        } else {
            for (const_iterator it = begin(); it != end(); ++it) {
                if(*it == value)
                    return true;
            }
        }

        return false;
    }

    size_t getSize() const {
        return size;
    }


    /**
       @brief Funzione per verificare se la coda è vuota

       @return true se la coda è vuota
    */
    bool isEmpty() const {
        return front == nullptr;
    }


    /**
       @brief Funzione per stampare la coda

       Funzione che permette di stampare la coda, segue l'ordinamente 
       con cui i valori sono stati inseriti

    */
    void printQueue() const {
        if (isEmpty()) {
            cout << "La coda e' vuota" << endl;
        }
        else {
            cout << "\nLa coda contiene: ";
            for(const_iterator it = begin(); it != end(); ++it){
                cout << "["<< *it << "] ";
            }
            cout << endl;
        }
    }


    /**
        @brief Classe const_iterator

        Implementazione degli iteratore per navigare la classe generica Queue
    */
    class const_iterator {
    private:
        friend class Queue;
        Node* ptr;

    public:
        typedef std::forward_iterator_tag iterator_category;
        typedef T                         value_type;
        typedef ptrdiff_t                 difference_type;
        typedef const T*                  pointer;
        typedef const T&                  reference;

        const_iterator(Node* n) {
            ptr = n;
        }

        const_iterator(const const_iterator &other) {
            ptr = other.ptr;
        }

        const_iterator& operator=(const const_iterator &other) {
            if(this != &other) {
                ptr = other.ptr;
            }
            return *this;
        }

        ~const_iterator() {
            ptr = nullptr;
        }

        const T& operator*() const {
            return ptr->value;
        }


        const T* operator->() const {
            return &(ptr->value);
        }

        const_iterator operator++(int) {
            const_iterator it(*this);
            ++*this;
            return it;
        }

        const_iterator& operator++() {
            ptr = ptr->next;
            return *this;
        }

        bool operator==(const const_iterator& other) const {
            return ptr == other.ptr;
        }

        bool operator!=(const const_iterator& other) const {
            return ptr != other.ptr;
        }
    };


    /**
       @brief Funzione per assegnare ad un iteratore il primo elemento di una coda
    */
    const_iterator begin() const {
        return const_iterator(front);
    }


    /**
       @brief Funzione per assegnare ad un iteratore l'ultimo elemento di una coda
    */
    const_iterator end() const {
        return const_iterator(nullptr);
    }
};


/**
    @brief Funzione globale per modificare gli elementi della coda

    Funzione che valuta ogni elemento di una coda tramite un predicato p
    Se la valutazione ritorna true viene applicato il funtore f

    La funzione transformif() non altera l'ordinamento della coda, modifica solo i valori dei nodi

    @param q Reference alla coda da modificare
    @param p Predicato con cui valutare i nodi
    @param f Funtore usato per modificare i nodi
*/
template <typename Q, typename P, typename F>
void transformif(Queue<Q>& q, P p, F f) {
    typename Queue<Q>::Node* current = q.front;

    while (current != nullptr) {
        if (p(current->value)) {
            current->value = f(current->value);
        }
        current = current->next;
    }
}

#endif