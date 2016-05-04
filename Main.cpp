#include "ElectSystem.h"
#include <sstream>

vector<string> split(const string &s, char delim);
void checkSize(int size, int requiredSize);
void doCommand(ElectSystem& electSystem, string command);
void getState(ElectSystem& electSystem, string fileName);

int main()
{
	string str;
	ElectSystem electSystem;

	while (true)
	{
		try
		{
			cout << '>';
			getline(cin, str);
			if (str == "exit")
				break;
			doCommand(electSystem, str);
		}
		catch (const exception & e)
		{
			cout << "ERROR: " << e.what() << endl;
		}
	}

	system("pause");
	return 0;
}

vector<string> split(const string &s, char delim)
{
	vector<string> elems;
	stringstream ss(s);
	string item;

	while (getline(ss, item, delim))
		elems.push_back(item);

	return elems;
}

void checkSize(int size, int requiredSize)
{
	if (size != requiredSize)
		throw invalid_argument("Incorrect operation.\n");
}

void doCommand(ElectSystem& electSystem, string command)
{
	vector<string> commands = split(command, ' ');

	if (commands[0] == "load")
	{
		checkSize(commands.size(), 2);
		getState(electSystem, commands[1]);
	}
	else if (commands[0] == "save")
	{
		checkSize(commands.size(), 2);
		electSystem.printFile(commands[1]);
	}
	else if (commands[0] == "list")
	{
		checkSize(commands.size(), 2);

		if (commands[1] == "polls")
			electSystem.printPolls();
		else if (commands[1] == "voters")
			electSystem.printVoters();
		else if (commands[1] == "candidates")
			electSystem.printCandidates();
		else
			electSystem.printVotersFromPoll(commands[1]);
	}
	else if (commands[0] == "add" && commands.size() > 2)
	{

		if (commands[1] == "voter")
		{
			checkSize(commands.size(), 5);
			electSystem.addVoter(commands[2], commands[3], commands[4]);
			cout << "Added: " << commands[2] << ' ' << commands[3] << endl;
		}
		else if (commands[1] == "poll")
		{
			checkSize(commands.size(), 3);
			electSystem.addPoll(commands[2]);
			cout << "Added: " << commands[2] << " poll" << endl;
		}
		else if (commands[1] == "candidate")
		{
			checkSize(commands.size(), 3);
			electSystem.addCandidate(commands[2]);
		}
		else
			throw logic_error("Incorrect operation");
	}
	else if (commands[0] == "merge")
	{
		checkSize(commands.size(), 3);
		electSystem.merge(commands[1], commands[2]); 
	}
	else if (commands.size() == 2 && commands[0] == "create" && commands[1] == "elections")
	{
		electSystem.createElections();
		cout << "Created\n";
	}
	else if (commands.size() == 2 && commands[0] == "start" && commands[1] == "elections")
	{
		electSystem.startElections();
		cout << "Started\n";
	}
	else if (commands.size() == 2 && commands[0] == "finish" && commands[1] == "elections")
	{
		electSystem.finishElections();
	}
	else if (commands.size() == 2 && commands[0] == "stop" && commands[1] == "elections")
	{
		electSystem.stopElections();
	}
	else if (commands[0] == "vote")
	{
		checkSize(commands.size(), 3);
		electSystem.vote(commands[1], commands[2]);
	}
	else if (commands[0] == "stats")
	{

		if (commands.size() == 1)
			electSystem.showStatistics();
		else
		{
			checkSize(commands.size(), 2);
			electSystem.showPollStatistics(commands[1]);
		}
	}
	else if (commands[0] == "rm" && commands.size() > 2)
	{
		checkSize(commands.size(), 3);

		if (commands[1] == "candidate")
			electSystem.removeCandidate(commands[2]);
		else if (commands[1] == "voter")
			electSystem.removeVoter(commands[2]);
		else
			throw logic_error("Incorrect operation");
	}
	else
		throw logic_error("Incorrect operation");
}

void getState(ElectSystem & electSystem, string fileName)
{
	ifstream fin(fileName);

	if (!fin.is_open())
		throw runtime_error("File is not found");

	string str;
	vector<string> commands;
	electSystem.clear();

	while (getline(fin, str))
	{
		commands = split(str, ' ');
		if (commands[0] == "voter")
		{
			checkSize(commands.size(), 4);
			electSystem.addVoter(commands[1], commands[2], commands[3]);
		}
		else if (commands[0] == "poll")
		{
			checkSize(commands.size(), 2);
			electSystem.addPoll(commands[1]);
		}
		else
		{
			electSystem.clear();
			throw logic_error("Incorrect information in file");
		}
	}

	fin.close();
}
