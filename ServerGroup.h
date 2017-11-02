/*
Author: Anthony Travisano
*/
#pragma once
#include <vector>
#include<iostream>

using namespace std;

class ServerGroup
{
	vector<int>servers;
	int spServer;
	int freeServer;
public: 
	ServerGroup(int num);
	bool spServerFree();
	bool serverFree();
	void useServer(int avTransTime);
	void usespServer(int avTransTime);
	void decServers();
};
//ServerGroup Constructor
ServerGroup::ServerGroup(int num)
{
	servers.resize(num);

	//Sets each element in the vector to zero
	for (int & element : servers)
	{
		servers[element] = 0;
	}

	spServer = 0;
}

//Returns true if spServer is zero, otherwise returns false
bool ServerGroup::spServerFree()
{
	if (spServer == 0)
	{
		return true;
	}

	return false;
}

//serverFree will return true if it finds a zero in the vector, and returns false otherwise
//If it finds a zero in the vector, it will set freeServer to that index
bool ServerGroup::serverFree()
{
	for (int i = 0; i < servers.size(); i++)
	{
		if (servers[i] == 0)
		{
			freeServer = i;
			return true;
		}
	}
	return false;
}

void ServerGroup::useServer(int avTransTime)
{
	servers[freeServer] = avTransTime;
}

void ServerGroup::usespServer(int avTransTime)
{
	spServer = avTransTime;
}

void ServerGroup::decServers()
{
//Decreases spServer if spServer is not zero
	if (spServer != 0)
	{
		spServer--;
	}
	for (int i=0 ; i < servers.size(); i++)
	{
		//decreases nonzero servers
		if (servers[i] != 0)
		{
			servers[i] = servers[i] - 1;
		}
	}

	

}
