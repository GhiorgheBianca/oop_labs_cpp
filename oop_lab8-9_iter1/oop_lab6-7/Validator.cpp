#include "Validator.h"
#include "Exceptions.h"
#include <assert.h>
#include <sstream>

void Validator::validate(const Disciplina& disciplina) {
	vector<string> errors;
	if (disciplina.getId() <= 0)
		errors.push_back("Id-ul este invalid!");
	if (disciplina.getOre() <= 0) 
		errors.push_back("Numarul de ore este invalid!");
	if (disciplina.getDenumire().size() == 0) 
		errors.push_back("Denumirea nu poate fi vida!");
	if (disciplina.getTip().size() == 0) 
		errors.push_back("Tipul nu poate fi vid!");
	if (disciplina.getTip() != "obligatorie" && disciplina.getTip() != "optionala" && disciplina.getTip() != "facultativa")
		errors.push_back("Tipul poate fi doar obligatorie, optionala sau facultativa!");
	if (disciplina.getCadruDidactic().size() == 0)
		errors.push_back("Numele cadrului didactic nu poate fi vid!");
	if (errors.size() > 0) {
		throw ValidateException(errors);
	}
}

ostream& operator<<(ostream& out, const ValidateException& ex) {
	for (const auto& msg : ex.messages) {
		out << msg << "\n";
	}
	return out;
}