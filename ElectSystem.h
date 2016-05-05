#ifndef _ELECTSYSTEM_H_
#define _ELECTSYSTEM_H_

#include "Poll.h"
#include <vector>
#include <fstream>

class ElectSystem
{
private:
	enum State { usual, prepared, elections };
	State _state; 
	map<string, Poll*> _polls;
	map<string, Candidate*> _candidates;
	map<string, Voter*> _voters;
public:
	ElectSystem() : _state(usual) { }
	void createElections();
	void startElections();
	Poll* findPoll(string name) const;
	Voter* findVoter(string id) const;
	Candidate* findCandidate(string id) const;
	void addVoter(string id, string name, string pollName);
	void addPoll(string name);
	void addCandidate(string id);
	void removeVoter(string id);
	void merge(string source, string destination);
	void removeCandidate(string id);
	void vote(string idVoter, string idCandidate);
	void printCandidates() const;
	void printPolls() const;
	void printVotersFromPoll(string pollName) const;
	void printVoters() const;
	void showStatistics() const;
	void showVoterStatistics(string id) const;
	void showPollStatistics(string pollName) const;
	void finishElections();
	void stopElections();
	void printFile(string fileName) const;
	void clear() { _polls.clear(); _candidates.clear(); _voters.clear(); }
	~ElectSystem() { _polls.clear(); _candidates.clear(); _voters.clear(); }
};

#endif
