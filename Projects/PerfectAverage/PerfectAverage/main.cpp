
#include "Solver.h"

int main()
{
	ECG::initType();

	Solver s;

	//s.solve2();

	s.testButterworthFilterECG();

	return 0;
}