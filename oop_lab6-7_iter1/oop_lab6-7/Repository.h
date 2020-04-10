#pragma once

#include "Domain.h"
#include <vector>
#include <string>
#include <ostream>

using std::vector;
using std::string;
using std::ostream;

class Repository
{
private:
	vector<Disciplina> discipline;

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
		Sterge o disciplina din repository.
		Input: disciplina - obiect de tip Disciplina;
		Output: arunca o exceptie daca disciplina nu exista sau o sterge din repository in caz contrar;
	*/
	void deleteDisciplina(const Disciplina& disciplina);

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
	const vector<Disciplina>& getDiscipline() const noexcept{
		return discipline;
	}

};

/*
	Folosit pentru a semnala situatii exceptionale care pot aparea in repository
*/
class RepoException {
	string message;

public:
	RepoException(string m) :message{ m } {}
	// functie friend (vreau sa folosesc membrul privat message)
	friend ostream& operator<<(ostream& out, const RepoException& ex);
};

ostream& operator<<(ostream& out, const RepoException& ex);