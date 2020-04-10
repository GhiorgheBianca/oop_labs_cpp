#include "Domain.h"

Disciplina::Disciplina(const std::string& denumire, int ore_pe_saptamana, const std::string& tip, const std::string& cadru_didactic) {
	this->denumire = denumire;
	this->ore_pe_saptamana = ore_pe_saptamana;
	this->tip = tip;
	this->cadru_didactic = cadru_didactic;
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

void DTO_statistics::inc_frecventa(DTO_statistics& stats) {
	stats.frecventa++;
}