#ifndef _ELECTSYSTEM_H_
#define _ELECTSYSTEM_H_

#include "Poll.h"
#include <vector>
#include <fstream>

class ElectSystem
{
private:
	bool _state; // true - состояние выборов активировано
	bool _elections; // true - начало выборов
	map<string, Poll*> _polls;
	map<string, Voter*> _candidates;
	map<string, Voter*> _voters;
public:
	ElectSystem(); 
	ElectSystem(map<string, Poll*> polls, map<string, Voter*> candidates, bool state = false, bool elections = false)
		: _polls(polls), _candidates(candidates), _state(state), _elections(elections) { }
	void createElections();
	void startElections();
	Poll* findPoll(string name) const;
	Voter* findVoter(string id) const;
	Voter* findCandidate(string id) const;
	void addVoter(string id, string name, string pollName);
	void removeVoter(string id);
	void addPoll(string name);
	void merge(string source, string destination);
	void addCandidate(string id);
	void removeCandidate(string id);
	void vote(string idVoter, string idCandidate);
	void printCandidates() const;
	void printPolls() const;
	void printVotersFromPoll(string pollName) const;
	void printVoters() const;
	void showStatistics() const;
	void showPollStatistics(string pollName) const;
	void finishElections();
	void stopElections();
	void printFile(string fileName) const;
	void clear() { _polls.clear(); _candidates.clear(); _voters.clear(); }
	~ElectSystem() { _polls.clear(); _candidates.clear(); _voters.clear(); }
};

#endif
