#pragma once
#include "SmallestBoundaryPolygon.h"
#include "../Utils/Animlog.h"

class SmallestBoundaryPolygonSolver :
	public SmallestBoundaryPolygonProblem
{
private:
	Animlog logger;
	std::vector<Point> solution;
	int minX;
	int maxX;
	int minY;
	int maxY;
	Point movePoint(Point p);
	void setBoundaries();
	void generateFirstSolution(unsigned numOfPoints);
public:
	SmallestBoundaryPolygonSolver();
	~SmallestBoundaryPolygonSolver();
	void solve(unsigned numOfPoints, unsigned itermax, bool isLoggingToFile = false);
};

