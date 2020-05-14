#pragma once

#include "Domain.h"
#include "Repository.h"

class ActiuneUndo {
public:
	virtual void doUndo() = 0;
	// destructorul este virtual pentru a ne asigura ca, la apelarea 
	// functiei delete, se apeleaza destructorul potrivit
	virtual ~ActiuneUndo() = default;
};

class UndoAdauga : public ActiuneUndo {
	Disciplina disciplinaAdaugata;
	VirtualRepository& repo;

public:
	// constructor with parameters
	UndoAdauga(VirtualRepository& repo, const Disciplina& disciplina) :repo{ repo }, disciplinaAdaugata{ disciplina } {}

	/*
		Functia care produce operatia de undo cand ultima operatie este adaugarea.
		Se revine la starea listei inaintea ultimei operatii.
	*/
	void doUndo() override {
		repo.deleteDisciplina(disciplinaAdaugata);
	}

};

class UndoSterge : public ActiuneUndo {
	Disciplina disciplinaStearsa;
	VirtualRepository& repo;

public:
	// constructor with parameters
	UndoSterge(VirtualRepository& repo, const Disciplina& disciplina) :repo{ repo }, disciplinaStearsa{ disciplina } {}

	/*
		Functia care produce operatia de undo cand ultima operatie este stergerea.
		Se revine la starea listei inaintea ultimei operatii.
	*/
	void doUndo() override {
		repo.addDisciplina(disciplinaStearsa);
	}

};

class UndoModifica : public ActiuneUndo {
	Disciplina disciplinaNemodificata;
	VirtualRepository& repo;

public:
	// constructor with parameters
	UndoModifica(VirtualRepository& repo, const Disciplina& disciplina) :repo{ repo }, disciplinaNemodificata{ disciplina } {}

	/*
		Functia care produce operatia de undo cand ultima operatie este modificarea.
		Se revine la starea listei inaintea ultimei operatii.
	*/
	void doUndo() override {
		repo.updateDisciplina(disciplinaNemodificata);
	}

};


class UndoAdauga_inContract : public ActiuneUndo {
	Disciplina disciplinaAdaugata_inContract;
	Contract& contract;
	VirtualRepository& repo;

public:
	// constructor with parameters
	UndoAdauga_inContract(VirtualRepository& repo, const Disciplina& disciplina, Contract& contractul) :repo{ repo }, disciplinaAdaugata_inContract{ disciplina }, contract{ contractul } {}

	/*
		Functia care produce operatia de undo cand ultima operatie este adaugarea in contract.
		Se revine la starea contractului inaintea ultimei operatii.
	*/
	void doUndo() override {
		repo.deleteDisciplina_fromContract(disciplinaAdaugata_inContract, contract);
	}

};