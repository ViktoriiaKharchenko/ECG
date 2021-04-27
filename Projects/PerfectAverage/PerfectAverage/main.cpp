
#include "Solver.h"
#include "SolverForNN.h"

int main()
{
	ECG::initType();

	Solver s;

	SolverForNN s2;

	//s.drawECG();

	//s.solve3();

	//s.makeRPeaksCSV2();

	//s.calcAlgorithmStatsCSV2();

	//s.computeRPeaksDetectionResults();

	//s.analyzeComputedStats1();

	//s.analyzeComputedStats2();

	//s.analyzeComputedStats3();

	//s.makeDataForMoisyClasification();
	//s.makeDataForMoisyClasification2();
	//s.makeDataForMoisyClasification3();

	//s.makeDataForNoisyModel();
	//s.makeDataAFvsNormalScaled();

	//s.combineNoisyPrediction();



	//s2.makeClassificationData();
	
	//s2.makeDataForNvsAF();
	//s2.makeDataForNvsO();
	//s2.makeDataForAFvsO();

	//s2.makeDataForNAFvsO();
	//s2.makeDataForNOvsAF();
	//s2.makeDataForAFOvsN();

	//s2.makeDataForNvsAFvsO();

	//s2.test1_1();
	//s2.test1_2();
	//s2.test2();

	//s2.p_test1_1();
	//s2.p_test1_2();
	s2.p_test2();

	return 0;
}