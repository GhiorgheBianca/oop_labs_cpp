#include "Service.h"
#include <functional>
#include <algorithm>
#include <assert.h>

#include <vector>
#include <unordered_map>
#include <random>

void Service::addDisciplinaService(const string& denumire, int ore_pe_saptamana, const string& tip, const string& cadru_didactic) {
	int id = static_cast<int>(repo.getDiscipline().size()) + 1;
	Disciplina disciplina{ id,denumire,ore_pe_saptamana,tip,cadru_didactic };
	validator.validate(disciplina);
	repo.addDisciplina(disciplina);
	undoActions.push_back(std::make_unique<UndoAdauga>(repo, disciplina));
}

void Service::updateDisciplinaService(int id, const string& denumire, int ore_pe_saptamana, const string& tip, const string& cadru_didactic) {
	Disciplina disciplina{ id,denumire,ore_pe_saptamana,tip,cadru_didactic };
	validator.validate(disciplina);
	Disciplina disciplina_neactualizata = cautaDisciplina(id).at(0);
	repo.updateDisciplina(disciplina);
	undoActions.push_back(std::make_unique<UndoModifica>(repo, disciplina_neactualizata));
}

void Service::deleteDisciplinaService(int id) {
	Disciplina disciplina{ id,"denumire",1,"optionala","cadru_didactic" };
	validator.validate(disciplina);
	repo.deleteDisciplina(disciplina);
	undoActions.push_back(std::make_unique<UndoSterge>(repo, disciplina));
}

vector<Disciplina> Service::sorteaza_dupa_durata() {
	auto copyAll = repo.getDiscipline();
	std::sort(copyAll.begin(), copyAll.end(), [](const Disciplina& prima_disciplina, const Disciplina& a_doua_disciplina) noexcept {
		return prima_disciplina.getOre() < a_doua_disciplina.getOre();
	});
	return copyAll;
}

vector<Disciplina> Service::sorteaza_dupa_denumire() {
	auto copyAll = repo.getDiscipline();
	std::sort(copyAll.begin(), copyAll.end(), cmpDenumire);
	return copyAll;
}

vector<Disciplina> Service::sorteaza_dupa_profesor_tip() {
	auto copyAll = repo.getDiscipline();
	std::sort(copyAll.begin(), copyAll.end(), [](const Disciplina& prima_disciplina, const Disciplina& a_doua_disciplina) {
		if (prima_disciplina.getCadruDidactic() == a_doua_disciplina.getCadruDidactic()) {
			return cmpTip(prima_disciplina, a_doua_disciplina);
		}
		return cmpCadruDidactic(prima_disciplina, a_doua_disciplina);
		});
	return copyAll;
}

vector<Disciplina> Service::filtreaza(function<bool(const Disciplina&)> fct) {
	vector<Disciplina> rez;
	auto copyAll = repo.getDiscipline();
	std::copy_if(copyAll.begin(), copyAll.end(), std::back_inserter(rez), fct);
	return rez;
}

vector<Disciplina> Service::filtrareCadruDidactic(const string& cadru_didactic) {
	return filtreaza([cadru_didactic](const Disciplina& disciplina) {
		return disciplina.getCadruDidactic() == cadru_didactic;
		});
}

vector<Disciplina> Service::filtrareDurata(int durataMin, int durataMax) {
	return filtreaza([=](const Disciplina& disciplina) noexcept {
		return disciplina.getOre() >= durataMin && disciplina.getOre() <= durataMax;
		});
}

vector<Disciplina> Service::cautaDisciplina(int id) {
	vector<Disciplina> rez;
	auto copyAll = repo.getDiscipline();
	auto get_disciplina = std::find_if(copyAll.begin(), copyAll.end(), [id](const Disciplina& disciplina) {
		return disciplina.getId() == id;
		});
	if (get_disciplina != copyAll.end())
		rez.push_back(*get_disciplina);
	else {
		throw ServiceException("Nu exista nicio disciplina cu id-ul: " + std::to_string(id));
	}
	return rez;
}

vector<DTO_statistics> Service::statsService() const {
	vector<Disciplina> discipline = repo.getDiscipline();
	vector<DTO_statistics> DTO_stats;
	std::unordered_map<string, DTO_statistics> my_map;

	for (const auto& disciplina : discipline) {
		if (my_map.find(disciplina.getTip()) == my_map.end())
		{
			DTO_statistics new_DTO{ disciplina.getTip(),1 };
			my_map.insert({ disciplina.getTip(),new_DTO });
		}
		else {
			my_map.at(disciplina.getTip()).inc_frecventa(my_map.at(disciplina.getTip()));
		}
	}
	int total = 0;
	for (const auto& stat : my_map)
	{
		total += stat.second.getFrecventa();
		DTO_stats.push_back(stat.second);
	}
	return DTO_stats;
}

void Service::undo() {
	if (undoActions.empty()) {
		throw ServiceException("Nu mai exista operatii!");
	}
	undoActions.back()->doUndo();
	undoActions.pop_back();
}

Service::~Service() {
}


const vector<Disciplina> Service::getDiscipline_dinContract() {
	return contract.getDiscipline_dinContract();
}

const int Service::totalDiscipline_dinContract() {
	return getDiscipline_dinContract().size();
}

bool Service::exist(const Disciplina& disciplina, const vector<Disciplina>& disciplinele) const {
	try {
		repo.findPosition(disciplina.getId(), disciplinele);
		return true;
	}
	catch (RepoException&) {
		return false;
	}
}

void Service::golesteContract() {
	contract.clearContract();
}



void Service::addDisciplina_toContract(const Disciplina& disciplina) {
	if (exist(disciplina, contract.getDiscipline_dinContract())) {
		throw RepoException("Exista deja o disciplina cu denumirea: " + disciplina.getDenumire() + " si cadrul didactic: " + disciplina.getCadruDidactic() + " in contract!");
	}
	contract.push_backContract(disciplina);
	undoActions.push_back(std::make_unique<UndoAdauga_inContract>(repo, disciplina, contract));
}

void Service::addDisciplina_toContractService(int id, const string& denumire, int ore_pe_saptamana, const string& tip, const string& cadru_didactic) {
	Disciplina disciplina{ id,denumire,ore_pe_saptamana,tip,cadru_didactic };
	validator.validate(disciplina);
	addDisciplina_toContract(disciplina);
}

// random uniq-number algorithm
vector<int> Service::random(int min, int max) {
	vector<int> vect;
	for (int nr = min; nr <= max; nr++) {
		vect.push_back(nr);
	}

	int n = vect.size(), aux;
	for (int i = 0; i < n - 1; i++) {
		int j = i + rand() % (n - i);
		aux = vect[i];
		vect[i] = vect[j];
		vect[j] = aux;
	}
	return vect;
}
////

void Service::addRandom_toContract(size_t number) {
	golesteContract();
	if (getDiscipline().size() < number)
		throw ServiceException("Nu exista suficiente discipline pentru a adauga " + std::to_string(number));
	vector<int> vect = random(0, getDiscipline().size() - 1);
	while (number != 0) {
		addDisciplina_toContract(getDiscipline().at(vect.at(number - 1)));
		number--;
	}
}

void Service::add_toContract_dupaId(int id) {
	Disciplina disciplina = cautaDisciplina(id).at(0);
	addDisciplina_toContract(disciplina);
}



void Service::save_toHTMLService(string myFile) {
	repo.save_toHTML(myFile, contract);
}

ostream& operator<<(ostream& out, const ServiceException& ex) {
	out << ex.service_mess;
	return out;
}