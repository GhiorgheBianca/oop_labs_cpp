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

	void statsUI();

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