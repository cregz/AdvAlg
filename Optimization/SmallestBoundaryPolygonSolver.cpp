#include "stdafx.h"
#include "SmallestBoundaryPolygonSolver.h"
#include "../Utils/Random.h"
#include <functional>
#include <numeric>
#include <algorithm>

Point SmallestBoundaryPolygonSolver::movePoint(Point p)
{
	Point returnVal = Point(p);  //make copy
	bool isUnique = false;
	do {
		Point temp = Point(returnVal);
		temp.x += randomUniform(-10, 10);
		temp.y += randomUniform(-10, 10);
		auto asd = std::find_if(solution.begin(), solution.end(), [&temp](const Point& elem) {return elem.x == temp.x && elem.y == temp.y; });
		if (asd == std::end(solution)) {
			isUnique = true;
			returnVal = temp;
		}

	} while (!isUnique);
	
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
	: logger("smallestBoundary.txt")
{
	loadPointsFromFile("../Environment/Input/Points.txt");
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
		bool isUnique = false;
		do {
			int xDiff = maxX - minX;
			int yDiff = maxY - minY;
			int x = randomUniform(minX-100, maxX+100);
			int y = randomUniform(minY-100, maxY+100);
			int xOrY = randomUniform(0, 2);
			if (xOrY == 0 || xOrY == 2) {
				if (x <= xDiff / 2 + minX)
					x -= (int)xDiff / 2;
				else
					x += (int)xDiff / 2;
			}
			if (xOrY == 1 || xOrY == 2) {
				if (y <= yDiff / 2 + minY)
					y -= (int)yDiff / 2;
				else
					y += (int)yDiff / 2;
			}
			p.x = x;
			p.y = y;
			if (solution.size() != 0) {
				auto asd = std::find_if(solution.begin(), solution.end(), [&p](const Point& elem) {return elem.x == p.x && elem.y == p.y; });
				if (asd == std::end(solution))
					isUnique = true;
			}
			else {
				isUnique = true;
			}
		} while (!isUnique);
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

		//cross product (center -> a) x (center -> b)
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

void SmallestBoundaryPolygonSolver::solve(unsigned numOfPoints, unsigned itermax, bool isLoggingToFile)
{
	//randomly generate first solution
	generateFirstSolution(numOfPoints);
	int i = 0;
	if (isLoggingToFile) {
		for (auto& p : points) {
			logger.putPoint(p.x, p.y, "red");
		}
	}
	while (constraint(solution) < 0) {
		unsigned whichPoint = randomUniform(0, solution.size() - 1);
		float s = constraint(solution);
		float currentSolution = objective(solution);
		Point p = movePoint(solution.at(whichPoint));
		Point temp = solution.at(whichPoint);
		solution.at(whichPoint) = p;
		if (constraint(solution) < s) {
			solution.at(whichPoint) = temp;
		}
	}
	logger.putInfo("Starting");
	while (i < itermax) {
		unsigned whichPoint = randomUniform(0, solution.size() - 1);
		float s = constraint(solution);
		float currentSolution = objective(solution);
		if (isLoggingToFile) {
			logger.putIteration(i);
			logger.putFitness(currentSolution);
			logger.putInfo(std::to_string(s));
			for (auto& p : solution) {
				logger.putPoint(p.x, p.y, "green");
			}
		}
		Point p = movePoint(solution.at(whichPoint));
		Point temp = solution.at(whichPoint);
		solution.at(whichPoint) = p;
		if (objective(solution) > currentSolution || constraint(solution) < s )  {
			solution.at(whichPoint) = temp;
		}
	
		i++;
	}
	if (isLoggingToFile) {
		logger.putIteration(i);
		logger.putFitness(objective(solution));
		for (auto& p : solution) {
			logger.putPoint(p.x, p.y, "green");
		}
	}
	std::cout << "Solution " << i << ". iter: " << std::endl;
	std::cout << "Fitness: " << objective(solution) << std::endl;
	printOutPoints(solution);
}
