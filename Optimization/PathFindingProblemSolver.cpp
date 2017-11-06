#include "stdafx.h"
#include "PathFindingProblemSolver.h"

PathFindingProblemSolver::PathFindingProblemSolver()
{
	loadMapFromFile("../Environment/Input/Map.txt");
}

PathFindingProblemSolver::~PathFindingProblemSolver()
{
}

void PathFindingProblemSolver::generateRandomPopulation(unsigned popSize)
{
	for (size_t i = 0; i < popSize; i++)
	{

	}
}

void PathFindingProblemSolver::Evaluate()
{
}

int PathFindingProblemSolver::selectOperator()
{
	return 0;
}

std::vector<unsigned> PathFindingProblemSolver::selectParents()
{
	return std::vector<unsigned>();
}

std::pair<Program, Program> PathFindingProblemSolver::crossover(const Program & p1, const Program & p2)
{
	return std::pair<Program, Program>();
}

Program::Program()
{
}

const std::vector<int> Program::getMachineCode() const
{
	return machineCode;
}

void Program::mutate()
{
}
