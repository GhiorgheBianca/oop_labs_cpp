#pragma once
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlistwidget.h>
#include <qmessagebox.h>
#include <qradiobutton.h>
#include <qlabel.h>
#include <qdebug.h>
#include <vector>
#include <string>
#include "Service.h"

using std::vector;
using std::string;

class InterfataGUI : public QWidget {
private:
	Service& service;
	QHBoxLayout* lyMain = new QHBoxLayout;
	QListWidget* lstDiscipline;
	QListWidget* lstContract;
	QPushButton* btnExit;
	QPushButton* btnAdd;
	QPushButton* btnUpdate;
	QPushButton* btnDelete;
	QPushButton* btnUndo;
	QPushButton* btnGolesteContract;
	QPushButton* btnAddContr_id;
	QPushButton* btnGenerareContract;
	QPushButton* btnSalv_html;
	QComboBox* comboBoxSort;
	QComboBox* comboBoxFilter;
	QRadioButton* radioBtnStats;
	QLabel* labelStats;
	QLabel* labelNrDiscipline_dinContract;
	QLineEdit* txtId;
	QLineEdit* txtDenumire;
	QLineEdit* txtTip;
	QLineEdit* txtDurata;
	QLineEdit* txtProfesor;
	QLineEdit* txt_n;
	QWidget* widDiscipline;
	QVBoxLayout* btnsDisciplineLayout;
	vector<QPushButton*> butoaneDiscipline;

	void curata_txt();
	void initGUICmps();
	void connectSignalsSlots();
	void reloadList(const vector<Disciplina>& discipline, const string tip);
	void statisticiDiscipline();
	void addNewDiscipline();
	void updateDiscipline();
	void deleteDiscipline();
	void undoDiscipline();
	void golesteContract();
	void adauga_inContract();
	void adaugaRandom_inContract();
	void salveaza_inHTML();
	void init_btnsDiscipline(const vector<Disciplina>& discipline);
	void delete_btnsDiscipline();
	//void buttonClicked(QPushButton* buton);

public:
	InterfataGUI(Service& service) :service{ service } {
		initGUICmps();
		connectSignalsSlots();
		reloadList(service.getDiscipline(), "discipline");
		reloadList(service.getDiscipline_dinContract(), "contract");
	}

};