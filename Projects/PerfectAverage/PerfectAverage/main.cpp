
#include "Solver.h"
#include "SolverForNN.h"
#include "SolverForNN2.h"

int main()
{
	ECG::initType();

	Solver s;

	SolverForNN s2;

	SolverForNN2 s3;

	//s.drawECG();

	//s.solve1();
	//s.solve2();
	//s.solve3();

	//s.testButterworthFilterECG();

	//s.makeRPeaksCSV2();

	//s.calcAlgorithmStatsCSV2();
	
	//s.drawPartWrap();

	//s.computeRPeaksDetectionResults();

	//s.analyzeComputedStats1();

	//s.analyzeComputedStats2();

	//s.analyzeComputedStats3();

	//s.makeDataForNoisyClasification();
	//s.makeDataForNoisyClasification2();
	//s.makeDataForNoisyClasification3();

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
	//s2.p_test2();

	
	//s3.makeClassificationData();
	
	//s3.makeDataForNvsAF();
	//s3.makeDataForNvsO();
	//s3.makeDataForAFvsO();
	
	//s3.makeDataForNAFvsO();
	//s3.makeDataForNOvsAF();
	//s3.makeDataForNvsAFO();

	s3.makeDataForNvsAFvsO();

	return 0;
}