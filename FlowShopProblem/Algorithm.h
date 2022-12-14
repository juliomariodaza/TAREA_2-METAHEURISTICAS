/*************************************************************************
Title: Algorithm.h
Description: Flow Shop Scheduling Problem
Author: Julio Mario Daza-Escorcia
Date: 11/12/22
*************************************************************************/

#pragma once
#include <string>
#include "Job.h"
#include <list>


class Algorithm
{
private:
	int getAndValidateData();

protected:
	int numberOfMachines;
	int numberOfJobs;
	std::vector<Job> jobs;
	int makespan;
	std::vector<Job> resultSchedule;

	int computeMakespan(const int jobsInResultSchedule);
	int scheduleMakespan(const std::vector<Job>& resultSchedule);
	int max(const int first, const int second);

public:
	
	explicit Algorithm();
	virtual ~Algorithm();

	bool initData();
	bool initData(const std::string fileName);

	void showData() const;
	void showResult(const std::string fileName, double TotalSecs=0.0) const;

	virtual void initialLexicographicalSolution() = 0;
};

