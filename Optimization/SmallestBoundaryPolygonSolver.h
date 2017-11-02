#pragma once
#include "SmallestBoundaryPolygon.h"

class SmallestBoundaryPolygonSolver :
	public SmallestBoundaryPolygonProblem
{
private:
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
	void solve(unsigned numOfPoints, unsigned itermax);
};

