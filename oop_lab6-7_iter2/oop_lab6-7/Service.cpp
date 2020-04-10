#include "Service.h"
#include <functional>
#include <algorithm>
#include <assert.h>

#include <vector>
#include <unordered_map>

Lista<Disciplina> Service::sorteaza(bool(*maiMicF)(const Disciplina&, const Disciplina&)) {
	Lista<Disciplina> v{ repo.getDiscipline() }; // facem o copie
	for (size_t i = 0; i < v.size(); i++) {
		for (size_t j = i + 1; j < v.size(); j++) {
			if (!maiMicF(v[i], v[j])) {
				Disciplina aux = v[i];
				v[i] = v[j];
				v[j] = aux;
			}
		}
	}
	return v;
}

void Service::addDisciplinaService(const string& denumire, int ore_pe_saptamana, const string& tip, const string& cadru_didactic) {
	Disciplina disciplina{ denumire,ore_pe_saptamana,tip,cadru_didactic };
	validator.validate(disciplina);
	repo.addDisciplina(disciplina);
}

void Service::updateDisciplinaService(const string& denumire, int ore_pe_saptamana, const string& tip, const string& cadru_didactic) {
	Disciplina disciplina{ denumire,ore_pe_saptamana,tip,cadru_didactic };
	validator.validate(disciplina);
	repo.updateDisciplina(disciplina);
}

void Service::deleteDisciplinaService(const string& denumire, const string& cadru_didactic) {
	Disciplina disciplina{ denumire,1,"optionala",cadru_didactic };
	validator.validate(disciplina);
	repo.deleteDisciplina(disciplina);
}

Lista<Disciplina> Service::sorteaza_dupa_durata() {
	return sorteaza([](const Disciplina& prima_disciplina, const Disciplina& a_doua_disciplina) {
		return prima_disciplina.getOre() < a_doua_disciplina.getOre();
		});
}

Lista<Disciplina> Service::sorteaza_dupa_denumire() {
	return sorteaza(cmpDenumire);
}

Lista<Disciplina> Service::sorteaza_dupa_profesor_tip() {
	return sorteaza([](const Disciplina& prima_disciplina, const Disciplina& a_doua_disciplina) {
		if (prima_disciplina.getCadruDidactic() == a_doua_disciplina.getCadruDidactic()) {
			return cmpTip(prima_disciplina, a_doua_disciplina);
		}
		return cmpCadruDidactic(prima_disciplina, a_doua_disciplina);
		});
}

Lista<Disciplina> Service::filtreaza(function<bool(const Disciplina&)> fct) {
	Lista<Disciplina> rez;
	for (const auto& disciplina : repo.getDiscipline()) {
		if (fct(disciplina)) {
			rez.push_back(disciplina);
		}
	}
	return rez;
}

Lista<Disciplina> Service::filtrareCadruDidactic(const string& cadru_didactic) {
	return filtreaza([cadru_didactic](const Disciplina& disciplina) {
		return disciplina.getCadruDidactic() == cadru_didactic;
		});
}

Lista<Disciplina> Service::filtrareDurata(int durataMin, int durataMax) {
	return filtreaza([=](const Disciplina& disciplina) {
		return disciplina.getOre() >= durataMin && disciplina.getOre() <= durataMax;
		});
}

Lista<Disciplina> Service::cautaDisciplina(const string& denumire, const string& profesor) {
	Lista<Disciplina> rez;
	rez.push_back(repo.findDisciplina(denumire, profesor));
	return rez;
}

vector<DTO_statistics> Service::statsService() const {
	Lista<Disciplina> discipline = repo.getDiscipline();
	vector<DTO_statistics> DTO_stats;
	unordered_map<string, DTO_statistics> my_map;

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