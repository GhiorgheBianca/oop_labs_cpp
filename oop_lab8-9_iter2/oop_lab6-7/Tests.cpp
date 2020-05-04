#include "Service.h"
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
		repo.findPosition(3, repo.getDiscipline());
		assert(false);
	}
	catch (const RepoException & e) {
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
		repo.findPosition(3, repo.getDiscipline());
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
		repo.findPosition(1, repo.getDiscipline());
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
		repo.findPosition(4, repo.getDiscipline());
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
	assert(repo.getDiscipline()[repo.findPosition(1, repo.getDiscipline())].getDenumire() == "a");
	assert(repo.getDiscipline()[repo.findPosition(1, repo.getDiscipline())].getCadruDidactic() == "c");
	assert(repo.getDiscipline()[repo.findPosition(2, repo.getDiscipline())].getDenumire() == "b");
	assert(repo.getDiscipline()[repo.findPosition(2, repo.getDiscipline())].getCadruDidactic() == "d");

	try {
		repo.findPosition(3, repo.getDiscipline());
		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}
	try {
		service.cautaDisciplina(3);
		assert(false);
	}
	catch (const ServiceException& e) {
		stringstream os;
		os << e;
		assert(os.str().find("nu exista") >= 0);
	}

	vector<Disciplina> result = service.cautaDisciplina(1);
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

void testUndo() {
	Repository repo;
	Validator validator;
	Service service{ repo,validator };
	try {
		service.undo();
		assert(false);
	}
	catch (ServiceException&) {
		assert(true);
	}
	service.addDisciplinaService("a", 3, "optionala", "a");
	service.addDisciplinaService("b", 4, "facultativa", "b");
	service.addDisciplinaService("c", 6, "obligatorie", "c");
	service.addDisciplinaService("d", 6, "optionala", "d");
	assert(service.getDiscipline().size() == 4);

	service.undo();
	assert(service.getDiscipline().size() == 3);
	assert(service.getDiscipline().at(2).getCadruDidactic() == "c");

	service.updateDisciplinaService(1, "ae", 4, "facultativa", "ad");
	assert(service.getDiscipline().at(0).getDenumire() == "ae");

	service.undo();
	assert(service.getDiscipline().size() == 3);
	assert(service.getDiscipline().at(0).getDenumire() == "a");

	service.deleteDisciplinaService(1);
	service.deleteDisciplinaService(2);
	assert(service.getDiscipline().size() == 1);
	try {
		repo.findPosition(2, repo.getDiscipline());
		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}

	service.undo();
	assert(service.getDiscipline().size() == 2);
	repo.findPosition(2, repo.getDiscipline());


	service.addDisciplina_toContractService(20, "a", 3, "optionala", "e");
	service.addDisciplina_toContractService(21, "b", 4, "facultativa", "f");
	service.addDisciplina_toContractService(22, "c", 6, "obligatorie", "g");
	assert(service.totalDiscipline_dinContract() == 3);

	service.undo();
	assert(service.totalDiscipline_dinContract() == 2);
	assert(service.getDiscipline_dinContract().at(0).getId() == 20);
	assert(service.getDiscipline_dinContract().at(1).getId() == 21);

	service.undo();
	assert(service.totalDiscipline_dinContract() == 1);
	assert(service.getDiscipline_dinContract().at(0).getId() == 20);

	service.undo();
	assert(service.totalDiscipline_dinContract() == 0);
}

void testCitire_Scriere_Fisier() {
	try {
		RepoFile no_file{ "no_file.txt",0 };
		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}
	RepoFile repo{ "test_discipline.txt",0 };
	repo.addDisciplina(Disciplina{ 1,"a",3,"obligatorie","e" });
	repo.addDisciplina(Disciplina{ 2,"b",4,"optionala","f" });
	repo.addDisciplina(Disciplina{ 3,"c",5,"facultativa","g" });
	RepoFile reopen_repo{ "test_discipline.txt",0 };
	assert(reopen_repo.getDiscipline().size() == 3);
	assert(reopen_repo.getDiscipline().at(0).getId() == 1);
	assert(reopen_repo.getDiscipline().at(0).getDenumire() == "a");
	assert(reopen_repo.getDiscipline().at(0).getOre() == 3);
	assert(reopen_repo.getDiscipline().at(0).getTip() == "obligatorie");
	assert(reopen_repo.getDiscipline().at(0).getCadruDidactic() == "e");
	assert(reopen_repo.getDiscipline().at(2).getId() == 3);

	reopen_repo.updateDisciplina(Disciplina{ 1,"ab",4,"optionala","ef" });
	assert(reopen_repo.getDiscipline().at(0).getId() == 1);
	assert(reopen_repo.getDiscipline().at(0).getDenumire() == "ab");
	assert(reopen_repo.getDiscipline().at(0).getOre() == 4);
	assert(reopen_repo.getDiscipline().at(0).getTip() == "optionala");
	assert(reopen_repo.getDiscipline().at(0).getCadruDidactic() == "ef");
	reopen_repo.deleteDisciplina(Disciplina{ 1,"ab",4,"optionala","ef" });
	try {
		reopen_repo.findPosition(1, reopen_repo.getDiscipline());
		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}

	repo.deleteFileContent();
}

void testContract() {
	Repository repo;
	Validator validator;
	Service service{ repo,validator };
	assert(service.totalDiscipline_dinContract() == 0);

	//test adaugare
	service.addDisciplina_toContractService(20, "a", 3, "optionala", "e");
	service.addDisciplina_toContractService(21, "b", 4, "facultativa", "f");
	service.addDisciplina_toContractService(22, "c", 6, "obligatorie", "g");
	try {
		service.addDisciplina_toContractService(20, "a", 3, "optionala", "e");
		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}

	assert(service.totalDiscipline_dinContract() == 3);
	assert(service.getDiscipline_dinContract().at(2).getCadruDidactic() == "g");
	assert(service.getDiscipline_dinContract().at(0).getDenumire() == "a");

	//test salvare
	service.save_toHTMLService("test_HTML.html");
	RepoFile repoF{ "test_HTML.html",0 };
	assert(repoF.getDiscipline().size() == 3);
	assert(repoF.getDiscipline().at(2).getCadruDidactic() == "g");
	assert(repoF.getDiscipline().at(0).getDenumire() == "a");

	//test stergere
	service.golesteContract();
	assert(service.totalDiscipline_dinContract() == 0);
}

void testRandomAdd() {
	Repository repo;
	Validator validator;
	Service service{ repo,validator };
	service.addDisciplinaService("a", 3, "optionala", "ab");
	service.addDisciplinaService("b", 4, "facultativa", "cd");
	service.addDisciplinaService("c", 6, "obligatorie", "ef");
	service.addDisciplinaService("d", 5, "facultativa", "gh");
	service.addDisciplinaService("e", 3, "facultativa", "ij");
	service.addDisciplinaService("f", 7, "optionala", "kl");
	
	try {
		service.addRandom_toContract(7);
		assert(false);
	}
	catch (ServiceException&) {
		assert(true);
	}

	assert(service.totalDiscipline_dinContract() == 0);
	service.addRandom_toContract(4);
	assert(service.totalDiscipline_dinContract() == 4);
	bool gasit = false;
	for (int i = 0; i < 6; i++)
		if (service.getDiscipline_dinContract().at(3).getId() == repo.getDiscipline().at(i).getId())
			gasit = true;
	assert(gasit);
}

void testAdauga_inContract() {
	Repository repo;
	Validator validator;
	Service service{ repo,validator };
	service.addDisciplinaService("a", 3, "optionala", "ab");
	service.addDisciplinaService("c", 6, "obligatorie", "ef");

	service.add_toContract_dupaId(1);
	try {
		service.add_toContract_dupaId(3);
		assert(false);
	}
	catch (ServiceException&) {
		assert(true);
	}
	assert(service.totalDiscipline_dinContract() == 1);

	service.add_toContract_dupaId(2);
	try {
		service.add_toContract_dupaId(2);
		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}
	assert(service.totalDiscipline_dinContract() == 2);
}

void testErrorProbability() {
	Repository repo{ 0.7 };
	int success = 0, unsuccess = 0;
	for (int j = 1; j <= 100; j++) {
		try {
			repo.addDisciplina(Disciplina{ j,"a",4,"optionala","a" });
			success++;
		}
		catch (RepoException&) {
			unsuccess++;
		}
	}
	//std::cout << success << " " << unsuccess << '\n';

	success = 0; unsuccess = 0;
	for (int j = 1; j <= 100; j++) {
		try {
			repo.updateDisciplina(Disciplina{ j,"a",4,"optionala","a" });
			success++;
		}
		catch (RepoException&) {
			unsuccess++;
		}
	}
	//std::cout << success << " " << unsuccess << '\n';

	success = 0; unsuccess = 0;
	for (int j = 1; j <= 100; j++) {
		try {
			repo.deleteDisciplina(Disciplina{ j,"a",4,"optionala","a" });
			success++;
		}
		catch (RepoException&) {
			unsuccess++;
		}
	}
	//std::cout << success << " " << unsuccess << '\n';
}

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
	testUndo();
	testCitire_Scriere_Fisier();
	testContract();
	testRandomAdd();
	testAdauga_inContract();
	testErrorProbability();
}