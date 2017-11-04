#include "stdafx.h"
#include <string>
#include "SmallestBoundaryPolygonSolver.h"
#include "TravellingSalesmanSolver.h"

int main()
{
	//SmallestBoundaryPolygonSolver solver;
	//solver.solve(20, 10000, true);
	TravellingSalesmanSolver solver;
	solver.solve(100,1000);
    return 0;
}

