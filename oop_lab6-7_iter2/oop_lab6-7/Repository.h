#pragma once

#include "Domain.h"
#include "LinkedList.h"
#include <string>
#include <ostream>

using std::string;
using std::ostream;

class Repository {
private:
	Lista<Disciplina> discipline;

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
		Gaseste pozitia pe care se afla disciplina dupa denumire si cadru didactic.
		Input: denumire, cadru_didactic - string;
		Output: pozitia pe care se afla disciplina care a fost gasita sau o exceptie daca nu s-a gasit nimic;
	*/
	int findPosition(const std::string& denumire, const std::string& cadru_didactic) const;

	/*
		Gaseste disciplina dupa denumire si cadru didactic.
		Input: denumire, cadru_didactic - string;
		Output: disciplina care a fost gasita sau o exceptie daca nu s-a gasit nimic;
	*/
	const Disciplina& findDisciplina(const std::string& denumire, const std::string& cadru_didactic) const;

	/*
		Obtine toate disciplinele existente.
		Output: toate disciplinele din repository;
	*/
	const Lista<Disciplina>& getDiscipline() {
		return discipline;
	}

};