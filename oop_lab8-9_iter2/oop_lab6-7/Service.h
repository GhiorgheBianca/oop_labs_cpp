#pragma once

#include "Domain.h"
//#include "LinkedList.h"
#include "Validator.h"
#include "Repository.h"
#include "Undo.h"

#include <string>
#include <functional>

using std::string;
using std::function;
using std::unique_ptr;

class Service {
	VirtualRepository& repo;
	Validator& validator;
	Contract contract;
	std::vector<unique_ptr<ActiuneUndo>> undoActions;

	/*
		Functie generala de filtrare
			fct - poate fi o functie
			fct - poate fi lambda, am folosit function<> pentru a permite si functii lambda care au ceva in capture list
		returneaza doar disciplinele care trec de filtru (fct(disciplina)==true)
	*/
	vector<Disciplina> filtreaza(function<bool(const Disciplina&)> fct);

	vector<int> random(int min, int max);

	/*
		Metoda privata, verifica daca exista deja disciplina in repository
		Input: disciplina - obiect de tip Disciplina;
		Output: true daca disciplina a fost gasita sau false daca nu s-a gasit nimic;
	*/
	bool exist(const Disciplina& disciplina, const vector<Disciplina>& discipline) const;

public:
	// default constructor
	Service() noexcept = default;

	// constructor with parameters
	Service(VirtualRepository& repo, Validator& validator) noexcept :repo{ repo }, validator{ validator } {}

	// destructor
	~Service();

	// nu permitem copierea de discipline
	Service(const Service& other) = delete;

	void operator=(const Service& other) = delete; //nu vreau sa mearga assignment

	/*
		Trimite toate disciplinele din repository printr-un vector.
		Output: returneaza vectorul cu toate disciplinele in ordinea in care au fost adaugate;
	*/
	const vector<Disciplina>& getDiscipline() {
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
		Input: denumire, tip, cadru_didactic - string; id, ore_pe_saptamana - int;
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
		Cauta in vector dupa id.
		Input: id - int;
		Output: returneaza vectorul cu disciplina care contine numai elementele care se potrivesc conditiei;
	*/
	vector<Disciplina> cautaDisciplina(int id);

	/*
		Formeaza statisticile referitoare la numarul tipurilor pentru fiecare disciplina existenta.
		Output: returneaza un vector cu statistici pentru toate tipurile declarate la cel putin o disciplina.
	*/
	vector<DTO_statistics> statsService() const;

	/*
		Functia care executa operatia de revenire undo.
	*/
	void undo();

	/*
		Functia care transmite numarul de discipline din contract.
		Output: returneaza numarul total de discipline din contract;
	*/
	const int totalDiscipline_dinContract();

	/*
		Salveaza disciplinele din contract intr-un fisier HTML al carui nume este specificat de utilizator.
		Input: myFile - string;
		Output: apeleaza scrierea in fisier vectorul de discipline din contract;
	*/
	void save_toHTMLService(string myFile);

	/*
		Obtine toate disciplinele existente din contract.
		Output: toate disciplinele din contract;
	*/
	const vector<Disciplina> getDiscipline_dinContract();

	/*
		Apeleaza adaugarea in contract pentru o disciplina.
		Input: denumire, tip, cadru_didactic - string; id, ore_pe_saptamana - int;
		Output: apeleaza adaugarea unei discipline in contract;
	*/
	void addDisciplina_toContractService(int id, const string& denumire, int ore_pe_saptamana, const string& tip, const string& cadru_didactic);

	/*
		Adauga in contract o disciplina.
		Input: disciplina - obiect de tip Disciplina;
		Output: adaugata o disciplina in contractul din service;
	*/
	void addDisciplina_toContract(const Disciplina& discipline);

	/*
		Adauga in contract disciplina existenta cu un anumit id.
		Input: id - int;
		Output: adaugata disciplina cu id-ul specificat in contractul din service;
	*/
	void add_toContract_dupaId(int id);

	/*
		Adauga in contract un numar de discipline, intr-o ordine aleatoare.
		Input: number - int;
		Output: adaugata un numar de discipline, intr-o ordine aleatoare, in contractul din service;
	*/
	void addRandom_toContract(size_t number);

	/*
		Sterge toate disciplinele din contract.
		Output: goleste vectorul de discipline din contract apeland functia din Domain;
	*/
	void golesteContract();

};