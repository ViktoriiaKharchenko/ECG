
#include "Solver.h"

int main()
{
	ECG::initType();

	Solver s;

	s.solve3();

	//s.testButterworthFilterECG();

	return 0;
}