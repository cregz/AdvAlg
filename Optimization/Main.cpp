#include "stdafx.h"
#include <string>
#include "SmallestBoundaryPolygonSolver.h"

int main()
{
	SmallestBoundaryPolygonSolver solver;
	std::cout << "Solution: " << std::endl;
	solver.solve(8, 200000);
    return 0;
}

