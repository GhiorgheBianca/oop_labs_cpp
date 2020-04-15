#pragma once

#include "Domain.h"
//#include "LinkedList.h"
#include <string>
#include <ostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Repository {
private:
	unordered_map<int, Disciplina> discipline;
	vector<Contract> contracte;

	/*
		Metoda privata, verifica daca exista deja disciplina in repository
		Input: disciplina - obiect de tip Disciplina;
		Output: true daca disciplina a fost gasita sau false daca nu s-a gasit nimic;
	*/
	bool exist(const Disciplina& disciplina) const;

public:
	// default constructor
	Repository() = default;

	// nu permite copierea de obiecte
	Repository(const Repository& other) = delete;

	/*
		Adauga o disciplina in repository.
		Input: disciplina - obiect de tip Disciplina;
		Output: arunca o exceptie daca disciplina exista deja sau o adaugata in repository in caz contrar;
	*/
	void addDisciplina(const Disciplina& disciplina);

	/*
		Modifica o disciplina in repository.
		Input: disciplina - obiect de tip Disciplina;
		Output: arunca o exceptie daca disciplina nu exista sau o modifica in repository in caz contrar;
	*/
	void updateDisciplina(Disciplina disciplina);

	/*
		Sterge o disciplina din repository.
		Input: disciplina - obiect de tip Disciplina;
		Output: arunca o exceptie daca disciplina nu exista sau o sterge din repository in caz contrar;
	*/
	void deleteDisciplina(const Disciplina& disciplina);

	/*
		Gaseste disciplina dupa id.
		Input: id - int;
		Output: disciplina care a fost gasita sau o exceptie daca nu s-a gasit nimic;
	*/
	const Disciplina& findDisciplina(int id) const;

	/*
		Obtine toate disciplinele existente.
		Output: toate disciplinele din repository;
	*/
	unordered_map<int, Disciplina> getDiscipline() {
		return discipline;
	}

	/*
		Adauga un contract cu discipline in repository.
		Input: discipline - vector cu obiect de tip Disciplina;
		Output: adaugata contractul in repository;
	*/
	//void addContract(const vector<Disciplina>& discipline, int id);

	/*
		Obtine toate disciplinele dintr-un contract existent cu un anumit id.
		Input: id - int, codul unic al contractului;
		Output: toate disciplinele din contract;
	*/
	//vector<Disciplina> getContract(int id);
	/*
	void golesteDiscipline();

	void golesteContract(int id);

	void stergeContract(int id);

	void updateContrat(int id);

	void setDiscipline_dinContract(int id);

	size_t getContractPosition(int id) const noexcept;
	*/
};