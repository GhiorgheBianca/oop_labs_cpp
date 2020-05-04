#pragma once

#include "Service.h"
#include "Domain.h"
//#include "LinkedList.h"

class ConsolUI {
	Service& service;

	/*
		Functia care citeste datele de la tastatura si adauga disciplina.
		Arunca exceptie daca: nu se poate salva, nu e valida.
	*/
	void adaugaUI();

	/*
		Functia care citeste datele de la tastatura si modifica o disciplina.
		Arunca exceptie daca: nu se poate modifica, datele nu sunt valide.
	*/
	void modificaUI();

	/*
		Functia care citeste denumirea si numele profesorului de la tastatura si sterge disciplina.
		Arunca exceptie daca: nu se poate sterge, datele nu sunt valide.
	*/
	void stergeUI();

	/*
		Functia prin care se tipareste lista de discipline.
	*/
	void tiparesteUI(const vector<Disciplina>& discipline);

	/*
		Functia prin care se apeleaza filtrarea dupa numele cadrului didactic.
	*/
	void filtreazaProfUI();

	/*
		Functia prin care se apeleaza filtrarea dupa o durata minima si o durata maxima.
	*/
	void filtreazaDurataUI();

	/*
		Functia prin care se cauta o disciplina dupa denumire si dupa numele cadrului didactic. Se afiseaza poate datele disciplinei.
	*/
	void cautaDisciplinaUI();

	/*
		Functia prin care se afiseaza statisticile referitoare la numarul tipurilor pentru fiecare disciplina existenta.
	*/
	void statsUI();

	/*
		Functia prin care se revine la lista de discipline formata inaintea ultimei operatii.
	*/
	void undoUI();

	/*
		Functia prin care se goleste total contractul de discipline.
	*/
	void golesteContractUI();

	/*
		Functia prin care se adauga in contract dupa id-ul unei discipline existente in lista.
	*/
	void adauga_inContractUI();

	/*
		Functia prin care se adauga aleator un numar de discipline in contract.
	*/
	void adaugaRandom_inContractUI();

	/*
		Functia prin care se salveaza intr-un fisier HTML disciplinele din contract.
	*/
	void salveaza_inHTMLUI();

public:
	// default constructor
	ConsolUI(Service& service) noexcept :service{ service } {}

	// nu permitem copierea obiectelor
	ConsolUI(const ConsolUI& other) = delete;

	/*
		Functia prin care se executa interfata grafica.
	*/
	void start();

};