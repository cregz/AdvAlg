#include "stdafx.h"
#include <string>
#include "SmallestBoundaryPolygonSolver.h"
#include "TravellingSalesmanSolver.h"

int main()
{
	//SmallestBoundaryPolygonSolver solver;
	//solver.solve(5, 100000, true);
	TravellingSalesmanSolver solver;
	solver.solve(250,1000);
    return 0;
}

