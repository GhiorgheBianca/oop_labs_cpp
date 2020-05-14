#include "lab11.h"
#include <QtWidgets/QApplication>
#include <crtdbg.h>
#include "Tests.h"
#include "Service.h"
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qpushbutton.h>
#include "InterfataGUI.h"

void adaugaCateva(Service& service) {
	service.addDisciplinaService("Sisteme de operare", 5, "optionala", "Boian");
	service.addDisciplinaService("Geometrie", 4, "obligatorie", "Blaga");
	service.addDisciplinaService("Fundamentele programarii", 6, "obligatorie", "Czibula");
	service.addDisciplinaService("Fundamentele programarii", 6, "obligatorie", "Molnar");
}

int main(int argc, char *argv[])
{
	{
		all_tests();

		Repository repo;
		//RepoFile repo{ "discipline.txt",0 };
		Validator validator;
		Service service{ repo,validator };
		if (repo.getDiscipline().size() == 0)
			adaugaCateva(service);

		QApplication a(argc, argv);
		InterfataGUI gui{ service };
		gui.show();
		
		return a.exec();
	}
	_CrtDumpMemoryLeaks();
}
