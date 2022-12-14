/*************************************************************************
Title: LocalSearch.h
Description: Flow Shop Scheduling Problem
Author: Julio Mario Daza-Escorcia
Date: 11/12/22
*************************************************************************/

#pragma once
#include "Algorithm.h"
#include <algorithm>
#include <queue>
#include <random>
#include <windows.h>

class LocalSearch : public Algorithm
{
private:
	void copyJobsToSortedJobs(std::vector<Job> &sortedJobs);
	void checkNewMakespan(int &tmpMakespan, std::vector<Job> &tmpResultSchedule);
	void findNewSchedule(int &numberOfJobsInResult, Job &job, std::vector<Job> &tmpResultSchedule);
	std::vector<Job> insert(const std::vector<Job>& actualResultSchedule);
public:
	explicit LocalSearch();
	LocalSearch(const Algorithm* a);
	~LocalSearch();

	virtual void initialLexicographicalSolution();
	virtual void randomMove();
	virtual void twoOptMove();	
	virtual double Performance_Counter_Diff(LARGE_INTEGER* a, LARGE_INTEGER* b);
	//LARGE_INTEGER* iniTime;
	//LARGE_INTEGER* endTime;
	int getMakespan() const;
	std::vector<Job> getResultSchedule() const;
};

