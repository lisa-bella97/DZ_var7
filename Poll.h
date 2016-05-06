#ifndef _POLL_H_
#define _POLL_H_

#include <map>
#include <iostream>
#include <string>

using namespace std;

class Poll;
class Voter;

class Candidate
{
private:
	Voter* _voter;
	int _votes;
public:
	Candidate(Voter* voter) : _voter(voter) { _votes = 0; }
	Voter* getVoter() const { return _voter; }
	int getVotes() const { return _votes; }
	void increaseVotes() { _votes++; }
};

class Voter
{
private:
	string _id; 
	string _name;
	Poll* _poll;
	Candidate* _candidate; 
public:
	Voter(string id, string name, Poll* poll) : _id(id), _name(name), _poll(poll) { _candidate = nullptr; }
	string getID() const { return _id; }
	string getName() const { return _name; }
	Poll* getPoll() const { return _poll; }
	Candidate* getCandidate() const { return _candidate; }
	void changePoll(Poll* poll) { _poll = poll; }
	void vote(Candidate* candidate);
	void showStatistics() const;
	void print() const;
	void removeCandidate() { _candidate = nullptr; }
};

class Poll 
{
private:
	string _name;
	map<string, Voter*> _voters;
public:
	Poll(string name) : _name(name) { }
	void addVoter(Voter* voter);
	void addVoters(map<string, Voter*> voters);
	void removeVoter(string id);
	string getName() const { return _name; }
	map<string, Voter*> getVoters() const { return _voters; }
	void showStatistics() const;
	void printVoters() const;
	~Poll(); 
};

#endif
