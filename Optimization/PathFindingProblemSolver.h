#pragma once
#include "PathFinding.h"

class Program {
private:
	std::vector<int> machineCode;
public:
	Program();
	const std::vector<int> getMachineCode() const;
	void mutate();

};

class PathFindingProblemSolver : public PathFindingProgrammingProblem {
private:
	std::vector<Program> population;
	void generateRandomPopulation(unsigned popSize);
	void Evaluate();
	int selectOperator();
	std::vector<unsigned> selectParents();
	std::pair<Program, Program> crossover(const Program& p1, const Program& p2);
	void solve(size_t popSize);
public:
	PathFindingProblemSolver();
	~PathFindingProblemSolver();

	
	
};