#pragma once
#include "TravellingSalesman.h"
#include <algorithm>
#include <memory>
#include <numeric>
#include <iterator>
#include "../Utils/Random.h"

class Path {
private:
	std::vector<Town> path;
	float fitness;
public:
	Town& at(size_t i);
	void push_back(Town);
	Path(std::vector<Town> path);
	Path(const Path& other);
	void randomize();
	const std::vector<Town>& getPath() const;
	void setFitness(float value);
	float getFitness() const;
	void mutate();
};

class TravellingSalesmanSolver :
	public TravellingSalesmanProblem
{
private:
	std::vector<Path> population;
	void initPop(unsigned populationSize);
	std::vector<unsigned> selectParents(unsigned matingPoolSize);

	std::vector<std::pair<unsigned, unsigned>> generatePairs(const std::vector<unsigned>& parents);
	void mutate(Path& child);
	std::pair<Path, Path> singlePointCrossover(const Path& p1, const Path& p2);
	void evaluate(std::vector<Path>& pops);
public:
	TravellingSalesmanSolver();
	~TravellingSalesmanSolver();

	void solve(unsigned populationSize, unsigned itermax);
};

