#pragma once

#include "Domain.h"
#include "Exceptions.h"
//#include "LinkedList.h"
#include <string>
#include <ostream>
#include <vector>

using std::vector;
using std::string;
using std::ostream;

class VirtualRepository {
public:
	virtual void addDisciplina(const Disciplina& disciplina) = 0;
	virtual void updateDisciplina(Disciplina disciplina) = 0;
	virtual void deleteDisciplina(const Disciplina& disciplina) = 0;
	virtual const vector<Disciplina>& getDiscipline() = 0;
	virtual int findPosition(int id, const vector<Disciplina>& discipline) const = 0;
	virtual void save_toHTML(string myFile, Contract contractul) = 0;
	virtual void deleteDisciplina_fromContract(const Disciplina& disciplina, Contract& contract) = 0;

	virtual ~VirtualRepository() = default;
};

class Repository : public VirtualRepository {
protected:
	vector<Disciplina> discipline;
	double error_probability;

	/*
		Metoda privata, verifica daca exista deja disciplina in repository
		Input: disciplina - obiect de tip Disciplina;
		Output: true daca disciplina a fost gasita sau false daca nu s-a gasit nimic;
	*/
	bool exist(const Disciplina& disciplina, const vector<Disciplina>& discipline) const;

public:
	// default constructor
	Repository() noexcept :error_probability{ 0 } {}
	//Repository() = default;

	// constructor with parameters
	Repository(const double error_probability) noexcept :error_probability{ error_probability } {}

	// nu permite copierea de obiecte
	Repository(const Repository& other) = delete;

	// destructor
	virtual ~Repository() = default;

	/*
		Adauga o disciplina in repository.
		Input: disciplina - obiect de tip Disciplina;
		Output: arunca o exceptie daca disciplina exista deja sau o adaugata in repository in caz contrar;
	*/
	virtual void addDisciplina(const Disciplina& disciplina);

	/*
		Modifica o disciplina in repository.
		Input: disciplina - obiect de tip Disciplina;
		Output: arunca o exceptie daca disciplina nu exista sau o modifica in repository in caz contrar;
	*/
	virtual void updateDisciplina(Disciplina disciplina);

	/*
		Sterge o disciplina din repository.
		Input: disciplina - obiect de tip Disciplina;
		Output: arunca o exceptie daca disciplina nu exista sau o sterge din repository in caz contrar;
	*/
	virtual void deleteDisciplina(const Disciplina& disciplina);

	/*
		Gaseste pozitia pe care se afla disciplina dupa id.
		Input: id - int;
		Output: pozitia pe care se afla disciplina care a fost gasita sau o exceptie daca nu s-a gasit nimic;
	*/
	int findPosition(int id, const vector<Disciplina>& discipline) const;

	/*
		Obtine toate disciplinele existente.
		Output: toate disciplinele din repository;
	*/
	const vector<Disciplina>& getDiscipline() noexcept {
		return discipline;
	}
	
	/*
		Sterge o disciplina din contract.
		Input: disciplina - obiect de tip Disciplina, contract - obiect de tip Contract;
		Output: arunca o exceptie daca disciplina nu exista sau o sterge din contract in caz contrar;
	*/
	void deleteDisciplina_fromContract(const Disciplina& disciplina, Contract& contract);

	/*
		Salveaza disciplinele din contract intr-un fisier HTML al carui nume este specificat de utilizator.
		Input: myFile - string;
		Output: scrie in fisier vectorul de discipline din contract;
	*/
	void save_toHTML(string myFile, Contract contractul);

};


class RepoFile : public Repository {
private:
	string fileName;
	void loadFromFile();
	void writeToFile(const vector<Disciplina>& disciplinele);
	double error_probability;

public:
	/*
		Functia care incarca disciplinele din fisier.
	*/
	RepoFile(string fileName, const double error_probability) :Repository(), fileName{ fileName }, error_probability{ error_probability } {
		loadFromFile();
	}

	/*
		Functia care scrie disciplinele in fisier.
	*/
	RepoFile(string fileName, Contract contract) :fileName{ fileName } {
		writeToFile(contract.getDiscipline_dinContract());
	}

	/*
		Functia care sterge tot continutul fisierului.
	*/
	void deleteFileContent();

	/*
		Adauga o disciplina in repository.
		Input: disciplina - obiect de tip Disciplina;
		Output: arunca o exceptie daca disciplina exista deja sau o adaugata in repository in caz contrar;
	*/
	void addDisciplina(const Disciplina& disciplina) override {
		Repository::addDisciplina(disciplina);
		writeToFile(getDiscipline());
	}

	/*
		Sterge o disciplina din repository.
		Input: disciplina - obiect de tip Disciplina;
		Output: arunca o exceptie daca disciplina nu exista sau o sterge din repository in caz contrar;
	*/
	void deleteDisciplina(const Disciplina& disciplina) override {
		Repository::deleteDisciplina(disciplina);
		writeToFile(getDiscipline());
	}

	/*
		Modifica o disciplina in repository.
		Input: disciplina - obiect de tip Disciplina;
		Output: arunca o exceptie daca disciplina nu exista sau o modifica in repository in caz contrar;
	*/
	void updateDisciplina(Disciplina disciplina) override {
		Repository::updateDisciplina(disciplina);
		writeToFile(getDiscipline());
	}

};