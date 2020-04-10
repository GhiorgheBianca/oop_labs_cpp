#include "Domain.h"
#include "Service.h"
#include "Repository.h"
#include "Validator.h"
#include <assert.h>
#include <iostream>
#include <sstream>

using std::ostream;
using std::stringstream;

void testAdauga() {
	Repository repo;
	repo.addDisciplina(Disciplina{ "a",4,"optionala","a" });
	assert(repo.getDiscipline().size() == 1);
	assert(repo.findDisciplina("a", "a").getDenumire() == "a");

	repo.addDisciplina(Disciplina{ "b",4,"optionala","b" });
	assert(repo.getDiscipline().size() == 2);

	try {
		repo.addDisciplina(Disciplina{ "a",4,"optionala","a" });
		assert(false);
	}
	catch (const RepoException&) {
		assert(true);
	}

	try {
		repo.findDisciplina("c","c");
		assert(false);
	}
	catch (const RepoException& e) {
		stringstream os;
		os << e;
		assert(os.str().find("exista") >= 0);
	}
}

void testStergere()
{
	Repository repo;
	repo.addDisciplina(Disciplina{ "a",3,"optionala","a" });
	repo.addDisciplina(Disciplina{ "b",4,"optionala","b" });
	repo.addDisciplina(Disciplina{ "c",5,"facultativa","c" });
	repo.addDisciplina(Disciplina{ "d",6,"obligatorie","d" });
	assert(repo.getDiscipline().size() == 4);

	try {
		repo.deleteDisciplina(Disciplina{ "a",4,"optionala","b" });
		assert(false);
	}
	catch (const RepoException&) {
		assert(true);
	}

	repo.deleteDisciplina(Disciplina{ "b",4,"optionala","b" });
	try {
		repo.findDisciplina("b", "b");
		assert(false);
	}
	catch (const RepoException & e) {
		stringstream os;
		os << e;
		assert(os.str().find("exista") >= 0);
	}
	assert(repo.getDiscipline().size() == 3);

	repo.deleteDisciplina(Disciplina{ "a",3,"optionala","a" });
	try {
		repo.findDisciplina("a", "a");
		assert(false);
	}
	catch (const RepoException & e) {
		stringstream os;
		os << e;
		assert(os.str().find("exista") >= 0);
	}
	assert(repo.getDiscipline().size() == 2);

	repo.deleteDisciplina(Disciplina{ "d",6,"obligatorie","d" });
	try {
		repo.findDisciplina("d", "d");
		assert(false);
	}
	catch (const RepoException & e) {
		stringstream os;
		os << e;
		assert(os.str().find("exista") >= 0);
	}
	assert(repo.getDiscipline().size() == 1);
	repo.deleteDisciplina(Disciplina{ "c",5,"facultativa","c" });
	assert(repo.getDiscipline().size() == 0);
}

void testCauta() {
	Repository repo;
	repo.addDisciplina(Disciplina{ "a",4,"obligatorie","c" });
	repo.addDisciplina(Disciplina{ "b",4,"optionala","b" });

	auto disciplina = repo.findDisciplina("a","c");
	assert(disciplina.getDenumire() == "a");
	assert(disciplina.getCadruDidactic() == "c");

	try {
		repo.findDisciplina("a","b");
		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}
}

void testAdaugaService() {
	Repository repo;
	Validator validator;
	Service service{ repo,validator };
	service.addDisciplinaService("a", 6, "facultativa", "a");
	assert(service.getDiscipline().size() == 1);

	try {
		service.addDisciplinaService("", -1, "", "");
		assert(false);
	}
	catch (ValidateException&) {
		assert(true);
	}
	
	try {
		service.addDisciplinaService("a", -1, "facultativa", "a");
		assert(false);
	}
	catch (ValidateException&) {
		assert(true);
	}
}

void testStergeService() {
	Repository repo;
	Validator validator;
	Service service{ repo,validator };
	service.addDisciplinaService("a", 6, "facultativa", "a");
	assert(service.getDiscipline().size() == 1);

	try {
		service.deleteDisciplinaService("", "");
		assert(false);
	}
	catch (ValidateException&) {
		assert(true);
	}
	assert(service.getDiscipline().size() == 1);
	service.deleteDisciplinaService("a", "a");
	assert(service.getDiscipline().size() == 0);
}

void testFiltrare() {
	Repository repo;
	Validator validator;
	Service service{ repo,validator };
	service.addDisciplinaService("a", 3, "optionala", "a");
	service.addDisciplinaService("b", 4, "facultativa", "b");
	service.addDisciplinaService("c", 6, "obligatorie", "c");
	assert(service.filtrareDurata(3, 5).size() == 2);
	assert(service.filtrareDurata(3, 4).size() == 2);
	assert(service.filtrareCadruDidactic("a").size() == 1);
	assert(service.filtrareCadruDidactic("b").size() == 1);
	assert(service.filtrareCadruDidactic("d").size() == 0);
}

void testSortare() {
	Repository repo;
	Validator validator;
	Service service{ repo,validator };
	service.addDisciplinaService("z", 3, "optionala", "z");
	service.addDisciplinaService("b", 4, "obligatorie", "b");
	service.addDisciplinaService("c", 6, "optionala", "b");

	auto firstP = service.sorteaza_dupa_denumire()[0];
	assert(firstP.getDenumire() == "b");

	firstP = service.sorteaza_dupa_durata()[0];
	assert(firstP.getOre() == 3);

	firstP = service.sorteaza_dupa_profesor_tip()[0];
	assert(firstP.getOre() == 4);

}

void testValidator() {
	Validator validator;
	Disciplina disciplina{ "",-1,"","" };
	try {
		validator.validate(disciplina);
	}
	catch (const ValidateException & ex) {
		std::stringstream sout;
		sout << ex;
		auto mesaj = sout.str();
		assert(mesaj.find("negativ") >= 0);
		assert(mesaj.find("vid") >= 0);
	}

}

void all_tests()
{
	testAdauga();
	testStergere();
	testCauta();
	testAdaugaService();
	testStergeService();
	testFiltrare();
	testSortare();
	testValidator();
}