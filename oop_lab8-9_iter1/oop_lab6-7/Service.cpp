#include "Service.h"
#include <algorithm> //=> sort, copy_if, transform

#include <vector>
#include <unordered_map>
#include <numeric> //=> accumulate

void Service::addDisciplinaService(const string& denumire, int ore_pe_saptamana, const string& tip, const string& cadru_didactic) {
	int id = static_cast<int>(repo.getDiscipline().size()) + 1;
	Disciplina disciplina{ id,denumire,ore_pe_saptamana,tip,cadru_didactic };
	validator.validate(disciplina);
	repo.addDisciplina(disciplina);
}

void Service::updateDisciplinaService(int id, const string& denumire, int ore_pe_saptamana, const string& tip, const string& cadru_didactic) {
	Disciplina disciplina{ id,denumire,ore_pe_saptamana,tip,cadru_didactic };
	validator.validate(disciplina);
	repo.updateDisciplina(disciplina);
}

void Service::deleteDisciplinaService(int id) {
	Disciplina disciplina{ id,"denumire",1,"optionala","cadru_didactic" };
	validator.validate(disciplina);
	repo.deleteDisciplina(disciplina);
}

vector<Disciplina> Service::sorteaza_dupa_durata() {
	auto copyAll = getDiscipline();
	std::sort(copyAll.begin(), copyAll.end(), [](const Disciplina& prima_disciplina, const Disciplina& a_doua_disciplina) noexcept {
		return prima_disciplina.getOre() < a_doua_disciplina.getOre();
		});
	return copyAll;
}

vector<Disciplina> Service::sorteaza_dupa_denumire() {
	auto copyAll = getDiscipline();
	std::sort(copyAll.begin(), copyAll.end(), cmpDenumire);
	return copyAll;
}

vector<Disciplina> Service::sorteaza_dupa_profesor_tip() {
	vector<Disciplina> copyAll = getDiscipline();
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
	vector<Disciplina> copyAll = getDiscipline();
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

vector<Disciplina> Service::cautaDisciplina(const string& denumire, const string& profesor) {
	vector<Disciplina> rez;
	vector<Disciplina> copyAll = getDiscipline();
	auto get_disciplina = std::find_if(copyAll.begin(), copyAll.end(), [denumire, profesor](const Disciplina& disciplina) {
		return disciplina.getDenumire() == denumire && disciplina.getCadruDidactic() == profesor;
		});
	if (get_disciplina != copyAll.end())
		rez.push_back(*get_disciplina);
	return rez;
}

vector<Disciplina> Service::getDiscipline() noexcept {
	auto disciplinele = repo.getDiscipline();
	vector<Disciplina> vector_discipline;
	std::transform(disciplinele.begin(), disciplinele.end(), back_inserter(vector_discipline), [](std::pair<int, Disciplina> repo) {
		return repo.second;
		});

	return vector_discipline;
}

const int Service::totalOreDiscipline() {
	vector<Disciplina> vector_discipline = getDiscipline();
	int contor = accumulate(vector_discipline.begin(), vector_discipline.end(), 0, [](int total, const Disciplina& disciplina) {
		return total + disciplina.getOre(); });
	return contor;
}

vector<DTO_statistics> Service::statsService() const {
	auto discipline = repo.getDiscipline();
	vector<DTO_statistics> DTO_stats;
	unordered_map<string, DTO_statistics> my_map;

	for (const auto& disciplina : discipline) {
		if (my_map.find(disciplina.second.getTip()) == my_map.end())
		{
			DTO_statistics new_DTO{ disciplina.second.getTip(),1 };
			my_map.insert({ disciplina.second.getTip(),new_DTO });
		}
		else {
			my_map.at(disciplina.second.getTip()).inc_frecventa(my_map.at(disciplina.second.getTip()));
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