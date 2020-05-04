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
	int durata = 0;
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
	int durata = 0, id = 0;
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
	int id = 0;
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
	string primeste_id;
	int id = 0;
	cout << "Dati id-ul disciplinei: ";
	getline(cin, primeste_id);
	id = stoi(primeste_id, nullptr);
	tiparesteUI(service.cautaDisciplina(id));
}

void ConsolUI::statsUI() {
	vector<DTO_statistics> DTO_stats = service.statsService();
	for (const auto& stats : DTO_stats) {
		cout << ' ' << stats.getTip() << " - " << stats.getFrecventa() << '\n';
	}
	cout << '\n' << '\n';
}

void ConsolUI::undoUI() {
	service.undo();
	tiparesteUI(service.getDiscipline());
}

void ConsolUI::golesteContractUI() {
	service.golesteContract();
	cout << "Numarul total al disciplinelor din contract: " << service.totalDiscipline_dinContract() << "\n\n\n";
}

void ConsolUI::adauga_inContractUI() {
	string primeste_id;
	int id = 0;
	cout << "Dati id-ul disciplinei: ";
	getline(cin, primeste_id);
	id = stoi(primeste_id, nullptr);

	service.add_toContract_dupaId(id);
	cout << "Numarul total al disciplinelor din contract: " << service.totalDiscipline_dinContract() << "\n\n\n";
}

void ConsolUI::adaugaRandom_inContractUI() {
	string primeste_nr;
	int nr_total = 0;
	cout << "Dati numarul disciplinelor: ";
	getline(cin, primeste_nr);
	nr_total = stoi(primeste_nr, nullptr);

	service.addRandom_toContract(nr_total);
	cout << "Numarul total al disciplinelor din contract: " << service.totalDiscipline_dinContract() << "\n\n\n";
}

void ConsolUI::salveaza_inHTMLUI() {
	cout << "Dati numele fisierului unde va fi salvat contractul: ";
	string my_Filename;
	getline(cin, my_Filename);
	my_Filename = my_Filename + ".html";

	service.save_toHTMLService(my_Filename);
	cout << "Numarul total al disciplinelor din contract: " << service.totalDiscipline_dinContract() << "\n\n\n";
}

void ConsolUI::start() {
	while (true) {
		cout << "Meniu:\n";
		cout << "1. Adauga\n2. Tipareste\n3. Modifica\n4. Sterge\n5. Sorteaza dupa denumire\n6. Sorteaza dupa durata\n7. Sorteaza dupa cadru didactic + tip\n8. Filtreaza numele cadrului didactic\n9. Filtreaza durata\n10. Cauta dupa denumire si cadru didactic\n11. Statistici\n12. Undo\n13. Goleste contractul\n14. Adauga in contract dupa id\n15. Genereaza contract\n16. Salveaza contractul in fisier\n0. Iesire\nComanda: ";
		int cmd = 0;
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
			case 12:
				undoUI();
				break;
			case 13:
				golesteContractUI();
				break;
			case 14:
				adauga_inContractUI();
				break;
			case 15:
				adaugaRandom_inContractUI();
				break;
			case 16:
				salveaza_inHTMLUI();
				break;
			case 0:
				return;
			default:
				cout << "Comanda invalida!\n\n\n";
			}
		}
		catch (const ServiceException & ex) {
			cout << ex << "\n\n\n";
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