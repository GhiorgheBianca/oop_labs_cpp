#pragma once
#include <string>
using namespace std;

// Structura Nodului: (valoarea nodului, legatura catre nodul urmator)
template <typename DataType>
struct Nod {
	// valoarea nodului (exp: Disciplina: "Fundamentele programarii", 6, "obligatorie", "Czibula Istvan")
	DataType valoare;
	// pointer catre urmatorul element
	Nod* urmator;
	// initializarea nodului fara un element urmator
	Nod(DataType val) noexcept :valoare{ val }, urmator{ nullptr } {};
	// initializarea nodului cu un element urmator
	Nod(DataType val, Nod* urm) noexcept :valoare{ val }, urmator{ urm } {};

};

template <typename DataType>
class ListaIterator;

template <typename DataType>
class Lista {
private:
	// pointer catre primul nod din lista
	Nod<DataType>* capat;

	/*
		Functia care elibereaza toate nodurile din lista.
	*/
	void elibereazaNoduri() noexcept;

	/*
		Functia care copiaza nodul curent.
		Input: curent - pointer catre nodul curent;
		Output: returneaza un pointer catre copia nodului curent daca exista, altfel returneaza nullptr;
	*/
	Nod<DataType>* copiaza(Nod<DataType>* curent);

public:
	/*
		Constructor. Functia care initializeaza lista.
	*/
	Lista() noexcept :capat{ nullptr } {};

	Lista(const Lista& other);

	/*
		Initializarea operatorului de egalitate (=). Astfel se realizeaza schimbarea listei curente cu alta lista.
		Input: other - referinta catre un obiect de tip Lista;
	*/
	void operator=(const Lista& other);

	/*
		Destructor. Functia care distruge lista.
	*/
	~Lista();

	/*
		Functia care obtine dimensiunea listei.
		Output: returneaza dimensiunea;
	*/
	size_t size() const noexcept;

	/*
		Functia care adauga la inceputul listei.
		Input: val - obiect de tipul DataType;
	*/
	void addInceput(DataType val);

	/*
		Functia care adauga la sfarsitul listei.
		Input: val - obiect de tipul DataType;
	*/
	void push_back(DataType val);

	/*
		Functia care actualizeaza o valoare din lista.
		Input: val - obiect de tipul DataType;
	*/
	void update(DataType val, int position);

	/*
		Functia care sterge o valoare din lista.
		Input: val - obiect de tipul DataType;
	*/
	void erase(int position) noexcept;

	/*
		Functia care returneaza valoarea primului element.
		Output: returneaza o referinta catre valoarea primului element din lista;
	*/
	DataType& first() const;

	/*
		Functia care returneaza lista iterator cu pointer catre primul nod din lista.
	*/
	ListaIterator<DataType> begin() const noexcept;

	/*
		Functia care returneaza lista iterator cu pointer catre ultimul nod din lista.
	*/
	ListaIterator<DataType> end() const noexcept;

	/*
		Initializarea operatorului [].
		Input: poz - obiect de tip size_t;
		Output: returneaza o referinta catre valoarea nodului de pe pozitia specificata;
	*/
	DataType& operator[](size_t poz) noexcept;

};

template <typename DataType>
Lista<DataType>::Lista(const Lista& other) {
	capat = copiaza(other.capat);

}

template <typename DataType>
void Lista<DataType>::operator=(const Lista& other) {
	elibereazaNoduri();

	capat = copiaza(other.capat);

}

template <typename DataType>
Lista<DataType>::~Lista() {
	elibereazaNoduri();

}

template <typename DataType>
Nod<DataType>* Lista<DataType>::copiaza(Nod<DataType>* curent) {
	if (curent == nullptr) {
		return nullptr;
	}
	auto nod = new Nod<DataType>{ curent->valoare };
	nod->urmator = copiaza(curent->urmator);
	return nod;

}

template <typename DataType>
void Lista<DataType>::addInceput(DataType val) {
	Nod<DataType>* nod = new Nod<DataType>{ val,capat };
	capat = nod;

}

template <typename DataType>
void Lista<DataType>::push_back(DataType val) {
	auto nodCurent = capat;
	while (nodCurent != nullptr && nodCurent->urmator != nullptr) {
		nodCurent = nodCurent->urmator;
	}

	if (nodCurent == nullptr) {
		capat = new Nod<DataType>{ val,nullptr }; // daca era o lista vida
	}
	else {
		nodCurent->urmator = new Nod<DataType>{ val,nullptr };
	}

}

template <typename DataType>
void Lista<DataType>::update(DataType val, int position) {
	auto nodCurent = capat;
	int contor = 0;
	while (contor != position) {
		nodCurent = nodCurent->urmator;
		contor++;
	}
	nodCurent->valoare = val;

}

template <typename DataType>
void Lista<DataType>::erase(int position) noexcept {
	auto nodCurent = capat;
	auto prev = capat;
	int contor = 0;

	if (contor != position) {
		nodCurent = nodCurent->urmator;
		contor++;
	}
	while (contor != position) {
		prev = prev->urmator;
		nodCurent = nodCurent->urmator;
		contor++;
	}

	if (contor == 0 && nodCurent->urmator == nullptr) {
		elibereazaNoduri(); // daca e primul si singurul element
	}
	else if (contor == 0) {
		auto aux = nodCurent->urmator; // daca e primul element
		delete nodCurent;
		capat = aux;
	}
	else if (nodCurent->urmator != nullptr) {
		auto aux = nodCurent->urmator; // daca e intre primul si ultimul
		delete nodCurent;
		prev->urmator = aux;
	}
	else {
		prev->urmator = nullptr; // daca e ultimul
		delete nodCurent;
	}

}

template <typename DataType>
size_t Lista<DataType>::size() const noexcept {
	auto nodCurent = capat;
	int length = 0;
	while (nodCurent != nullptr) {
		length++;
		nodCurent = nodCurent->urmator;
	}
	return length;

}

template <typename DataType>
DataType& Lista<DataType>::operator[](size_t position) noexcept {
	auto nodCurent = capat;
	size_t length = 0;
	while (length < position) {
		length++;
		nodCurent = nodCurent->urmator;
	}
	return nodCurent->valoare;

}

template <typename DataType>
DataType& Lista<DataType>::first() const {
	return capat->valoare;

}

template <typename DataType>
void Lista<DataType>::elibereazaNoduri() noexcept {
	auto nodCurent = capat;
	while (nodCurent != nullptr) {
		auto aux = nodCurent->urmator;
		delete nodCurent;
		nodCurent = aux;
	}
	capat = nullptr;

}

template <typename DataType>
class ListaIterator {
private:
	// pointer catre nodul curent din lista
	Nod<DataType>* curent;

public:
	/*
		Constructor. Functia care initializeaza lista iterator cu un pointer catre nodul curent.
	*/
	ListaIterator(Nod<DataType>* curent) noexcept :curent{ curent } {}

	/*
		Initializarea operatorului de inegalitate (!=).
		Input: other - referinta catre un obiect de tip ListaIterator;
		Output: returneaza true daca cele doua elemente nu sunt egale, altfel false;
	*/
	bool operator!=(const ListaIterator& other) noexcept;

	/*
		Initializarea operatorului care face posibila trecerea la urmatorul nod.
	*/
	void operator++() noexcept;

	/*
		Initializarea operatorului care face posibila obtinerea valorii nodului curent.
		Output: returneaza o referinta catre valoarea nodului curent;
	*/
	DataType& operator*() noexcept;

};

template <typename DataType>
ListaIterator<DataType> Lista<DataType>::begin() const noexcept {
	return ListaIterator<DataType>{ capat };

}

template <typename DataType>
ListaIterator<DataType> Lista<DataType>::end() const noexcept {
	return ListaIterator<DataType>{ nullptr };

}

template <typename DataType>
bool ListaIterator<DataType>::operator!=(const ListaIterator& other) noexcept {
	return curent != other.curent;

}

template <typename DataType>
void ListaIterator<DataType>::operator++() noexcept {
	curent = curent->urmator;

}

template <typename DataType>
DataType& ListaIterator<DataType>::operator*() noexcept {
	return curent->valoare;

}