
#include "Solver.h"

int main()
{
	ECG::initType();

	Solver s;

	s.makeRPeaksCSV2();

	//s.calcAlgorithmStatsCSV2();

	return 0;
}