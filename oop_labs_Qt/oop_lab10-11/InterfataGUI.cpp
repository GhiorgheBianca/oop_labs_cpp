#include "InterfataGUI.h"
#include <qpushbutton.h>
#include <qcombobox.h>
#include <qtabwidget.h>

void InterfataGUI::curata_txt() {
	txtId->setText("");
	txtDenumire->setText("");
	txtDurata->setText("");
	txtTip->setText("");
	txtProfesor->setText("");
}

void InterfataGUI::initGUICmps() {
	setLayout(lyMain);

	QWidget* widDreapta = new QWidget;
	QVBoxLayout* vl = new QVBoxLayout;
	widDreapta->setLayout(vl);
	lstDiscipline = new QListWidget;
	lstContract = new QListWidget;

	QTabWidget* tabs = new QTabWidget;
	QWidget* widTabDiscipline = new QWidget;
	QVBoxLayout* listLayoutDiscipline = new QVBoxLayout;
	widTabDiscipline->setLayout(listLayoutDiscipline);
	listLayoutDiscipline->addWidget(lstDiscipline);
	tabs->addTab(widTabDiscipline, "Discipline");

	QWidget* widTabContract = new QWidget;
	QVBoxLayout* listLayoutContract = new QVBoxLayout;
	widTabContract->setLayout(listLayoutContract);
	listLayoutContract->addWidget(lstContract);
	tabs->addTab(widTabContract, "Contract");

	vl->addWidget(tabs);

	QWidget* widBtnDreapta = new QWidget;
	QGridLayout* lyBtnsDr = new QGridLayout;
	widBtnDreapta->setLayout(lyBtnsDr);

	comboBoxSort = new QComboBox;
	comboBoxSort->addItem("Alege modul de sortare");
	comboBoxSort->addItem("Sorteaza dupa denumire");
	comboBoxSort->addItem("Sorteaza dupa durata");
	comboBoxSort->addItem("Sorteaza dupa profesor si tip");
	lyBtnsDr->addWidget(comboBoxSort, 0, 0);

	comboBoxFilter = new QComboBox;
	comboBoxFilter->addItem("Alege modul de filtrare");
	comboBoxFilter->addItem("Sorteaza dupa profesor");
	comboBoxFilter->addItem("Sorteaza dupa durata");
	lyBtnsDr->addWidget(comboBoxFilter, 0, 1);

	radioBtnStats = new QRadioButton("Statistici");
	lyBtnsDr->addWidget(radioBtnStats, 1, 0);
	labelStats = new QLabel;
	lyBtnsDr->addWidget(labelStats, 1, 1);

	QLabel* txtNr_dinContract = new QLabel("Numarul total al disciplinelor din contract: ");
	lyBtnsDr->addWidget(txtNr_dinContract, 2, 0);
	labelNrDiscipline_dinContract = new QLabel("0");
	lyBtnsDr->addWidget(labelNrDiscipline_dinContract, 2, 1);

	vl->addWidget(widBtnDreapta);
	lyMain->addWidget(widDreapta);

	QWidget* widDetalii = new QWidget;
	QFormLayout* formLDetalii = new QFormLayout;
	widDetalii->setLayout(formLDetalii);
	txtId = new QLineEdit;
	txtDenumire = new QLineEdit;
	txtDurata = new QLineEdit;
	txtTip = new QLineEdit;
	txtProfesor = new QLineEdit;
	txt_n = new QLineEdit;
	formLDetalii->addRow("Id", txtId);
	formLDetalii->addRow("Denumire", txtDenumire);
	formLDetalii->addRow("Durata", txtDurata);
	formLDetalii->addRow("Tip", txtTip);
	formLDetalii->addRow("Profesor", txtProfesor);
	formLDetalii->addRow("n = ", txt_n);
	vl->addLayout(formLDetalii);

	QLabel* optiuneDiscipline = new QLabel("Optiuni discipline:");
	optiuneDiscipline->setStyleSheet("QLabel { font : 10pt; color : green; }");
	formLDetalii->addWidget(optiuneDiscipline);

	btnAdd = new QPushButton("Adauga disciplina");
	formLDetalii->addWidget(btnAdd);

	btnUpdate = new QPushButton("Actualizeaza disciplina");
	formLDetalii->addWidget(btnUpdate);

	btnDelete = new QPushButton("Sterge disciplina");
	formLDetalii->addWidget(btnDelete);

	btnUndo = new QPushButton("Reface ultima operatie");
	formLDetalii->addWidget(btnUndo);

	QLabel* optiuneContract = new QLabel("Optiuni contract:");
	optiuneContract->setStyleSheet("QLabel { font : 10pt; color : blue; }");
	formLDetalii->addWidget(optiuneContract);

	btnGolesteContract = new QPushButton("Goleste contractul");
	formLDetalii->addWidget(btnGolesteContract);

	btnAddContr_id = new QPushButton("Adauga in contract dupa id");
	formLDetalii->addWidget(btnAddContr_id);

	btnGenerareContract = new QPushButton("Genereaza contract cu <n> discipline");
	formLDetalii->addWidget(btnGenerareContract);

	btnSalv_html = new QPushButton("Salveaza contractul in fisierul <n>");
	formLDetalii->addWidget(btnSalv_html);

	btnExit = new QPushButton("Iesire");
	formLDetalii->addWidget(btnExit);

	lyMain->addWidget(widDetalii);

	widDiscipline = new QWidget;
	btnsDisciplineLayout = new QVBoxLayout;
	init_btnsDiscipline(service.getDiscipline());
}

void InterfataGUI::delete_btnsDiscipline() {
	for (auto& buton : butoaneDiscipline) {
		delete buton;
	}
	butoaneDiscipline.clear();
}

void InterfataGUI::init_btnsDiscipline(const vector<Disciplina>& discipline) {
	setLayout(lyMain);
	widDiscipline->setLayout(btnsDisciplineLayout);

	butoaneDiscipline.clear();
	for (const auto& disciplina : discipline) {
		QPushButton* button = new QPushButton;
		butoaneDiscipline.push_back(button);
		button->setText(QString::number(disciplina.getId()));
		btnsDisciplineLayout->addWidget(button);

		QObject::connect(button, &QPushButton::clicked, [&]() {
			auto disc = service.cautaDisciplina(disciplina.getId());
			service.deleteDisciplinaService(disc.at(0).getId(), disc.at(0).getDenumire(), disc.at(0).getOre(), disc.at(0).getTip(), disc.at(0).getCadruDidactic());
			reloadList(service.getDiscipline(), "discipline");

			//curatam textul daca s-a reusit introducerea datelor in lista
			curata_txt();

			delete_btnsDiscipline();
			init_btnsDiscipline(service.getDiscipline());
			});
	}

	lyMain->addWidget(widDiscipline);
	//lyMain->removeWidget(widLayout);
}

void InterfataGUI::connectSignalsSlots() {
	//cand se emite semnalul clicked de pe butonul Exit, se iese din program
	QObject::connect(btnExit, &QPushButton::clicked, [&]() {
		close();
		});

	//cand se selecteaza o optiune din combo box, se executa sortarea aleasa
	QObject::connect(comboBoxSort, QOverload<int>::of(&QComboBox::currentIndexChanged),
		[=](int index) {
			vector<Disciplina> discipline_sortate;
			if (index == 0) {
				discipline_sortate = service.getDiscipline();
				reloadList(discipline_sortate, "discipline");
			}
			else if (index == 1) {
				discipline_sortate = service.sorteaza_dupa_denumire();
				reloadList(discipline_sortate, "discipline");
			}
			else if (index == 2) {
				discipline_sortate = service.sorteaza_dupa_durata();
				reloadList(discipline_sortate, "discipline");
			}
			else if (index == 3) {
				discipline_sortate = service.sorteaza_dupa_profesor_tip();
				reloadList(discipline_sortate, "discipline");
			}

			delete_btnsDiscipline();
			init_btnsDiscipline(discipline_sortate);
		});

	//cand se selecteaza o optiune din combo box, se executa filtrul ales
	QObject::connect(comboBoxFilter, QOverload<int>::of(&QComboBox::currentIndexChanged),
		[=](int index) {
			vector<Disciplina> discipline_filtrate;
			if (index == 0) {
				discipline_filtrate = service.getDiscipline();
				reloadList(discipline_filtrate, "discipline");
			}
			else if (index == 1) {
				discipline_filtrate = service.filtrareCadruDidactic(txtProfesor->text().toStdString());
				reloadList(discipline_filtrate, "discipline");
			}
			else if (index == 2) {
				discipline_filtrate = service.filtrareDurata(txtDurata->text().toInt(), txtDurata->text().toInt());
				reloadList(discipline_filtrate, "discipline");
			}

			delete_btnsDiscipline();
			init_btnsDiscipline(discipline_filtrate);
		});

	//cand se emite semnalul clicked de pe buton, adaug in lista o disciplina noua
	QObject::connect(btnAdd, &QPushButton::clicked, this, &InterfataGUI::addNewDiscipline);

	//cand se emite semnalul clicked de pe buton, actualizeaza in lista o disciplina
	QObject::connect(btnUpdate, &QPushButton::clicked, this, &InterfataGUI::updateDiscipline);

	//cand se emite semnalul clicked de pe buton, sterge din lista o disciplina
	QObject::connect(btnDelete, &QPushButton::clicked, this, &InterfataGUI::deleteDiscipline);

	//cand se emite semnalul clicked de pe buton, se reface ultima operatie
	QObject::connect(btnUndo, &QPushButton::clicked, this, &InterfataGUI::undoDiscipline);

	//cand se selecteaza o linie din lista, se completeaza casutele text
	QObject::connect(lstDiscipline, &QListWidget::itemSelectionChanged, [&]() {
		auto selected_elem = lstDiscipline->selectedItems();
		if (selected_elem.isEmpty()) {
			curata_txt();
		}
		else {
			auto selectedItem = selected_elem.at(0);
			selectedItem->setBackground(QBrush{ Qt::green, Qt::SolidPattern });
			auto id = selectedItem->data(Qt::UserRole).toInt();
			auto disc = service.cautaDisciplina(id);
			txtId->setText(QString::number(disc.at(0).getId()));
			txtDenumire->setText(QString::fromStdString(disc.at(0).getDenumire()));
			txtDurata->setText(QString::number(disc.at(0).getOre()));
			txtTip->setText(QString::fromStdString(disc.at(0).getTip()));
			txtProfesor->setText(QString::fromStdString(disc.at(0).getCadruDidactic()));
		}
		});

	//cand se selecteaza o linie din lista, se completeaza casutele text
	QObject::connect(lstContract, &QListWidget::itemSelectionChanged, [&]() {
		auto selected_elem = lstContract->selectedItems();
		if (selected_elem.isEmpty()) {
			curata_txt();
		}
		else {
			auto selectedItem = selected_elem.at(0);
			selectedItem->setBackground(QBrush{ Qt::blue, Qt::SolidPattern });
			auto id = selectedItem->data(Qt::UserRole).toInt();
			auto disc = service.cautaDisciplina(id);
			txtId->setText(QString::number(disc.at(0).getId()));
			txtDenumire->setText(QString::fromStdString(disc.at(0).getDenumire()));
			txtDurata->setText(QString::number(disc.at(0).getOre()));
			txtTip->setText(QString::fromStdString(disc.at(0).getTip()));
			txtProfesor->setText(QString::fromStdString(disc.at(0).getCadruDidactic()));
		}
		});

	//cand se emite semnalul clicked de pe buton, se afiseaza statisticile (tip - numar de aparitii)
	QObject::connect(radioBtnStats, &QRadioButton::clicked, this, &InterfataGUI::statisticiDiscipline);

	//cand se emite semnalul clicked de pe buton, se sterg toate disciplinele din contract
	QObject::connect(btnGolesteContract, &QPushButton::clicked, this, &InterfataGUI::golesteContract);

	//cand se emite semnalul clicked de pe buton, adaug in contract o disciplina existenta
	QObject::connect(btnAddContr_id, &QPushButton::clicked, this, &InterfataGUI::adauga_inContract);

	//cand se emite semnalul clicked de pe buton, se adauga un numar de discipline in contract
	QObject::connect(btnGenerareContract, &QPushButton::clicked, this, &InterfataGUI::adaugaRandom_inContract);

	//cand se emite semnalul clicked de pe buton, se salveaza intr-un fisier html disciplinele din contract
	QObject::connect(btnSalv_html, &QPushButton::clicked, this, &InterfataGUI::salveaza_inHTML);
}

void InterfataGUI::statisticiDiscipline() {
	vector<DTO_statistics> DTO_stats = service.statsService();
	string statistici;
	for (const auto& stats : DTO_stats) {
		statistici += stats.getTip() + " - " + std::to_string(stats.getFrecventa()) + "\n";
	}
	labelStats->setText(QString::fromStdString(statistici));
}

void InterfataGUI::addNewDiscipline() {
	try {
		service.addDisciplinaService(txtDenumire->text().toStdString(), txtDurata->text().toInt(), txtTip->text().toStdString(), txtProfesor->text().toStdString());
		reloadList(service.getDiscipline(), "discipline");

		//curatam textul daca s-a reusit introducerea datelor in lista
		curata_txt();

		delete_btnsDiscipline();
		init_btnsDiscipline(service.getDiscipline());
	}
	catch (RepoException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
	}
	catch (ValidateException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
	}
}

void InterfataGUI::updateDiscipline() {
	try {
		service.updateDisciplinaService(txtId->text().toInt(), txtDenumire->text().toStdString(), txtDurata->text().toInt(), txtTip->text().toStdString(), txtProfesor->text().toStdString());
		reloadList(service.getDiscipline(), "discipline");
	}
	catch (RepoException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
	}
	catch (ValidateException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
	}
}

void InterfataGUI::deleteDiscipline() {
	try {
		service.deleteDisciplinaService(txtId->text().toInt(), txtDenumire->text().toStdString(), txtDurata->text().toInt(), txtTip->text().toStdString(), txtProfesor->text().toStdString());
		reloadList(service.getDiscipline(), "discipline");

		//curatam textul daca s-a reusit stergerea datelor din lista
		curata_txt();

		delete_btnsDiscipline();
		init_btnsDiscipline(service.getDiscipline());
	}
	catch (RepoException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
	}
	catch (ValidateException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
	}
}

void InterfataGUI::undoDiscipline() {
	try {
		service.undo();
		reloadList(service.getDiscipline(), "discipline");

		delete_btnsDiscipline();
		init_btnsDiscipline(service.getDiscipline());
	}
	catch (ServiceException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
	}
}

void InterfataGUI::golesteContract() {
	service.golesteContract();
	reloadList(service.getDiscipline_dinContract(), "contract");
	labelNrDiscipline_dinContract->setText(QString::number(service.totalDiscipline_dinContract()));
	QMessageBox::information(this, "Info", "Contract golit cu succes!");
}

void InterfataGUI::adauga_inContract() {
	try {
		service.add_toContract_dupaId(txtId->text().toInt());
		reloadList(service.getDiscipline_dinContract(), "contract");
		labelNrDiscipline_dinContract->setText(QString::number(service.totalDiscipline_dinContract()));
	}
	catch (RepoException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
	}
	catch (ServiceException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
	}
}

void InterfataGUI::adaugaRandom_inContract() {
	try {
		service.addRandom_toContract(txt_n->text().toInt());
		reloadList(service.getDiscipline_dinContract(), "contract");
		labelNrDiscipline_dinContract->setText(QString::number(service.totalDiscipline_dinContract()));
	}
	catch (RepoException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
	}
	catch (ServiceException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
	}
}

void InterfataGUI::salveaza_inHTML() {
	string my_Filename = txt_n->text().toStdString();
	my_Filename = my_Filename + ".html";
	service.save_toHTMLService(my_Filename);
	QMessageBox::information(this, "Info", "Contract salvat cu succes!");
}

void InterfataGUI::reloadList(const vector<Disciplina>& discipline, const string tip) {
	if (tip == "discipline") {
		lstDiscipline->clear();
	}
	else if (tip == "contract") {
		lstContract->clear();
	}
	for (const auto& disciplina : discipline) {
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(disciplina.getDenumire() + " -- " + disciplina.getCadruDidactic()));
		item->setData(Qt::UserRole, disciplina.getId());
		if (tip == "discipline") {
			lstDiscipline->addItem(item);
		}
		else if (tip == "contract") {
			lstContract->addItem(item);
		}
	}
}