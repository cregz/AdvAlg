#include "stdafx.h"
#include "SmallestBoundaryPolygonSolver.h"
#include "../Utils/Random.h"


Point SmallestBoundaryPolygonSolver::movePoint(Point p)
{
	Point returnVal = Point(p);
	returnVal.x += randomUniform(-5, 5);
	returnVal.y += randomUniform(-5, 5);
	return returnVal;
}

void SmallestBoundaryPolygonSolver::setBoundaries()
{
	minX = 0;
	maxX = 100;
	minY = 0;
	maxY = 100;
	for (size_t i = 0; i < points.size(); i++)
	{
		Point &p = points.at(i);
		if (p.x > maxX)
			maxX = p.x;
		if (p.x < minX)
			minX = p.x;
		if (p.y > maxY)
			maxY = p.y;
		if (p.y < minY)
			minY = p.y;
	}
}

SmallestBoundaryPolygonSolver::SmallestBoundaryPolygonSolver()
{
	loadPointsFromFile("../Environment/Input/Points.txt");
	setBoundaries();

}


SmallestBoundaryPolygonSolver::~SmallestBoundaryPolygonSolver()
{
}


void SmallestBoundaryPolygonSolver::solve(unsigned numOfPoints, unsigned itermax)
{
	//randomly generate first solution
	for (size_t i = 0; i < numOfPoints; i++)
	{
		Point p;
		p.x = randomUniform(0, 1) == 1 ? minX : randomUniform(maxX, maxX + 10);
		p.y = randomUniform(0, 1) == 1 ? minY : randomUniform(maxY, maxY + 10);
		solution.push_back(p);
	}
	int i = 0;
	while (i < itermax || constraint(solution) < 0) {
		unsigned whichPoint = randomUniform(0, solution.size() - 1);
		float s = constraint(solution);
		float currentSolution = objective(solution);
		Point p = movePoint(solution.at(whichPoint));
		Point temp = solution.at(whichPoint);
		solution.at(whichPoint) = p;
		if ((objective(solution) > currentSolution && constraint(solution) >= 0) || constraint(solution) < s) {
			solution.at(whichPoint) = temp;
		}
		//std::cout << "Solution " << i << ". iter: " << std::endl;
		//printOutPoints(solution);
		//std::cout << std::endl;
		if(s >= 0) 
			i++;
	}
	std::cout << "Solution " << i << ". iter: " << std::endl;
	printOutPoints(solution);
	
}
