#include "UI.h"
#include "Service.h"
#include "Repository.h"
#include "Validator.h"
#include "Tests.h"
#include <crtdbg.h>

void adaugaCateva(Service& service) {
	service.addDisciplinaService("Geometrie", 4, "obligatorie", "Blaga");
	service.addDisciplinaService("Sisteme de operare", 5, "obligatorie", "Boian");
	service.addDisciplinaService("Fundamentele programarii", 6, "obligatorie", "Czibula");
	service.addDisciplinaService("Fundamentele programarii", 6, "obligatorie", "Molnar");
}

int main()
{
	{
		all_tests();

		Repository repo;
		Validator validator;
		Service service{ repo,validator };
		adaugaCateva(service);
		ConsolUI ui{ service };
		ui.start();
	}
	_CrtDumpMemoryLeaks();
	return 0;
}