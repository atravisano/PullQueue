/*
Author: Anthony Travisano
*/
#include "ServerGroup.h"
#include "pullqueue.h"
#include<iostream>
#include<string>
#include<memory>
#include<cstdlib>

struct customer
{
	int timeStamp = 0;
	int transType = 0;
	bool operator==(const customer & item)
	{
		return transType == item.transType;
	}
};

int main()
{
	srand(0);
	int simLength = 0;
	int numServers = 0;
	string YNspServer = "";
	bool spServer = false;
	int numTransTypes = 0;		
	int avgCustomerArrival = 0;
	int clock = 0;
	float avgWaitTime = 0.0;
	float arrivalProb = 0.0;
	float totalWaitTimeForCustomersServed = 0.0;
	int totalNumCustomersServed = 0;

	cout << "Enter the length of the simulation: ";
	cin >> simLength;
	cout << "\nEnter the number of general purpose servers: ";
	cin >> numServers;
	cout << "\nWill there be a special purpose server? ";
	cin >> YNspServer;
	if (YNspServer == "yes")
	{
		spServer = true;
	}
	cout << "\nEnter the number of different types of transactions: ";
	cin >> numTransTypes;
	unique_ptr<int[]> transTypeArr(new int[numTransTypes]);
	for (int i = 0; i < numTransTypes; i++)
	{
		cout << "\nEnter the average transaction time for transaction " << i << " : ";
		cin >> transTypeArr[i];
	}
	cout << "\nEnter the average time between customer arrivals: ";
	cin >> avgCustomerArrival;

	arrivalProb = 1.0 / avgCustomerArrival;		//the probabability of a new customer arriving
	
	ServerGroup gpServers (numServers);

	PullQueue<customer> pq;
		
	customer c1;
	customer pullc1;

	while (clock < simLength)
	{	
		clock++;
		gpServers.decServers();
		
		//randomly determines whether a customer arrived
		if (float(rand()) / RAND_MAX <= arrivalProb)
		{	
			c1.transType = rand() % numTransTypes;	//randomly determines transaction type for customer
			c1.timeStamp = clock;  //gives time of clock when enqueued
			pq.enqueue(c1);		//enqueue customer on the PullQueue
		}
		
		if (spServer && gpServers.spServerFree())
		{
			c1.transType = 0;
			//an attempt is made to pull an item from the PullQueue
			if (pq.pull(c1, pullc1))
			{
				gpServers.usespServer(transTypeArr[pullc1.transType]);	
				totalNumCustomersServed++;
				totalWaitTimeForCustomersServed += clock - pullc1.timeStamp;
			}
			else
			{
				if (gpServers.serverFree() && !pq.isEmpty())
				{
					pq.dequeue(c1);
					gpServers.useServer(transTypeArr[c1.transType]);
					totalNumCustomersServed++;
					totalWaitTimeForCustomersServed += clock - c1.timeStamp;
				}
			}
		}
		
		

		else if (gpServers.serverFree() && !pq.isEmpty())
		{
			pq.dequeue(c1);
			gpServers.useServer(transTypeArr[c1.transType]);
			totalNumCustomersServed++;
			totalWaitTimeForCustomersServed += clock - c1.timeStamp;
		}
	}
		//Average wait time = (total wait time for all customers served) / (number of customers served)
	avgWaitTime = totalWaitTimeForCustomersServed / totalNumCustomersServed;
	
	if (spServer)
	{
		cout << endl;
		cout << "special purpose server enabled" << endl;
		cout << "average wait time: " << avgWaitTime;
		getchar();
	}

	else
	{
		cout << endl;
		cout << "no special purpose server" << endl;
		cout << "average wait time: " << avgWaitTime;
		getchar();
	}

	getchar();

	return 0;
}
