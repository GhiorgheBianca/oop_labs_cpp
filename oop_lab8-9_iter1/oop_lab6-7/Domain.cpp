#include "Domain.h"

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