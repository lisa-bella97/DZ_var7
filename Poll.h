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
	Voter* _candidate;
public:
	Voter(string id, string name, Poll* poll) : _id(id), _name(name), _poll(poll) { }
	string getID() const { return _id; }
	string getName() const { return _name; }
	Poll* getPoll() const { return _poll; }
	void changePoll(Poll* poll) { _poll = poll; }
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
	~Poll() { _voters.clear(); }
};

#endif