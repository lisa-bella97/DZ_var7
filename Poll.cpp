#include "Poll.h"

//******************** Voter ***********************************

void Voter::vote(Candidate * candidate)
{
	if (_candidate != nullptr)
		throw  logic_error("No second time voting");

	_candidate = candidate;
}

void Voter::showStatistics() const
{
	if (_candidate)
		cout << _id << " chose " << _candidate->getVoter()->_id << endl;
	else
		cout << _id << " has not chosen anybody" << endl;
}

void Voter::print() const
{
	cout << _id << ' ' << _name << endl;
}

//******************** Poll ***********************************

void Poll::addVoter(Voter * voter)
{
	if (_voters.count(voter->getID()) > 0)
		throw logic_error("ID already exists");

	_voters.insert(pair<string, Voter*>(voter->getID(), voter));
}

void Poll::addVoters(map<string, Voter*> voters)
{
	_voters.insert(voters.begin(), voters.end());
}

void Poll::removeVoter(string id)
{
	if (_voters.count(id) == 0)
		throw logic_error("Voter has not been found");

	_voters.erase(id);
}

void Poll::showStatistics() const
{
	for (auto it = _voters.begin(); it != _voters.end(); it++)
		it->second->showStatistics();
}

void Poll::printVoters() const
{
	for (auto it = _voters.begin(); it != _voters.end(); it++)
		it->second->print();
}

Poll::~Poll()
{
	for (auto it = _voters.begin(); it != _voters.end(); it++)
		delete it->second;

	_voters.clear();
}
