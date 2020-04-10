#pragma once

#include "Domain.h"
#include "LinkedList.h"
#include "Validator.h"
#include "Repository.h"

#include <string>
#include <functional>

using std::string;
using std::function;

class Service {
	Repository& repo;
	Validator& validator;

	/*
		Functie de sortare generala
		maiMicF - functie care compara 2 discipline, verifica daca are loc relatia mai mic
			  - poate fi orice functe (in afara clasei) care respecta signatura (returneaza bool are 2 parametrii Disciplina)
			  - poate fi functie lambda (care nu capteaza nimic in capture list)
		returneaza o lista sortata dupa criteriu dat ca paramatru
	*/
	Lista<Disciplina> sorteaza(bool (*maiMicF)(const Disciplina&, const Disciplina&));

	/*
		Functie generala de filtrare
			fct - poate fi o functie
			fct - poate fi lambda, am folosit function<> pentru a permite si functii lambda care au ceva in capture list
		returneaza doar disciplinele care trec de filtru (fct(disciplina)==true)
	*/
	Lista<Disciplina> filtreaza(function<bool(const Disciplina&)> fct);

public:
	// default constructor
	Service(Repository& repo, Validator& validator) :repo{ repo }, validator{ validator } {}

	// nu permitem copierea de discipline
	Service(const Service& other) = delete;

	/*
		Trimite toate disciplinele din repository printr-un vector.
		Output: returneaza vectorul cu toate disciplinele in ordinea in care au fost adaugate;
	*/
	const Lista<Disciplina>& getDiscipline() {
		return repo.getDiscipline();
	}

	/*
		Adauga o disciplina prin service.
		Input: denumire, tip, cadru_didactic - string; ore_pe_saptamana - int;
		Output: trimite disciplina spre repository pentru adaugare sau arunca exceptie daca nu se poate salva, nu este valid;
	*/
	void addDisciplinaService(const string& denumire, int ore_pe_saptamana, const string& tip, const string& cadru_didactic);

	/*
		Modifica o disciplina prin service.
		Input: denumire, tip, cadru_didactic - string; ore_pe_saptamana - int;
		Output: trimite disciplina spre repository pentru modificare sau arunca exceptie daca denumirea si/sau numele cadrului didactic sunt invalide;
	*/
	void updateDisciplinaService(const string& denumire, int ore_pe_saptamana, const string& tip, const string& cadru_didactic);

	/*
		Sterge o disciplina prin service.
		Input: denumire, cadru_didactic - string;
		Output: trimite disciplina spre repository pentru stergere sau arunca exceptie daca denumirea si/sau numele cadrului didactic sunt invalide;
	*/
	void deleteDisciplinaService(const string& denumire, const string& cadru_didactic);

	/*
		Sorteaza vectorul dupa numarul de ore.
		Output: returneaza vectorul de discipline sortat;
	*/
	Lista<Disciplina> sorteaza_dupa_durata();

	/*
		Sorteaza vectorul dupa denumire.
		Output: returneaza vectorul de discipline sortat;
	*/
	Lista<Disciplina> sorteaza_dupa_denumire();

	/*
		Sorteaza vectorul dupa tip si dupa numarul de ore.
		Output: returneaza vectorul de discipline sortat;
	*/
	Lista<Disciplina> sorteaza_dupa_profesor_tip();

	/*
		Filtreaza vectorul dupa cadrul didactic.
		Output: returneaza vectorul de discipline numai cu elementele care se potrivesc conditiei; 
	*/
	Lista<Disciplina> filtrareCadruDidactic(const string& cadru_didactic);

	/*
		Filtreaza vectorul dupa numarul de ore astfel incat sa se incadreze intre minim si maxim.
		Output: returneaza vectorul de discipline numai cu elementele care se potrivesc conditiei;
	*/
	Lista<Disciplina> filtrareDurata(int durataMin, int durataMax);

	/*
		Cauta in vector dupa denumire si numele cadrului didactic.
		Output: returneaza vectorul cu disciplina care contine numai elementele care se potrivesc conditiei;
	*/
	Lista<Disciplina> cautaDisciplina(const string& denumire, const string& profesor);

	/*
		Formeaza statisticile referitoare la numarul tipurilor pentru fiecare disciplina existenta.
		Output: returneaza un vector cu statistici pentru toate tipurile declarate la cel putin o disciplina.
	*/
	vector<DTO_statistics> statsService() const;

};