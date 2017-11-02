#include "stdafx.h"
#include "SmallestBoundaryPolygonSolver.h"
#include "../Utils/Random.h"
#include <functional>
#include <numeric>
#include <algorithm>

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
	loadPointsFromFile("C:\\Users\\I345182\\source\\repos\\AdvAlg\\Bin\\Environment\\Input\\Points.txt");
	setBoundaries();

}


SmallestBoundaryPolygonSolver::~SmallestBoundaryPolygonSolver()
{
}

void SmallestBoundaryPolygonSolver::generateFirstSolution(unsigned numOfPoints){
	//generate numOfPoints random points outside the bounding box
	for (size_t i = 0; i < numOfPoints; i++)
	{
		Point p;
		int xOrY = randomUniform(0, 1);
		if (xOrY == 0) {
			p.x = randomUniform(0, 1) == 1 ? minX : randomUniform(maxX, maxX + 10);
			p.y = randomUniform(minY, maxY);
		}
		else {
			p.x = randomUniform(minX, maxX);
			p.y = randomUniform(0, 1) == 1 ? minY : randomUniform(maxY, maxY + 10);
		}
		solution.push_back(p);
	}
	float avgX = solution.at(0).x;
	float avgY = solution.at(0).y;
	for (size_t i = 1; i < numOfPoints; i++)
	{
		Point& p = solution.at(i);
		avgX += p.x;
		avgY += p.y;
	}
	avgX /= solution.size();
	avgY /= solution.size();

	//sort the random points clockwise
	std::sort(solution.begin(), solution.end(), [avgX, avgY] (Point f, Point s){
		if (f.x - avgX >= 0 && s.x - avgX < 0)
			return true;
		if (f.x - avgX < 0 && s.x - avgX >= 0)
			return false;
		if (f.x - avgX == 0 && s.x - avgX == 0) {
			if (f.y - avgY >= 0 || s.y - avgY >= 0) {
				return f.y > s.y;
			}
			return s.y > f.y;
		}

		//cross product center -> a x center -> b
		float det = (f.x - avgX) * (s.y - avgY) - (s.x - avgX) * (f.y - avgY);
		if (det < 0)
			return true;
		if (det > 0)
			return false;

		// points a and b are on the same line from the center
		// check which point is closer to the center
		float d1 = (f.x - avgX) * (f.x - avgX) + (f.y - avgY) * (f.y - avgY);
		float d2 = (s.x - avgX) * (s.x - avgX) + (s.y - avgY) * (s.y - avgY);
		return d1 > d2;
	});

}

void SmallestBoundaryPolygonSolver::solve(unsigned numOfPoints, unsigned itermax)
{
	//randomly generate first solution
	generateFirstSolution(numOfPoints);
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
		
		if(s >= 0) 
			i++;
	}
	std::cout << "Solution " << i << ". iter: " << std::endl;
	printOutPoints(solution);
	
}
