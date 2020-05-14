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

	const string getMessage() {
		string msgs;
		for (const auto& msg : messages) {
			msgs = msgs + msg + "\n";
		}
		return msgs;
	}
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

	const string getMessage() {
		return message;
	}
};

ostream& operator<<(ostream& out, const RepoException& ex);


/*
	Folosit pentru a semnala situatii exceptionale care pot aparea in service
*/
class ServiceException {
	string service_mess;

public:
	ServiceException(string mess) :service_mess{ mess } {}
	// functie friend (vreau sa folosesc membrul privat message)
	friend ostream& operator<<(ostream& out, const ServiceException& ex);

	const string getMessage() {
		return service_mess;
	}
};

ostream& operator<<(ostream& out, const ServiceException& ex);