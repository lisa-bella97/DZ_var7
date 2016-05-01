#include "ElectSystem.h"

ElectSystem::ElectSystem()
{
	_state = false;
}

Poll * ElectSystem::findPoll(string name) const
{
	auto poll = _polls.find(name);
	if (poll == _polls.end())
		return nullptr;
	return poll->second;
}

Voter * ElectSystem::findVoter(string id) const
{
	auto voter = _voters.find(id);
	if (voter == _voters.end())
		return nullptr;
	return voter->second;
}

void ElectSystem::addVoter(string id, string name, string pollName)
{
	Poll* poll = findPoll(pollName);
	if (!poll)
		throw logic_error("Poll has not been found");
	if (!findVoter(id))
		throw logic_error("ID already exists");
	Voter* voter = new Voter(id, name, poll);
	_voters.insert(pair<string, Voter*>(id, voter));
	poll->addVoter(voter);
}

void ElectSystem::removeVoter(string id)
{
	Voter* voter = findVoter(id);
	if (!voter)
		throw logic_error("Voter has not been found");
	voter->getPoll()->removeVoter(id);
	_voters.erase(id);
}

void ElectSystem::addPoll(string name)
{
	if (findPoll(name))
		throw logic_error("Poll with such name already exists");
	_polls.insert(pair<string, Poll*>(name, new Poll(name)));
}

void ElectSystem::merge(string source, string destination)
{
	Poll* s_poll = findPoll(source);
	if (!s_poll)
		throw logic_error("Source poll has not been found");
	Poll* dest_poll = findPoll(source);
	if (!dest_poll)
		throw logic_error("Destination poll has not been found");
	map<string, Voter*> s_voters = s_poll->getVoters();
	for (auto it = s_voters.begin(); it != s_voters.end(); it++)
		it->second->changePoll(dest_poll);
	dest_poll->addVoters(s_voters);
	_polls.erase(source);
}

void ElectSystem::addCandidate(string id)
{
	Voter* voter = findVoter(id);
	if (!voter)
		throw logic_error("Voter has not been found");
	_candidates.insert(pair<string, Voter*>(id, voter));
}

void ElectSystem::removeCandidate(string id)
{
	if (!findVoter(id))
		throw logic_error("Voter has not been found");
	_candidates.erase(id);
}

