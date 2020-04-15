#include "Domain.h"
#include "Service.h"
#include "Repository.h"
#include "Validator.h"
#include "Exceptions.h"
#include <assert.h>
#include <iostream>
#include <sstream>

using std::ostream;
using std::stringstream;

void testAdauga() {
	Repository repo;
	repo.addDisciplina(Disciplina{ 1,"a",4,"optionala","a" });
	assert(repo.getDiscipline().size() == 1);

	repo.addDisciplina(Disciplina{ 2,"b",4,"optionala","b" });
	assert(repo.getDiscipline().size() == 2);

	try {
		repo.addDisciplina(Disciplina{ 2,"a",4,"optionala","a" });
		assert(false);
	}
	catch (const RepoException&) {
		assert(true);
	}

	try {
		repo.findDisciplina(3);
		assert(false);
	}
	catch (const RepoException& e) {
		stringstream os;
		os << e;
		assert(os.str().find("exista") >= 0);
	}
}

void testModificare() {
	Repository repo;
	Validator validator;
	Service service{ repo,validator };
	repo.addDisciplina(Disciplina{ 1,"a",3,"optionala","a" });
	repo.addDisciplina(Disciplina{ 2,"b",4,"optionala","b" });
	repo.addDisciplina(Disciplina{ 3,"c",5,"facultativa","c" });
	repo.addDisciplina(Disciplina{ 4,"d",6,"obligatorie","d" });
	assert(repo.getDiscipline().size() == 4);
	
	try {
		repo.updateDisciplina(Disciplina{ 5,"abc",4,"optionala","b" });
		assert(false);
	}
	catch (const RepoException&) {
		assert(true);
	}
	
	repo.updateDisciplina(Disciplina{ 2,"b",7,"obligatorie","b" });
	assert(service.filtrareDurata(7, 7).size() == 1);
	assert(repo.getDiscipline().size() == 4);

	repo.updateDisciplina(Disciplina{ 1,"a",5,"optionala","a" });
	assert(service.filtrareDurata(5, 5).size() == 2);
}

void testStergere() {
	Repository repo;
	repo.addDisciplina(Disciplina{ 1,"a",3,"optionala","a" });
	repo.addDisciplina(Disciplina{ 2,"b",4,"optionala","b" });
	repo.addDisciplina(Disciplina{ 3,"c",5,"facultativa","c" });
	repo.addDisciplina(Disciplina{ 4,"d",6,"obligatorie","d" });
	assert(repo.getDiscipline().size() == 4);
	
	try {
		repo.deleteDisciplina(Disciplina{ 5,"a",4,"optionala","b" });
		assert(false);
	}
	catch (const RepoException&) {
		assert(true);
	}
	
	repo.deleteDisciplina(Disciplina{ 3,"c",5,"facultativa","c" });
	try {
		repo.findDisciplina(3);
		assert(false);
	}
	catch (const RepoException & e) {
		stringstream os;
		os << e;
		assert(os.str().find("exista") >= 0);
	}
	assert(repo.getDiscipline().size() == 3);
	
	repo.deleteDisciplina(Disciplina{ 1,"a",3,"optionala","a" });
	try {
		repo.findDisciplina(1);
		assert(false);
	}
	catch (const RepoException & e) {
		stringstream os;
		os << e;
		assert(os.str().find("exista") >= 0);
	}
	assert(repo.getDiscipline().size() == 2);
	
	repo.deleteDisciplina(Disciplina{ 4,"d",6,"obligatorie","d" });
	try {
		repo.findDisciplina(4);
		assert(false);
	}
	catch (const RepoException & e) {
		stringstream os;
		os << e;
		assert(os.str().find("exista") >= 0);
	}
	assert(repo.getDiscipline().size() == 1);
	repo.deleteDisciplina(Disciplina{ 2,"b",4,"optionala","b" });
	assert(repo.getDiscipline().size() == 0);
}

void testCauta() {
	Repository repo;
	Validator validator;
	Service service{ repo,validator };
	repo.addDisciplina(Disciplina{ 1,"a",4,"obligatorie","c" });
	repo.addDisciplina(Disciplina{ 2,"b",4,"optionala","d" });
	assert(repo.findDisciplina(1).getDenumire() == "a");
	assert(repo.findDisciplina(1).getCadruDidactic() == "c");
	assert(repo.findDisciplina(2).getDenumire() == "b");
	assert(repo.findDisciplina(2).getCadruDidactic() == "d");

	try {
		repo.findDisciplina(3);
		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}

	vector<Disciplina> result = service.cautaDisciplina("a", "c");
	for (const auto& disciplina : result) {
		if (disciplina.getDenumire() != "a" && disciplina.getCadruDidactic() != "c") {
			assert(false);
		}
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

void testModificaService() {
	Repository repo;
	Validator validator;
	Service service{ repo,validator };
	service.addDisciplinaService("a", 6, "facultativa", "a");
	assert(service.getDiscipline().size() == 1);

	try {
		service.updateDisciplinaService(0, "", -1, "gol", "");
		assert(false);
	}
	catch (ValidateException&) {
		assert(true);
	}
	assert(service.getDiscipline().size() == 1);
	service.updateDisciplinaService(1, "a", 4, "optionala", "a");
	assert(service.filtrareDurata(4, 4).size() == 1);
	assert(service.filtrareDurata(6, 6).size() == 0);
}

void testStergeService() {
	Repository repo;
	Validator validator;
	Service service{ repo,validator };
	service.addDisciplinaService("a", 6, "facultativa", "a");
	assert(service.getDiscipline().size() == 1);

	try {
		service.deleteDisciplinaService(-1);
		assert(false);
	}
	catch (ValidateException&) {
		assert(true);
	}
	assert(service.getDiscipline().size() == 1);
	service.deleteDisciplinaService(1);
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
	Disciplina disciplina{ 0,"",-1,"","" };
	try {
		validator.validate(disciplina);
	}
	catch (const ValidateException & ex) {
		std::stringstream sout;
		sout << ex;
		const auto mesaj = sout.str();
		assert(mesaj.find("negativ") >= 0);
		assert(mesaj.find("vid") >= 0);
	}
}

void testStats() {
	Repository repo;
	Validator validator;
	Service service{ repo,validator };
	service.addDisciplinaService("a", 3, "optionala", "a");
	service.addDisciplinaService("b", 4, "facultativa", "b");
	service.addDisciplinaService("c", 6, "obligatorie", "c");
	service.addDisciplinaService("d", 6, "optionala", "d");

	vector<DTO_statistics> DTO_stats = service.statsService();
	for (const auto& stat : DTO_stats) {
		if (stat.getTip() == "optionala")
			assert(stat.getFrecventa() == 2);
		else if (stat.getTip() == "obligatorie")
			assert(stat.getFrecventa() == 1);
		else if (stat.getTip() == "facultativa")
			assert(stat.getFrecventa() == 1);
	}
}

void testTotalDiscipline() {
	Repository repo;
	Validator validator;
	Service service{ repo,validator };
	service.addDisciplinaService("a", 3, "optionala", "a");
	service.addDisciplinaService("b", 4, "facultativa", "b");
	service.addDisciplinaService("c", 6, "obligatorie", "c");
	service.addDisciplinaService("d", 6, "optionala", "d");

	assert(service.totalOreDiscipline() == 19);
}

/*
void testAdaugareContract() {
	Repository repo;
	repo.addDisciplina(Disciplina{ "a",3,"optionala","e" });
	repo.addDisciplina(Disciplina{ "b",4,"optionala","f" });
	repo.addDisciplina(Disciplina{ "c",5,"facultativa","g" });
	repo.addDisciplina(Disciplina{ "d",6,"obligatorie","h" });
	repo.addContract(repo.getDiscipline(), 1);
	int i = 0;
	vector<Disciplina> contract = repo.getContract(1);
	for (const auto& disciplina : contract) {
		assert(disciplina.getDenumire() == repo.getDiscipline()[i].getDenumire());
		i++;
	}
	try {
		repo.getContract(2);
		assert(false);
	}
	catch (RepoException) {
		assert(true);
	}
	repo.golesteDiscipline();
	assert(repo.getContract(1)[0].getDenumire() == "a");
	assert(repo.getContract(1).size() == 4);
	repo.golesteContract(1);
	assert(repo.getContract(1).size() == 0);
	repo.stergeContract(1);
	repo.addDisciplina(Disciplina{ "abc",5,"facultativa","a" });
	repo.addDisciplina(Disciplina{ "def",6,"facultativa","c" });
	repo.addContract(repo.getDiscipline(), 2);
	i = 0;
	contract = repo.getContract(2);
	for (const auto& disciplina : contract) {
		assert(disciplina.getDenumire() == repo.getDiscipline()[i].getDenumire());
		i++;
	}
	assert(contract.size() == 2);
	repo.setDiscipline_dinContract(2);
}*/

void all_tests()
{
	testAdauga();
	testModificare();
	testStergere();
	testCauta();
	testAdaugaService();
	testModificaService();
	testStergeService();
	testFiltrare();
	testSortare();
	testStats();
	testValidator();
	testTotalDiscipline();
	//testAdaugareContract();
}