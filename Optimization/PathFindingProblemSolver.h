#pragma once
#include "PathFinding.h"
#include <algorithm>
#include "../Utils/Random.h"

class Program {
private:
	std::vector<int> machineCode;
	float fitness;
public:
	Program();
	Program(std::vector<int> mc, float f);
	const std::vector<int> getMachineCode() const;
	void mutate();
	void setFitness(float value);
	float getFitness() const;
	void push_back(int m);
};

class PathFindingProblemSolver : public PathFindingProgrammingProblem {
private:
	std::vector<Program> population;
	void generateRandomPopulation(unsigned popSize);
	void evaluate(std::vector<Program>& pop);
	int selectOperator();
	std::vector<Program> selectParents();
	std::pair<Program, Program> crossover(const std::vector<Program>& parents);
	
public:
	PathFindingProblemSolver();
	~PathFindingProblemSolver();

	void solve(size_t popSize, unsigned iterMax);
	const int CROSSOVEROP = 94;
	const int MUTATIONOP = 2;
	const int REPRODUCTION = 100 - (CROSSOVEROP + MUTATIONOP);

	
	
};