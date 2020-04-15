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
	discipline.insert({ disciplina.getId(),disciplina });
}

void Repository::updateDisciplina(Disciplina disciplina) {
	if (!exist(disciplina)) {
		throw RepoException("Nu exista disciplina cu denumirea: " + disciplina.getDenumire() + " si cadrul didactic: " + disciplina.getCadruDidactic());
	}
	discipline.at(disciplina.getId()) = disciplina;
}

void Repository::deleteDisciplina(const Disciplina& disciplina) {
	if (!exist(disciplina)) {
		throw RepoException("Nu exista disciplina cu denumirea: " + disciplina.getDenumire() + " si cadrul didactic: " + disciplina.getCadruDidactic());
	}
	discipline.erase(disciplina.getId());
}

bool Repository::exist(const Disciplina& disciplina) const {
	try {
		findDisciplina(disciplina.getId());
		return true;
	}
	catch (RepoException&) {
		return false;
	}
}

const Disciplina& Repository::findDisciplina(int id) const {
	if (discipline.find(id) != discipline.end()) {
		return discipline.at(id);
	}
	throw RepoException("Nu exista o disciplina cu id-ul: " + id);
}

/*
void Repository::addContract(const vector<Disciplina>& disciplinele, int id) {
	if (disciplinele.size() == 0) {
		throw RepoException("Nu exista discipline pentru inserare!");
	}
	Contract contract{ disciplinele,id };
	contracte.push_back(contract);
}

vector<Disciplina> Repository::getContract(int id) {
	size_t const contor = getContractPosition(id);
	if (contracte.size() == contor)
		throw RepoException("Nu exista un contract cu id-ul: " + id);
	return contracte.at(contor).getDiscipline_dinContract();
}

void Repository::golesteDiscipline() {
	int constexpr id = 0;
	while (discipline.size() != 0) {
		deleteDisciplina(discipline.at(id));
	}
}

void Repository::golesteContract(int id) {
	golesteDiscipline();
	updateContrat(id);
}

void Repository::stergeContract(int id) {
	size_t const contor = getContractPosition(id);
	if (contor == contracte.size())
		throw RepoException("Nu exista un contract cu id-ul: " + id);
	contracte.erase(contracte.begin() + contor);
}

void Repository::setDiscipline_dinContract(int id) {
	discipline = getContract(id);
}

size_t Repository::getContractPosition(int id) const noexcept {
	size_t contor = 0;
	for (auto contract : contracte)
		if (contract.getIdContract() == id)
			break;
		else
			contor++;
	return contor;
}

void Repository::updateContrat(int id) {
	size_t const contor = getContractPosition(id);
	if (contracte.size() == contor)
		throw RepoException("Nu exista un contract cu id-ul: " + id);
	contracte.at(contor).setDiscipline_dinContract(discipline);
}
*/

ostream& operator<<(ostream& out, const RepoException& ex) {
	out << ex.message;
	return out;
}