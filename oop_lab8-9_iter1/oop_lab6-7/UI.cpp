#include "UI.h"
#include "Domain.h"
#include "Exceptions.h"

#include <iostream>
#include <string>
using namespace std;

void ConsolUI::tiparesteUI(const vector<Disciplina>& discipline) {
	cout << "\nDiscipline:\n";
	for (const auto& disciplina : discipline) {
		cout << ' ' << disciplina.getId() << ", " << disciplina.getDenumire() << ", " << disciplina.getOre() << " ore, " << disciplina.getTip() << ", " << disciplina.getCadruDidactic() << '\n';
	}
	cout << '\n' << '\n';
}

void ConsolUI::adaugaUI() {
	string denumire, tip, profesor;
	string primeste_durata;
	int durata;
	cout << "Dati denumire: ";
	getline(cin, denumire);
	cout << "Dati durata: ";
	getline(cin, primeste_durata);
	durata = stoi(primeste_durata, nullptr);
	cout << "Dati tipul: ";
	getline(cin, tip);
	cout << "Dati numele cadrului didactic: ";
	getline(cin, profesor);
	service.addDisciplinaService(denumire, durata, tip, profesor);
	cout << "Adaugat cu succes!\n\n\n";
}

void ConsolUI::modificaUI() {
	string denumire, tip, profesor;
	string primeste_nr;
	int durata, id;
	cout << "Dati id-ul disciplinei: ";
	getline(cin, primeste_nr);
	id = stoi(primeste_nr, nullptr);
	cout << "Dati denumire: ";
	getline(cin, denumire);
	cout << "Dati durata: ";
	getline(cin, primeste_nr);
	durata = stoi(primeste_nr, nullptr);
	cout << "Dati tipul: ";
	getline(cin, tip);
	cout << "Dati numele cadrului didactic: ";
	getline(cin, profesor);
	service.updateDisciplinaService(id, denumire, durata, tip, profesor);
	cout << "Modificat cu succes!\n\n\n";
}

void ConsolUI::stergeUI() {
	string primeste_id;
	int id;
	cout << "Dati id-ul disciplinei: ";
	getline(cin, primeste_id);
	id = stoi(primeste_id, nullptr);
	service.deleteDisciplinaService(id);
	cout << "Sters cu succes!\n\n\n";
}

void ConsolUI::filtreazaProfUI() {
	cout << "Dati numele profesorului: ";
	string profesor;
	getline(cin, profesor);
	tiparesteUI(service.filtrareCadruDidactic(profesor));
}

void ConsolUI::filtreazaDurataUI() {
	string citeste_nr;
	cout << "Dati durata minim: ";
	int durataMin;
	getline(cin, citeste_nr);
	durataMin = stoi(citeste_nr, nullptr);
	cout << "Dati durata maxim: ";
	int durataMax;
	getline(cin, citeste_nr);
	durataMax = stoi(citeste_nr, nullptr);
	tiparesteUI(service.filtrareDurata(durataMin, durataMax));
}

void ConsolUI::cautaDisciplinaUI() {
	string denumire, profesor;
	cout << "Dati denumire: ";
	getline(cin, denumire);
	cout << "Dati numele cadrului didactic: ";
	getline(cin, profesor);
	tiparesteUI(service.cautaDisciplina(denumire, profesor));
}

void ConsolUI::statsUI() {
	vector<DTO_statistics> DTO_stats = service.statsService();
	for (const auto& stats : DTO_stats) {
		cout << ' ' << stats.getTip() << ", " << stats.getFrecventa() << '\n';
	}
	cout << '\n' << '\n';
}

void ConsolUI::start() {
	while (true) {
		cout << "Meniu:\n";
		cout << "1. Adauga\n2. Tipareste\n3. Modifica\n4. Sterge\n5. Sorteaza dupa denumire\n6. Sorteaza dupa durata\n7. Sorteaza dupa cadru didactic + tip\n8. Filtreaza numele cadrului didactic\n9. Filtreaza durata\n10. Cauta dupa denumire si cadru didactic\n11. Statistici\n0. Iesire\nComanda: ";
		int cmd;
		try {
			cin >> cmd;
			cin.ignore();
			switch (cmd) {
			case 1:
				adaugaUI();
				break;
			case 2:
				tiparesteUI(service.getDiscipline());
				break;
			case 3:
				modificaUI();
				break;
			case 4:
				stergeUI();
				break;
			case 5:
				tiparesteUI(service.sorteaza_dupa_denumire());
				break;
			case 6:
				tiparesteUI(service.sorteaza_dupa_durata());
				break;
			case 7:
				tiparesteUI(service.sorteaza_dupa_profesor_tip());
				break;
			case 8:
				filtreazaProfUI();
				break;
			case 9:
				filtreazaDurataUI();
				break;
			case 10:
				cautaDisciplinaUI();
				break;
			case 11:
				statsUI();
				break;
			case 0:
				return;
			default:
				cout << "Comanda invalida!\n\n\n";
			}
		}
		catch (const RepoException & ex) {
			cout << ex << "\n\n\n";
		}
		catch (const ValidateException & ex) {
			cout << ex << "\n\n";
		}
		catch (exception) {
			cout << "Eroare la introducerea datelor!" << "\n\n\n";
		}
	}
}