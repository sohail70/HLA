#include <iostream>
#include <string>
#include <vector>
#include "federate.h"
#include <Windows.h>
using namespace std;

void printUsage(wstring pExeName)
{
	wcout << "Usage: "
		<< pExeName
		<< " <Country Name> <Initial Population> [<Number of Ticks>]"
		<< endl;
}

int main(int argc, char* argv[])
{
	
	std::shared_ptr<country> myCountry; 
	
	//////////////COMMAND LINE ARGS//////////////////////////
	vector<string> cmdlineStringArgs(&argv[0], &argv[0 + argc]);
	vector<wstring>cmdlineWStringArgs;

	for (int i = 0; i < cmdlineStringArgs.size(); i++)
		cmdlineWStringArgs.push_back(s2ws(cmdlineStringArgs[i]));
	/////////////////////////////////////////////////////////

	wstring exeName = cmdlineWStringArgs[0]; 
	
	
	if (argc < 3)
	{
		printUsage(exeName);
		return -1;
	}
	else if (cmdlineWStringArgs[1].empty() && cmdlineWStringArgs[2].empty())
	{
		printUsage(exeName);
		return -1;
	}
	else
	{
		myCountry = make_shared<country>(cmdlineWStringArgs[1] , cmdlineWStringArgs[2]);
	}
	///////////////////////////////////////////////
	myCountry->runFederate(myCountry);
	///////////////////////////////////////////////
	cin.get();
}
