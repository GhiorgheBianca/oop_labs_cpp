#pragma once

#include "Domain.h"
//#include "LinkedList.h"
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
		Functie generala de filtrare
			fct - poate fi o functie
			fct - poate fi lambda, am folosit function<> pentru a permite si functii lambda care au ceva in capture list
		returneaza doar disciplinele care trec de filtru (fct(disciplina)==true)
	*/
	vector<Disciplina> filtreaza(function<bool(const Disciplina&)> fct);

public:
	// default constructor
	Service(Repository& repo, Validator& validator) noexcept :repo{ repo }, validator{ validator } {}

	// nu permitem copierea de discipline
	Service(const Service& other) = delete;

	/*
		Trimite toate disciplinele din repository printr-un vector.
		Output: returneaza vectorul cu toate disciplinele in ordinea in care au fost adaugate;
	*/
	vector<Disciplina> getDiscipline() noexcept;

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
	void updateDisciplinaService(int id, const string& denumire, int ore_pe_saptamana, const string& tip, const string& cadru_didactic);

	/*
		Sterge o disciplina prin service.
		Input: id - int;
		Output: trimite disciplina spre repository pentru stergere sau arunca exceptie daca id-ul este invalid;
	*/
	void deleteDisciplinaService(int id);

	/*
		Sorteaza vectorul dupa numarul de ore.
		Output: returneaza vectorul de discipline sortat;
	*/
	vector<Disciplina> sorteaza_dupa_durata();

	/*
		Sorteaza vectorul dupa denumire.
		Output: returneaza vectorul de discipline sortat;
	*/
	vector<Disciplina> sorteaza_dupa_denumire();

	/*
		Sorteaza vectorul dupa tip si dupa numarul de ore.
		Output: returneaza vectorul de discipline sortat;
	*/
	vector<Disciplina> sorteaza_dupa_profesor_tip();

	/*
		Filtreaza vectorul dupa cadrul didactic.
		Output: returneaza vectorul de discipline numai cu elementele care se potrivesc conditiei; 
	*/
	vector<Disciplina> filtrareCadruDidactic(const string& cadru_didactic);

	/*
		Filtreaza vectorul dupa numarul de ore astfel incat sa se incadreze intre minim si maxim.
		Output: returneaza vectorul de discipline numai cu elementele care se potrivesc conditiei;
	*/
	vector<Disciplina> filtrareDurata(int durataMin, int durataMax);

	/*
		Cauta in vector dupa denumire si numele cadrului didactic.
		Output: returneaza vectorul cu disciplina care contine numai elementele care se potrivesc conditiei;
	*/
	vector<Disciplina> cautaDisciplina(const string& denumire, const string& profesor);

	/*
		Formeaza statisticile referitoare la numarul tipurilor pentru fiecare disciplina existenta.
		Output: returneaza un vector cu statistici pentru toate tipurile declarate la cel putin o disciplina.
	*/
	vector<DTO_statistics> statsService() const;

	/*
		Functia care calculeaza numarul total de ore alocat pentru toate disciplinele.
		Output: returneaza suma formata din numarul orelor clasificate fiecarei discipline, ca intreg (int);
	*/
	const int totalOreDiscipline();

};