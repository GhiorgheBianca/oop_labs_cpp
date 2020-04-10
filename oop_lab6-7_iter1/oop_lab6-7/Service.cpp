#include "Service.h"
#include <functional>
#include <algorithm>
#include <assert.h>

vector<Disciplina> Service::sorteaza(bool(*maiMicF)(const Disciplina&, const Disciplina&)) {
	vector<Disciplina> v{ repo.getDiscipline() }; // facem o copie
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

void Service::deleteDisciplinaService(const string& denumire, const string& cadru_didactic) {
	Disciplina disciplina{ denumire,1,"optionala",cadru_didactic };
	validator.validate(disciplina);
	repo.deleteDisciplina(disciplina);
}

vector<Disciplina> Service::sorteaza_dupa_durata() {
	auto copyAll = repo.getDiscipline();
	std::sort(copyAll.begin(), copyAll.end(), cmpNumarOre);
	return copyAll;
}

vector<Disciplina> Service::sorteaza_dupa_denumire() {
	return sorteaza(cmpDenumire);
}

vector<Disciplina> Service::sorteaza_dupa_profesor_tip() {
	return sorteaza([](const Disciplina& prima_disciplina, const Disciplina& a_doua_disciplina) {
		if (prima_disciplina.getCadruDidactic() == a_doua_disciplina.getCadruDidactic()) {
			return cmpTip(prima_disciplina, a_doua_disciplina);
		}
		return cmpCadruDidactic(prima_disciplina, a_doua_disciplina);
		});
}

vector<Disciplina> Service::filtreaza(function<bool(const Disciplina&)> fct) {
	vector<Disciplina> rez;
	for (const auto& disciplina : repo.getDiscipline()) {
		if (fct(disciplina)) {
			rez.push_back(disciplina);
		}
	}
	return rez;
}

vector<Disciplina> Service::filtrareCadruDidactic(const string& cadru_didactic) {
	return filtreaza([cadru_didactic](const Disciplina& disciplina) {
		return disciplina.getCadruDidactic() == cadru_didactic;
		});
}

vector<Disciplina> Service::filtrareDurata(int durataMin, int durataMax) {
	return filtreaza([=](const Disciplina& disciplina) {
		return disciplina.getOre() >= durataMin && disciplina.getOre() <= durataMax;
		});
}