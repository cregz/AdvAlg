#include "stdafx.h"
#include "TravellingSalesmanSolver.h"


void TravellingSalesmanSolver::initPop(unsigned populationSize)
{
	for (size_t i = 0; i < populationSize; i++)
	{
		Path elem = Path(towns);
		elem.randomize();
		population.push_back(elem);
	}
}

std::vector<unsigned> TravellingSalesmanSolver::selectParents(unsigned matingPoolSize)
{
	std::vector<unsigned> returnVal(matingPoolSize);
	std::iota(std::begin(returnVal), std::end(returnVal), 0);
	return returnVal;
}

std::vector<std::pair<unsigned, unsigned>> TravellingSalesmanSolver::generatePairs(const std::vector<unsigned>& parents)
{
	std::vector<std::pair<unsigned, unsigned>> returnVal;
	for (size_t i = 0; i < parents.size()-1; i++)
	{
		for (size_t j = i; j < parents.size(); j++)
		{
			std::pair<unsigned, unsigned> p = std::pair<unsigned, unsigned>(i, j);
			returnVal.push_back(p);
		}
	}
	return returnVal;
}

void TravellingSalesmanSolver::mutate(Path& child)
{
	int shouldMutate = randomUniform(0, 1);
	if (shouldMutate == 0) {
		child.mutate();
	}
}

void TravellingSalesmanSolver::evaluate(std::vector<Path>& pops)
{
	std::vector<float> returnVal;
	for (size_t i = 0; i<pops.size(); i++)
	{
		float fitness = objective(pops.at(i).getPath());
		pops.at(i).setFitness( fitness);
	}
}

std::pair<Path, Path> TravellingSalesmanSolver::singlePointCrossover(const Path& p1, const Path& p2) {
	std::vector<Town> c1;
	std::vector<Town> c2;
	std::vector<Town> temp;
	unsigned point = randomUniform((int)(p1.getPath().size() / 3), (int)(p1.getPath().size() / 3)*2);
	size_t i = 0;
	for (; i < point; i++)
	{
		c1.push_back(p1.getPath().at(i));
		c2.push_back(p2.getPath().at(i));
	}
	for (; i < p1.getPath().size(); i++)
	{
		c1.push_back(p2.getPath().at(i));
		c2.push_back(p1.getPath().at(i));
	}

	Path child1 = Path(c1);
	Path child2 = Path(c2);
	std::pair<Path, Path> twins = std::pair<Path, Path>(child1, child2);

	return twins;
}

TravellingSalesmanSolver::TravellingSalesmanSolver()
{
	loadTownsFromFile("../Environment/Input/Towns.txt");
}


TravellingSalesmanSolver::~TravellingSalesmanSolver()
{
}

void TravellingSalesmanSolver::solve(unsigned populationSize, unsigned itermax)
{
	initPop(populationSize);
	evaluate(population);
	std::sort(population.begin(), population.end(), [](const Path& p1, const Path& p2) {
		return p1.getFitness() < p2.getFitness();
	});
	Path& bestSolution = population.at(0);
	unsigned i = 0;
	unsigned matingPoolSize = populationSize / 2;
	while (i < itermax) {
		std::vector<unsigned> parents = selectParents(matingPoolSize);
		std::vector<std::pair<unsigned, unsigned>> parentPairs = generatePairs(parents);
		std::vector<Path> children;
		for (size_t i = 0; i < populationSize / 2; i++)
		{
			int whichParents = randomUniform(0, parentPairs.size()-1);
			auto& parent1 = population.at(parentPairs.at(whichParents).first);
			auto& parent2 = population.at(parentPairs.at(whichParents).second);
			std::pair<Path, Path> child = singlePointCrossover(parent1, parent2);
			mutate(child.first);
			mutate(child.second);
			children.push_back(child.first);
			children.push_back(child.second);
		}
		evaluate(children);
		std::sort(children.begin(), children.end(), [](const Path& p1, const Path& p2) {
			return p1.getFitness() < p2.getFitness();
		});
		bestSolution = children.at(0);
		population = children;
		std::cout << population.at(0).getFitness() << std::endl;
		i++;
	}
	std::cout << "Best solution: " << std::endl << population.at(0).getFitness() << std::endl;
	printOutTowns(population.at(0).getPath());
}

Town & Path::at(size_t i)
{
	return path.at(i);
}

void Path::push_back(Town t)
{
	path.push_back(t);
}

Path::Path(std::vector<Town> path)
	:path(path)
{
}

Path::Path(const Path & other)
{
	path = other.getPath();
	fitness = other.getFitness();
}

void Path::randomize()
{
	std::random_shuffle(path.begin(), path.end());
}

const std::vector<Town>& Path::getPath() const
{
	return path;
}

void Path::setFitness(float value)
{
	fitness = value;
}

float Path::getFitness() const
{
	return fitness;
}

void Path::mutate()
{
	size_t n1 = randomUniform(0, path.size() - 1);
	size_t n2 = randomUniform(0, path.size() - 1);
	std::iter_swap(path.begin() + n1, path.begin() + n2);
}
