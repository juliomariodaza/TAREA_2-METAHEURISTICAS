/*************************************************************************
Title: LocalSearch.cpp
Description: Flow Shop Scheduling Problem
Author: Julio Mario Daza-Escorcia
Date: 11/12/22
*************************************************************************/

#include "stdafx.h"
#include "LocalSearch.h"


LocalSearch::LocalSearch() : Algorithm()
{
}


LocalSearch::~LocalSearch()
{
}


LocalSearch::LocalSearch(const Algorithm* a)
{
	const LocalSearch *other = static_cast<const LocalSearch*>(a);
	this->numberOfJobs = other->numberOfJobs;
	this->numberOfMachines = other->numberOfMachines;
	this->jobs = other->jobs;
}

void LocalSearch::initialLexicographicalSolution()
{
	for (auto it = jobs.begin(); it != jobs.end(); it++)
		resultSchedule.push_back(*it);
	makespan = computeMakespan(jobs.size());
	//int prueba = scheduleMakespan(resultSchedule);
	//std::cout << "\n" << makespan << " = " << prueba << "\n";
}

void LocalSearch::randomMove()
{
	const int MAX_ITER = (numberOfMachines * numberOfJobs);
	std::vector<Job> actualResultSchedule = resultSchedule;

	for (int i = 1; i <= MAX_ITER; i++)
	{
		std::vector<Job> newResultSchedule = insert(actualResultSchedule);
		int newMakespan = scheduleMakespan(newResultSchedule);
		if (newMakespan < makespan)
		{
			makespan = newMakespan;
			resultSchedule = newResultSchedule;
			actualResultSchedule = newResultSchedule;
		}
	}

}

void LocalSearch::twoOptMove()
{
	std::vector<Job> actualResultSchedule = resultSchedule;
	std::vector<Job> OriginalResultSchedule = resultSchedule;

	//for (auto it = OriginalResultSchedule.begin(); it != OriginalResultSchedule.end(); it++)
	//	std::cout << it->getJobNumber() << "-";
	//std::cout << "\n";
	int i, j, jobI = 0, jobJ = 0, newMakespan = 0, Size = OriginalResultSchedule.size();
	for (i = 1; i <= Size-2 ; i++)
	{
		Job jobI = OriginalResultSchedule[i];
		for (j = i+1; j <= Size-1; j++)
		{
			Job jobJ = OriginalResultSchedule[j];
			
			auto it = actualResultSchedule.begin();
			actualResultSchedule.erase(it + i);
			actualResultSchedule.insert(it + i, jobJ);
			actualResultSchedule.erase(it + j);
			actualResultSchedule.insert(it + j, jobI);
			newMakespan = scheduleMakespan(actualResultSchedule);

			//for (auto it = actualResultSchedule.begin(); it != actualResultSchedule.end(); it++)
			//	std::cout << it->getJobNumber() << "-";
			//std::cout << "\n";

			if (newMakespan < makespan)
			{
				makespan = newMakespan;
				resultSchedule = actualResultSchedule;				
			}
			actualResultSchedule = OriginalResultSchedule;
		}
	}
}

double LocalSearch::Performance_Counter_Diff(LARGE_INTEGER* a, LARGE_INTEGER* b)
{
	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	return (double)(a->QuadPart - b->QuadPart) / (double)freq.QuadPart;

}

void LocalSearch::copyJobsToSortedJobs(std::vector<Job> &sortedJobs)
{
	for (auto it = jobs.begin(); it != jobs.end(); it++)
		sortedJobs.push_back(*it);	
}

void LocalSearch::findNewSchedule(int &numberOfJobsInResult, Job &job, std::vector<Job> &tmpResultSchedule)
{
	int tmpMakespan = INT_MAX;
	auto it = resultSchedule.begin();
	for (int i = 0; i < numberOfJobsInResult; i++)
	{
		it = resultSchedule.insert(it + i, job);
		makespan = computeMakespan(numberOfJobsInResult);
		checkNewMakespan(tmpMakespan, tmpResultSchedule);
		resultSchedule.erase(it);
		it = resultSchedule.begin();
	}
	resultSchedule.clear();
	resultSchedule = tmpResultSchedule;
}

std::vector<Job> LocalSearch::insert(const std::vector<Job>& actualResultSchedule)
{
	std::vector<Job> tmpResultSchedule = actualResultSchedule;
	std::random_device randomDevice;
	std::mt19937 generator(randomDevice());
	std::uniform_int_distribution<> range(0, numberOfJobs - 1);

	int a = 0;
	int b = 0;

	while ((a = range(generator)) == 0);
		
	while ((b = range(generator)) == a);
		Job tmp = tmpResultSchedule[a];

	auto it = tmpResultSchedule.begin();
	tmpResultSchedule.erase(it + a);
	tmpResultSchedule.insert(it + b, tmp);

	return tmpResultSchedule;
}

void LocalSearch::checkNewMakespan(int &tmpMakespan, std::vector<Job> &tmpResultSchedule)
{
	if (tmpMakespan > makespan)
	{
		tmpResultSchedule.clear();
		tmpResultSchedule = resultSchedule;
		tmpMakespan = makespan;
	}
}

int LocalSearch::getMakespan() const
{
	return makespan;
}

std::vector<Job> LocalSearch::getResultSchedule() const
{
	return resultSchedule;
}