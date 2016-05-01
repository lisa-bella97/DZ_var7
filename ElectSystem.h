#ifndef _ELECTSYSTEM_H_
#define _ELECTSYSTEM_H_

#include "Poll.h"

class ElectSystem
{
private:
	bool _state; // true - проведение выборов
	map<string, Poll*> _polls;
	map<string, Voter*> _candidates;
	map<string, Voter*> _voters;
public:
	ElectSystem(); 
	ElectSystem(map<string, Poll*> polls, map<string, Voter*> candidates, bool state = false)
		: _polls(polls), _candidates(candidates), _state(state) { }
	void setState(bool state) { _state = state; }
	Poll* findPoll(string name) const;
	Voter* findVoter(string id) const;
	void addVoter(string id, string name, string pollName);
	void removeVoter(string id);
	void addPoll(string name);
	void merge(string source, string destination);
	void addCandidate(string id);
	void removeCandidate(string id);
	~ElectSystem() { _polls.clear(); _candidates.clear(); }
};

#endif

