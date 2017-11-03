#include "stdafx.h"
#include <string>
#include "SmallestBoundaryPolygonSolver.h"

int main()
{
	SmallestBoundaryPolygonSolver solver;
	solver.solve(5, 100000, true);
    return 0;
}

