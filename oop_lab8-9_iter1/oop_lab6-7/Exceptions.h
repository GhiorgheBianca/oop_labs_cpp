#pragma once
#include <iostream>
#include <string>
#include <vector>

using std::vector;
using std::string;
using std::ostream;

/*
	Folosit pentru a semnala datele care nu indeplinesc conditiile necesare obiectului de tip Disciplina.
*/
class ValidateException {
	vector<string> messages;

public:
	ValidateException(const vector<string>& errors) :messages{ errors } {}
	// functie friend (vreau sa folosesc membru privat messages)
	friend ostream& operator<<(ostream& out, const ValidateException& ex);

};

ostream& operator<<(ostream& out, const ValidateException& ex);


/*
	Folosit pentru a semnala situatii exceptionale care pot aparea in repository
*/
class RepoException {
	string message;

public:
	RepoException(string m) :message{ m } {}
	// functie friend (vreau sa folosesc membrul privat message)
	friend ostream& operator<<(ostream& out, const RepoException& ex);
};

ostream& operator<<(ostream& out, const RepoException& ex);