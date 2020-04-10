#include "UI.h"
#include "Domain.h"

#include <iostream>
#include <string>

using std::cout;
using std::cin;

void ConsolUI::tiparesteUI(const vector<Disciplina>& discipline) {
	cout << "\nDiscipline:\n";
	for (const auto& disciplina : discipline) {
		cout << ' ' << disciplina.getDenumire() << ", " << disciplina.getOre() << " ore, " << disciplina.getTip() << ", " << disciplina.getCadruDidactic() << '\n';
	}
	cout << '\n' << '\n';
}

void ConsolUI::adaugaUI() {
	string denumire, tip, profesor;
	char primeste_durata[50];
	int durata;
	cout << "Dati denumire: ";
	cin >> denumire;
	cout << "Dati durata: ";
	cin >> primeste_durata;
	durata = atoi(primeste_durata);
	cout << "Dati tipul: ";
	cin >> tip;
	cout << "Dati numele cadrului didactic: ";
	cin >> profesor;
	service.addDisciplinaService(denumire, durata, tip, profesor);
	cout << "Adaugat cu succes!\n\n\n";
}

void ConsolUI::stergeUI() {
	string denumire, profesor;
	cout << "Dati denumire: ";
	cin >> denumire;
	cout << "Dati numele cadrului didactic: ";
	cin >> profesor;
	service.deleteDisciplinaService(denumire, profesor);
	cout << "Sters cu succes!\n\n\n";
}

void ConsolUI::filtreazaProfUI() {
	cout << "Dati numele profesorului: ";
	string profesor;
	cin >> profesor;
	tiparesteUI(service.filtrareCadruDidactic(profesor));
}

void ConsolUI::filtreazaDurataUI() {
	char citeste_nr[50];
	cout << "Dati durata minim: ";
	int durataMin;
	cin >> citeste_nr;
	durataMin = atoi(citeste_nr);
	cout << "Dati durata maxim: ";
	int durataMax;
	cin >> citeste_nr;
	durataMax = atoi(citeste_nr);
	tiparesteUI(service.filtrareDurata(durataMin, durataMax));
}

void ConsolUI::start() {
	while (true) {
		cout << "Meniu:\n";
		cout << "1. Adauga\n2. Tipareste\n3. Modifica\n4. Sterge\n5. Sorteaza dupa denumire\n6. Sorteaza dupa durata\n7. Sorteaza dupa cadru didactic + tip\n8. Filtreaza numele cadrului didactic\n9. Filtreaza durata\n0. Iesire\nComanda: ";
		int cmd;
		char citeste_nr[50];
		cin >> citeste_nr;
		cmd = atoi(citeste_nr);
		try {
			switch (cmd) {
			case 1:
				adaugaUI();
				break;
			case 2:
				tiparesteUI(service.getDiscipline());
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
	}
}