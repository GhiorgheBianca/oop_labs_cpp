#pragma once

#include "Domain.h"
#include <string>
#include <vector>

using std::vector;
using std::string;
using std::ostream;

class Validator {
public:
	/*
		Functia de validare. Verifica datele Disciplinei pentru a se asigura ca sunt corecte.
		Input: disciplina - obiect de tip Disciplina;
		Output: arunca exceptie daca cel putin una dintre date nu este corecta;
	*/
	void validate(const Disciplina& disciplina);

};