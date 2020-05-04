#include "UI.h"
#include "Service.h"
#include "Repository.h"
#include "Validator.h"
#include "Tests.h"
#include <crtdbg.h>

void adaugaCateva(Service& service) {
	service.addDisciplinaService("Sisteme de operare", 5, "optionala", "Boian");
	service.addDisciplinaService("Geometrie", 4, "obligatorie", "Blaga");
	service.addDisciplinaService("Fundamentele programarii", 6, "obligatorie", "Czibula");
	service.addDisciplinaService("Fundamentele programarii", 6, "obligatorie", "Molnar");
}

int main()
{
	{
		all_tests();

		Repository repo{ 0.7 };
		//RepoFile repo{ "discipline.txt",0 };
		Validator validator;
		Service service{ repo,validator };
		//if (repo.getDiscipline().size() == 0)
			//adaugaCateva(service);
		ConsolUI ui{ service };
		ui.start();
	}
	_CrtDumpMemoryLeaks();
	return 0;
}