#include "Poll.h"

void Poll::addVoter(Voter * voter)
{
	if (_voters.count(voter->getID()) > 0)
		throw logic_error("ID already exists");
	_voters.insert(pair<string, Voter*>(voter->getID(), voter));
}

void Poll::addVoter(string id, string name)
{
	addVoter(new Voter(id, name, this));
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

void Poll::removeVoter(Voter * voter)
{
	removeVoter(voter->getID());
}
