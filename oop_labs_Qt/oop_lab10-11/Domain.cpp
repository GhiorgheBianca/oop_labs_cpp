#include "Domain.h"

vector<Disciplina> Contract::getDiscipline_dinContract() {
	return discipline;
}

void Contract::push_backContract(const Disciplina& disciplina) {
	discipline.push_back(disciplina);
}

void Contract::erase(int position) {
	discipline.erase(discipline.begin() + position);
}

void Contract::clearContract() {
	discipline.clear();
}

bool cmpDenumire(const Disciplina& prima_disciplina, const Disciplina& a_doua_disciplina) {
	return prima_disciplina.getDenumire() < a_doua_disciplina.getDenumire();
}

bool cmpTip(const Disciplina& prima_disciplina, const Disciplina& a_doua_disciplina) {
	return prima_disciplina.getTip() < a_doua_disciplina.getTip();
}

bool cmpCadruDidactic(const Disciplina& prima_disciplina, const Disciplina& a_doua_disciplina) {
	return prima_disciplina.getCadruDidactic() < a_doua_disciplina.getCadruDidactic();
}

void DTO_statistics::inc_frecventa(DTO_statistics& stats) noexcept {
	stats.frecventa++;
}