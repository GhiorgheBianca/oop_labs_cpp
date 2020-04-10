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

/*
	Folosit pentru a semnala datele care nu indeplinesc conditiile necesare obiectului de tip Disciplina.
*/
class ValidateException {
	vector<string> messages;

public:
	ValidateException(const vector<string>& errors) :messages{ errors } {}
	// functie friend (vreau sa folosesc membru privat msg)
	friend ostream& operator<<(ostream& out, const ValidateException& ex);

};

ostream& operator<<(ostream& out, const ValidateException& ex);