/*************************************************************************
Title: FlowShopProblem.cpp
Description: Flow Shop Scheduling Problem
Author: Julio Mario Daza-Escorcia
Date: 11/12/22
*************************************************************************/

#include "stdafx.h"
#include "Algorithm.h"
#include "LocalSearch.h"
#include <array>

int _tmain(int argc, _TCHAR* argv[])
{
	using namespace std;
	double TotalSecs = 0.0;							// Tiempo Total de corrida en segundos
	LARGE_INTEGER iniTime, endTime;					// Tiempo inicial y final de corrida

	array<string,10> files  
	{
		"../Taillard/T500_20/t500_20.1.txt",
		"../Taillard/T500_20/t500_20.2.txt",
		"../Taillard/T500_20/t500_20.3.txt",
		"../Taillard/T500_20/t500_20.4.txt",
		"../Taillard/T500_20/t500_20.5.txt",
		"../Taillard/T500_20/t500_20.6.txt",
		"../Taillard/T500_20/t500_20.7.txt",
		"../Taillard/T500_20/t500_20.8.txt",
		"../Taillard/T500_20/t500_20.9.txt",
		"../Taillard/T500_20/t500_20.10.txt",
	};

		cout << "-----------------------------------------------------------------------\n";
		cout << " --- FLOW SHOP SCHEDULING PROBLEM BY JULIO MARIO DAZA-ESCORCIA ---\n";
		cout << "-----------------------------------------------------------------------\n";

	for (unsigned int i = 0; i < files.size(); i++)
	{
		cout << "\tCorrer Instancia No " << i+1 << ": " << files.at(i) << "\n";
		cout << "-----------------------------------------------------------------------\n";
		cout << " - Lexicographical Solution - ";
		cout << "\n-----------------------------------------------------------------------\n";
		LocalSearch b;
		b.initData(files.at(i));
		b.initialLexicographicalSolution();
		b.showResult(files.at(i));
		cout << "\n\n-----------------------------------------------------------------------\n";
		cout << " - Local Search: twoOptMove + randomMove - ";
		cout << "\n-----------------------------------------------------------------------\n";
		QueryPerformanceCounter(&iniTime);		
		
		//b.randomMove();
		//b.twoOptMove();
		//b.randomMove();

		b.randomMove();
		b.twoOptMove();

		//b.twoOptMove();
		//b.randomMove();

		//b.twoOptMove();
		//b.randomMove();
		//b.twoOptMove();
		
		QueryPerformanceCounter(&endTime);
		TotalSecs = b.Performance_Counter_Diff(&endTime, &iniTime);
		b.showResult(files.at(i), TotalSecs);
		//b.showData();
		cout << "\n-----------------------------------------------------------------------\n";
	}

	std::cin.clear();
	return 0;
}

