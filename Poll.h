#ifndef _POLL_H_
#define _POLL_H_

#include <map>
#include <iostream>
#include <string>

using namespace std;

class Poll;

class Voter // Избиратель
{
private:
	string _id; // уникальный идентификатор избирателя
	string _name;
	Poll* _poll;
	Voter* _candidate; // кандидат, за которого проголосовал избиратель
	int _votes; //кол-во голосов, отданных за кандидата (если избиратель - кандидат)
public:
	Voter(string id, string name, Poll* poll) : _id(id), _name(name), _poll(poll) { _candidate = nullptr; _votes = 0; }
	string getID() const { return _id; }
	string getName() const { return _name; }
	Poll* getPoll() const { return _poll; }
	Voter* getCandidate() const { return _candidate; }
	int getVotes() const { return _votes; }
	void increaseVotes() { _votes++; }
	void changePoll(Poll* poll) { _poll = poll; }
	void vote(Voter* candidate);
	void showStatistics() const;
	void print() const;
	void removeCandidate() { _candidate = nullptr; }
};

class Poll // Избирательный участок
{
private:
	string _name;
	map<string, Voter*> _voters;
public:
	Poll(string name) : _name(name) { }
	void addVoter(Voter* voter);
	void addVoter(string id, string name);
	void addVoters(map<string, Voter*> voters);
	void removeVoter(string id);
	void removeVoter(Voter* voter);
	string getName() const { return _name; }
	map<string, Voter*> getVoters() const { return _voters; }
	void showStatistics() const;
	void printVoters() const;
	~Poll() { _voters.clear(); }
};

#endif
