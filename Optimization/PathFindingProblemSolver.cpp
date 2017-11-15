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
		int size = randomUniform(4, 20);
		Program child;
		for (size_t j = 0; j < size; j++)
		{
			child.push_back(randomUniform(1,59));
		}
		population.push_back(child);
	}
}

void PathFindingProblemSolver::evaluate(std::vector<Program>& pop)
{
	for (size_t i = 0; i < pop.size(); i++)
	{
		float fitness = objective(pop.at(i).getMachineCode());
		pop.at(i).setFitness(fitness);
	}
}

int PathFindingProblemSolver::selectOperator()
{
	return randomUniform(0, 99);
}

std::vector<Program> PathFindingProblemSolver::selectParents()
{
	std::vector<Program> parents = std::vector<Program>(population.begin(), population.begin() + population.size() / 5);
	for (size_t i = 0; i < 20; i++)
	{
		parents.push_back(population.at(randomUniform((int)population.size() / 5, (int)population.size() -1)));
	}
	return parents;
}

std::pair<Program, Program> PathFindingProblemSolver::crossover(const std::vector<Program>& parents)
{
	unsigned p1 = randomUniform(0, parents.size() - 1);
	unsigned p2 = randomUniform(0, parents.size() - 1);
	while (p1 == p2) {
		p2 = randomUniform(0, parents.size() - 1);
	}
	const Program& paretn1 = parents.at(p1);
	unsigned randomP1 = randomUniform(1, paretn1.getMachineCode().size() - 1);
	const Program& paretn2 = parents.at(p2);
	unsigned randomP2 = randomUniform(1, paretn2.getMachineCode().size() - 1);
	std::vector<int> c1;
	for (size_t i = 0; i < randomP1; i++)
	{
		c1.push_back(paretn1.getMachineCode().at(i));
	}
	for (size_t i = randomP2; i < paretn2.getMachineCode().size()-1; i++)
	{
		c1.push_back(paretn2.getMachineCode().at(i));
	}
	std::vector<int> c2 ;
	for (size_t i = 0; i < randomP2; i++)
	{
		c2.push_back(paretn2.getMachineCode().at(i));
	}
	for (size_t i = randomP1; i < paretn1.getMachineCode().size() - 1; i++)
	{
		c2.push_back(paretn1.getMachineCode().at(i));
	}
	int rnadomLength1 = randomUniform(1, c1.size()-1);
	int rnadomLength2 = randomUniform(1, c2.size()-1);
	if (c1.size() > 100) {
		c1 = std::vector<int>(c1.begin(), c1.begin() + 99);
	}
	if (c2.size() > 100) {
		c2 = std::vector<int>(c2.begin(), c2.begin() + 99);
	}
	//Program child1 = Porgram(std::vector<int>(paretn1.begin(), paretn1))
	return std::pair<Program, Program>(Program(c1, 0), Program(c2,0));
}

void PathFindingProblemSolver::solve(size_t popSize, unsigned iterMax)
{
	generateRandomPopulation(popSize);
	evaluate(population);
	std::sort(population.begin(), population.end(), [](const Program& e1, const Program& e2) {
		return e1.getFitness() < e2.getFitness();
	});
	Program best = population.at(0);
	unsigned i = 0;
	while (i < iterMax && best.getFitness() > 0) {
		std::vector<Program> children;
		while (children.size() < popSize) {
			unsigned op = selectOperator();
			std::vector<Program> parents = selectParents();
			if (op < MUTATIONOP) {
				unsigned parentIdx = randomUniform(0, parents.size() - 1);
				Program child = population.at(parentIdx);
				child.mutate();
				children.push_back(child);
			}
			else if (op < MUTATIONOP + REPRODUCTION) {
				Program child = parents.at(randomUniform(0, parents.size() - 1));
				children.push_back(child);
			}
			else {
				std::pair<Program, Program> twins = crossover(parents);
				children.push_back(twins.first);
				children.push_back(twins.second);
			}
		}
		evaluate(children);
		std::sort(children.begin(), children.end(), [](const Program& e1, const Program& e2) {
			return e1.getFitness() < e2.getFitness();
		});
		best = children.at(0);
		population = children;
		i++;
	}
	logExecution(population.at(0).getMachineCode(), "path.txt");
	std::cout << "End" << std::endl;
}

Program::Program()
{
}

Program::Program(std::vector<int> mc, float f)
{
	machineCode = mc;
	fitness = f;
}

const std::vector<int> Program::getMachineCode() const
{
	return machineCode;
}

void Program::mutate()
{
	int r1 = randomUniform(0, machineCode.size() - 1);
	int r2 = randomUniform(0, machineCode.size() - 1);
	std::iter_swap(machineCode.begin() + r1, machineCode.begin() + r2);
}

void Program::setFitness(float value)
{
	fitness = value;
}

float Program::getFitness() const
{
	return fitness;
}

void Program::push_back(int m)
{
	machineCode.push_back(m);
}
