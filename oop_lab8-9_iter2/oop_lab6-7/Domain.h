#pragma once
#include <iostream>
#include <vector>

using std::vector;
using std::string;

class Disciplina
{
private:
	int id_unic;
	string denumire;
	int ore_pe_saptamana;
	string tip;
	string cadru_didactic;

public:
	// constructor with parameters
	Disciplina(int id_unic, const string& denumire, int ore_pe_saptamana, const string& tip, const string& cadru_didactic) :id_unic{ id_unic }, denumire{ denumire }, ore_pe_saptamana{ ore_pe_saptamana }, tip{ tip }, cadru_didactic{ cadru_didactic } {}

	// GETTERS
	/*
		Functia returneaza id-ul unei discipline.
		Output: id_unic - int
	*/
	int getId() const noexcept {
		return id_unic;
	}
	/*
		Functia returneaza denumirea unei discipline.
		Output: denumire - string
	*/
	string getDenumire() const { 
		return denumire; 
	}
	/*
		Functia returneaza durata unei discipline in functie de numarul de ore pe saptamana.
		Output: ore_pe_saptamana - int
	*/
	int getOre() const noexcept { 
		return ore_pe_saptamana; 
	}
	/*
		Functia returneaza tipul unei discipline (obligatorie, optionala, facultativa).
		Output: tip - string
	*/
	string getTip() const { 
		return tip; 
	}
	/*
		Functia returneaza numele cadrului didactic care preda disciplina.
		Output: cadru_didactic - string
	*/
	string getCadruDidactic() const { 
		return cadru_didactic; 
	}

};


class Contract
{
	friend class Disciplina;
private:
	vector<Disciplina> discipline;

public:
	// constructor with parameters
	Contract(const vector<Disciplina>& discipline) :discipline{ discipline } {}

	// default constructor
	Contract() = default;

	// GETTERS
	/*
		Obtine toate disciplinele existente din contract.
		Output: toate disciplinele din contract;
	*/
	vector<Disciplina> getDiscipline_dinContract();

	/*
		Adauga o disciplina in contract.
		Input: disciplina - obiect de tip Disciplina;
		Output: adaugata disciplina in vectorul de discipline din contract;
	*/
	void push_backContract(const Disciplina& disciplina);

	/*
		Functia de stergere a unei discipline din contract.
		Input: position - numar intreg;
	*/
	void erase(int position);

	/*
		Sterge toate disciplinele din contract.
		Output: goleste vectorul de discipline din contract;
	*/
	void clearContract();

};


class DTO_statistics
{
private:
	string tip;
	int frecventa;

public:
	// constructor with parameters
	DTO_statistics(const string& tip, int frecventa) :tip{ tip }, frecventa{ frecventa }{}

	/*
		Functia care incrementeaza frecventa unui anumit tip.
		Input: stats - referinta la un obiect de tip DTO_statistics;
	*/
	void inc_frecventa(DTO_statistics& stats) noexcept;

	// GETTERS
	/*
		Functia returneaza tipul unei discipline (obligatorie, optionala, facultativa...).
		Output: tip - string;
	*/
	string getTip() const {
		return tip;
	}
	/*
		Functia returneaza frecventa unui tip in functie de disciplinele existente.
		Output: frecventa - int;
	*/
	int getFrecventa() const noexcept {
		return frecventa;
	}

};

/*
	Compara 2 discipline dupa denumire.
	Input: prima_disciplina, a_doua_disciplina - obiect de tip Disciplina
	Output: returneaza true daca prima denumire este mai mica decat a doua, false altfel
*/
bool cmpDenumire(const Disciplina& prima_disciplina, const Disciplina& a_doua_disciplina);

/*
	Compara 2 discipline dupa tip.
	Input: prima_disciplina, a_doua_disciplina - obiect de tip Disciplina
	Output: returneaza true daca primul tip este mai mic decat al doilea, false altfel
*/
bool cmpTip(const Disciplina& prima_disciplina, const Disciplina& a_doua_disciplina);

/*
	Compara 2 discipline dupa numele cadrului didactic.
	Input: prima_disciplina, a_doua_disciplina - obiect de tip Disciplina
	Output: returneaza true daca primul nume este mai mic decat al doilea, false altfel
*/
bool cmpCadruDidactic(const Disciplina& prima_disciplina, const Disciplina& a_doua_disciplina);