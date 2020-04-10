#pragma once
#include <iostream>

class Disciplina
{
private:
	std::string denumire;
	int ore_pe_saptamana;
	std::string tip;
	std::string cadru_didactic;

public:
	// default constructor
	Disciplina();

	// constructor with parameters
	Disciplina(const std::string& denumire, int ore_pe_saptamana, const std::string& tip, const std::string& cadru_didactic);

	// GETTERS
	/*
		Functia returneaza denumirea unei discipline.
		Output: denumire - string
	*/
	std::string getDenumire() const { 
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
	std::string getTip() const { 
		return tip; 
	}
	/*
		Functia returneaza numele cadrului didactic care preda disciplina.
		Output: cadru_didactic - string
	*/
	std::string getCadruDidactic() const { 
		return cadru_didactic; 
	}

};

/*
	Compara 2 discipline dupa denumire.
	Input: prima_disciplina, a_doua_disciplina - obiect de tip Disciplina
	Output: returneaza true daca prima denumire este mai mica decat a doua, false altfel
*/
bool cmpDenumire(const Disciplina& prima_disciplina, const Disciplina& a_doua_disciplina);

/*
	Compara 2 discipline dupa numarul de ore.
	Input: prima_disciplina, a_doua_disciplina - obiect de tip Disciplina
	Output: returneaza true daca prima durata este mai mica decat a doua, false altfel
*/
bool cmpNumarOre(const Disciplina& prima_disciplina, const Disciplina& a_doua_disciplina);

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