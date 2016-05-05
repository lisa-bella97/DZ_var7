#include "ElectSystem.h"

void ElectSystem::createElections()
{
	if (_state == prepared)
		throw logic_error("Elections have just created");
	_state = prepared;
}

void ElectSystem::startElections()
{
	if (_state == elections)
		throw logic_error("Elections have just started");
	_state = elections;
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

Candidate* ElectSystem::findCandidate(string id) const
{
	auto candidate = _candidates.find(id);
	if (candidate == _candidates.end())
		return nullptr;
	return candidate->second;
}

void ElectSystem::addVoter(string id, string name, string pollName)
{
	if (_state == elections)
		throw logic_error("Elections have just started");
	Poll* poll = findPoll(pollName);
	if (!poll)
		throw logic_error("Poll has not been found");
	if (findVoter(id))
		throw logic_error("ID already exists");
	Voter* voter = new Voter(id, name, poll);
	_voters.insert(pair<string, Voter*>(id, voter));
	poll->addVoter(voter);
}

void ElectSystem::addPoll(string name)
{
	if (_state == elections)
		throw logic_error("Elections have just started");
	if (findPoll(name))
		throw logic_error("Poll with such name already exists");
	_polls.insert(pair<string, Poll*>(name, new Poll(name)));
}

void ElectSystem::addCandidate(string id)
{
	if (_state != prepared)
		throw logic_error("No elections created");
	else if (_state == elections)
		throw logic_error("Elections have just started");
	Voter* voter = findVoter(id);
	if (!voter)
		throw logic_error("Voter has not been found");
	_candidates.insert(pair<string, Candidate*>(id, new Candidate(voter)));
	cout << "Added: " << voter->getID() << ' ' << voter->getName() << endl;
}

void ElectSystem::removeVoter(string id)
{
	if (_state == elections)
		throw logic_error("Elections have just started");
	Voter* voter = findVoter(id);
	if (!voter)
		throw logic_error("Voter has not been found");
	Candidate* candidate = findCandidate(id);
	if (candidate && candidate->getVoter() == voter)
		_candidates.erase(id);
	voter->getPoll()->removeVoter(id);
	_voters.erase(id);
}

void ElectSystem::merge(string source, string destination)
{
	if (_state == elections)
		throw logic_error("Elections have just started");
	Poll* s_poll = findPoll(source);
	if (!s_poll)
		throw logic_error("Source poll has not been found");
	Poll* dest_poll = findPoll(destination);
	if (!dest_poll)
		throw logic_error("Destination poll has not been found");
	map<string, Voter*> s_voters = s_poll->getVoters();
	for (auto it = s_voters.begin(); it != s_voters.end(); it++)
		it->second->changePoll(dest_poll);
	dest_poll->addVoters(s_voters);
	_polls.erase(source);
}

void ElectSystem::removeCandidate(string id)
{
	if (_state != prepared)
		throw logic_error("No elections created");
	else if (_state == elections)
		throw logic_error("Elections have just started");
	if (!findVoter(id))
		throw logic_error("Voter has not been found");
	_candidates.erase(id);
}

void ElectSystem::vote(string idVoter, string idCandidate)
{
	if (_state != elections)
		throw logic_error("No elections going on");
	Voter* voter = findVoter(idVoter);
	if (!voter)
		throw logic_error("Voter has not been found");
	Candidate* candidate = findCandidate(idCandidate);
	if (!candidate)
		throw logic_error("Candidate has not been found");
	voter->vote(candidate);
	candidate->increaseVotes();
}

void ElectSystem::printCandidates() const
{
	if (_state != prepared)
		throw logic_error("No elections going on");
	for (auto it = _candidates.begin(); it != _candidates.end(); it++)
		cout << it->first << it->second->getVoter()->getName() << endl;
}

void ElectSystem::printPolls() const
{
	for (auto it = _polls.begin(); it != _polls.end(); it++)
		cout << it->first << endl;
}

void ElectSystem::printVotersFromPoll(string pollName) const
{
	Poll* poll = findPoll(pollName);
	if (!poll)
		throw logic_error("Poll has not been found");
	poll->printVoters();
}

void ElectSystem::printVoters() const
{
	for (auto it = _polls.begin(); it != _polls.end(); it++)
	{
		cout << it->first << ":\n";
		it->second->printVoters();
	}
}

void ElectSystem::showStatistics() const
{
	if (_state != prepared)
		throw logic_error("No elections going on");
	for (auto it = _polls.begin(); it != _polls.end(); it++)
	{
		cout << it->first << ":\n";
		it->second->showStatistics();
	}
}

void ElectSystem::showVoterStatistics(string id) const
{
	if (_state != prepared)
		throw logic_error("No elections going on");
	Voter* voter = findVoter(id);
	if (!voter)
		throw logic_error("Voter has not been found");
	voter->showStatistics();
}

void ElectSystem::showPollStatistics(string pollName) const
{
	if (_state != prepared)
		throw logic_error("No elections going on");
	Poll* poll = findPoll(pollName);
	if (!poll)
		throw logic_error("Poll has not been found");
	poll->showStatistics();
}

void ElectSystem::finishElections()
{
	if (_state != elections)
		throw logic_error("No elections going on");
	int max = 0;
	for (auto it = _candidates.begin(); it != _candidates.end(); it++)
	{
		if (it->second->getVotes() > max)
			max = it->second->getVotes();
	}
	if (max != 0)
	{
		for (auto it = _candidates.begin(); it != _candidates.end(); it++)
		{
			if (max == it->second->getVotes())
				cout << it->second->getVoter()->getID() << ' ' << it->second->getVoter()->getName() << " won!\n";
		}
	}
	else
		cout << "No winners";
	_state == prepared;
}

void ElectSystem::stopElections()
{
	if (_state != prepared)
		throw logic_error("No elections going on");
	for (auto it = _voters.begin(); it != _voters.end(); it++)
		it->second->removeCandidate();
	_candidates.clear();
	_state = usual;
}

void ElectSystem::printFile(string fileName) const
{
	ofstream fout(fileName);
	for (auto it = _polls.begin(); it != _polls.end(); it++)
		fout << "poll " << it->second->getName() << endl;
	for (auto it = _voters.begin(); it != _voters.end(); it++)
		fout << "voter " << it->second->getID() << ' ' << it->second->getName() << ' ' << it->second->getPoll()->getName() << endl;
	fout.close();
}
