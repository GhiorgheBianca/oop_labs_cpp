#include "Repository.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <random>

using std::ostream;
using std::stringstream;

void Repository::addDisciplina(const Disciplina& disciplina) {
	double f = (double)rand() / RAND_MAX;
	double err_prob = f;
	if (err_prob < error_probability) {
		throw RepoException("Eroare random!!!");
	}

	if (exist(disciplina, discipline)) {
		throw RepoException("Exista deja o disciplina cu denumirea: " + disciplina.getDenumire() + " si cadrul didactic: " + disciplina.getCadruDidactic());
	}
	discipline.push_back(disciplina);
}

void Repository::updateDisciplina(Disciplina disciplina) {
	double f = (double)rand() / RAND_MAX;
	double err_prob = f;
	if (err_prob < error_probability) {
		throw RepoException("Eroare random!!!");
	}

	if (!exist(disciplina, discipline)) {
		throw RepoException("Nu exista disciplina cu denumirea: " + disciplina.getDenumire() + " si cadrul didactic: " + disciplina.getCadruDidactic());
	}
	int contor = findPosition(disciplina.getId(), discipline);
	discipline.at(contor) = disciplina;
}

void Repository::deleteDisciplina(const Disciplina& disciplina) {
	double f = (double)rand() / RAND_MAX;
	double err_prob = f;
	if (err_prob < error_probability) {
		throw RepoException("Eroare random!!!");
	}

	if (!exist(disciplina, discipline)) {
		throw RepoException("Nu exista disciplina cu id-ul: " + std::to_string(disciplina.getId()));
	}
	int contor = findPosition(disciplina.getId(), discipline);
	discipline.erase(discipline.begin() + contor);
}

bool Repository::exist(const Disciplina& disciplina, const vector<Disciplina>& disciplinele) const {
	try {
		findPosition(disciplina.getId(), disciplinele);
		return true;
	}
	catch (RepoException&) {
		return false;
	}
}

int Repository::findPosition(int id, const vector<Disciplina>& disciplinele) const {
	int contor = 0;
	for (const auto& disciplina : disciplinele) {
		if (disciplina.getId() == id) {
			return contor;
		}
		else {
			contor++;
		}
	}
	throw RepoException("Nu exista o disciplina cu id-ul: " + std::to_string(id));
}

void Repository::deleteDisciplina_fromContract(const Disciplina& disciplina, Contract& contract) {
	double f = (double)rand() / RAND_MAX;
	double err_prob = f;
	if (err_prob < error_probability) {
		throw RepoException("Eroare random!!!");
	}
	
	int contor = findPosition(disciplina.getId(), contract.getDiscipline_dinContract());
	contract.erase(contor);
}

void RepoFile::loadFromFile() {
	std::ifstream in(fileName);
	// verify if the stream is open
	if (!in.is_open()) {
		throw RepoException("Unable to open file: " + fileName);
	}
	else {
		string line;
		while (getline(in, line))
		{
			string delimiter = ",";
			size_t pos = 0;
			string element_nr;

			string denumire, tip, profesor;
			int id = 0, durata = 0;

			// citirea id-ului
			pos = line.find(delimiter);
			element_nr = line.substr(0, pos);
			id = stoi(element_nr, nullptr);
			line.erase(0, pos + delimiter.length());
			///

			// citirea denumirii
			pos = line.find(delimiter);
			denumire = line.substr(0, pos);
			line.erase(0, pos + delimiter.length());
			///

			// citirea duratei
			pos = line.find(delimiter);
			element_nr = line.substr(0, pos);
			durata = stoi(element_nr, nullptr);
			line.erase(0, pos + delimiter.length());
			///

			// citirea tipului
			pos = line.find(delimiter);
			tip = line.substr(0, pos);
			line.erase(0, pos + delimiter.length());
			///

			// citirea cadrului didactic
			pos = line.find(delimiter);
			profesor = line.substr(0, pos);
			line.erase(0, pos + delimiter.length());
			///

			Disciplina disciplina{ id,denumire.c_str(),durata,tip.c_str(),profesor.c_str() };
			discipline.push_back(disciplina);
		}

		in.close();
	}
}

void RepoFile::writeToFile(const vector<Disciplina>& disciplinele) {
	std::ofstream out(fileName);
	for (auto& disciplina : disciplinele) {
		out << disciplina.getId() << ",";
		out << disciplina.getDenumire() << ",";
		out << disciplina.getOre() << ",";
		out << disciplina.getTip() << ",";
		out << disciplina.getCadruDidactic() << "\n";
	}
	out.close();
}

void RepoFile::deleteFileContent() {
	double f = (double)rand() / RAND_MAX;
	double err_prob = f;
	if (err_prob < error_probability) {
		throw RepoException("Eroare random!!!");
	}

	std::ofstream ofs;
	ofs.open(fileName, std::ofstream::out | std::ofstream::trunc);
	ofs.close();
}

void Repository::save_toHTML(string myFile, Contract contractul) {
	RepoFile repoF{ myFile,contractul };
}

ostream& operator<<(ostream& out, const RepoException& ex) {
	out << ex.message;
	return out;
}