#include "Repository.h"
#include "Exceptions.h"
#include <iostream>
#include <sstream>

using std::ostream;
using std::stringstream;

void Repository::addDisciplina(const Disciplina& disciplina) {
	if (exist(disciplina)) {
		throw RepoException("Exista deja o disciplina cu denumirea: " + disciplina.getDenumire() + " si cadrul didactic: " + disciplina.getCadruDidactic());
	}
	discipline.push_back(disciplina);
}

void Repository::updateDisciplina(Disciplina disciplina) {
	if (!exist(disciplina)) {
		throw RepoException("Nu exista disciplina cu denumirea: " + disciplina.getDenumire() + " si cadrul didactic: " + disciplina.getCadruDidactic());
	}
	int contor = findPosition(disciplina.getDenumire(), disciplina.getCadruDidactic());
	discipline.update(disciplina, contor);
}

void Repository::deleteDisciplina(const Disciplina& disciplina) {
	if (!exist(disciplina)) {
		throw RepoException("Nu exista disciplina cu denumirea: " + disciplina.getDenumire() + " si cadrul didactic: " + disciplina.getCadruDidactic());
	}
	int contor = findPosition(disciplina.getDenumire(), disciplina.getCadruDidactic());
	discipline.erase(contor);
}

bool Repository::exist(const Disciplina& disciplina) const {
	try {
		findPosition(disciplina.getDenumire(), disciplina.getCadruDidactic());
		return true;
	}
	catch (RepoException&) {
		return false;
	}
}

int Repository::findPosition(const std::string& denumire, const std::string& cadru_didactic) const {
	int contor = 0;
	for (const auto& disciplina : discipline) {
		if (disciplina.getDenumire() == denumire && disciplina.getCadruDidactic() == cadru_didactic) {
			return contor;
		}
		else {
			contor++;
		}
	}
	throw RepoException("Nu exista o disciplina cu denumirea: " + denumire + " si cadrul didactic: " + cadru_didactic);
}

const Disciplina& Repository::findDisciplina(const std::string& denumire, const std::string& cadru_didactic) const {
	for (const auto& disciplina : discipline) {
		if (disciplina.getDenumire() == denumire && disciplina.getCadruDidactic() == cadru_didactic) {
			return disciplina;
		}
	}
	throw RepoException("Nu exista o disciplina cu denumirea: " + denumire + " si cadrul didactic: " + cadru_didactic);
}

ostream& operator<<(ostream& out, const RepoException& ex) {
	out << ex.message;
	return out;
}