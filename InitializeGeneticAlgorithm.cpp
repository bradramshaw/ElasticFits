#include "stdafx.h"
#include "GeneticAlgorithm.h"

void GeneticAlgorithm::initializeRandomNumberGenerators(){
	SYSTEMTIME t;
	GetLocalTime(&t);
	unsigned int max = _nPopulation - 1;

	vslNewStream( & stream, VSL_BRNG_SFMT19937, t.wMilliseconds );
	ints1 = new int[_nPopulation];
    ints2 = new int[_nPopulation];
    ints3 = new int[_nPopulation];
	shuffleIndex = new int[_nPopulation];
}

void GeneticAlgorithm::initialiseMatrices(){
	_emat = calcEmat(_R, _basis);

	int address = 0;
	int addresses[8];
			
		for(int i = 0; i < 8; i ++){
			addresses[i] = address;
			address += (_basisPop[i])*(_R+1);
		}
		
		
		
		for(int i = 0; i < 8; i++){
		
			int ch0 = LAPACKE_dpotrf(LAPACK_ROW_MAJOR, 'U', _basisPop[i], &_emat[addresses[i]], _R);

			
		}


	_gradientCalcs = calcGradient(_R,_basis);
	return;
}

void GeneticAlgorithm::initializeParameters(double* dataSet, int dataSetLength, int nPopulation, double scaleFactor, double crossingProbability){

	_scaleFactor = scaleFactor;
	_crossingProbability = crossingProbability;
	_dataSetLength = dataSetLength;
	_dataSet = dataSet;

	_residualArray = new double*[nThreads];
	_paramArray = new double*[nThreads];
	for(int i = 0; i < nThreads; i++){
	_residualArray[i] = new double[_dataSetLength];
	_paramArray[i] = new double[nParams];

	}
	
	_populationParametersOld = (Parameters::fitParameters *) mkl_malloc(sizeof(Parameters::fitParameters)*nPopulation,16);
	_populationParametersNew = (Parameters::fitParameters *) mkl_malloc(sizeof(Parameters::fitParameters)*nPopulation,16);
	for(int i  = 0; i < _nPopulation; i++){
		
		_populationParametersOld[i].missFreq = new long[_nMissing];
		_populationParametersNew[i].missFreq = new long[_nMissing];


		
	/*	_populationParametersOld[i].c11 = (randomDouble(196,196.1))*pow(10,9);
		_populationParametersOld[i].c22 = _populationParametersOld[i].c11;
		
		_populationParametersOld[i].c33 = (randomDouble(187,187.1))*pow(10,9);

		_populationParametersOld[i].c44 = (randomDouble(63.5,63.6))*pow(10,9);
		_populationParametersOld[i].c55 = _populationParametersOld[i].c44;
		
		_populationParametersOld[i].c66 = (randomDouble(55.7,55.8))*pow(10,9);

		_populationParametersOld[i].c12 = (randomDouble(62.5,62.6))*pow(10,9);
	
		_populationParametersOld[i].c13 = (randomDouble(69.8,69.9))*pow(10,9);
		_populationParametersOld[i].c23 = _populationParametersOld[i].c13; 

		_populationParametersOld[i].chiSq = calculateResidual(&_populationParametersOld[i],0);/// ***Tetragonal PuCoGa5*/
			
	/*	_populationParametersOld[i].c11 = (randomDouble(260,300))*pow(10,9);
		_populationParametersOld[i].c22 = _populationParametersOld[i].c11;
		
		_populationParametersOld[i].c33 = (randomDouble(290,320))*pow(10,9);

		_populationParametersOld[i].c44 = (randomDouble(90,110))*pow(10,9);
		_populationParametersOld[i].c55 = _populationParametersOld[i].c44;
		
		_populationParametersOld[i].c66 = (randomDouble(130,150))*pow(10,9);

		_populationParametersOld[i].c12 = (randomDouble(140,165))*pow(10,9);
	
		_populationParametersOld[i].c13 = (randomDouble(100,130))*pow(10,9);
		_populationParametersOld[i].c23 = _populationParametersOld[i].c13; 

		_populationParametersOld[i].chiSq = calculateResidual(&_populationParametersOld[i],0);/// ***Tetragonal URu2Si2
*/

		_populationParametersOld[i].c11 = (randomDouble(220,260))*pow(10,9);
		_populationParametersOld[i].c22 = (randomDouble(210,250))*pow(10,9);
		
		_populationParametersOld[i].c33 = (randomDouble(100,150))*pow(10,9);

		_populationParametersOld[i].c44 = (randomDouble(32,38))*pow(10,9);
		_populationParametersOld[i].c55 = (randomDouble(48,52))*pow(10,9);
		
		_populationParametersOld[i].c66 = (randomDouble(94,98))*pow(10,9);

		_populationParametersOld[i].c12 = (randomDouble(100,150))*pow(10,9);
	
		_populationParametersOld[i].c13 = (randomDouble(25,60))*pow(10,9);
		_populationParametersOld[i].c23 = (randomDouble(20,70))*pow(10,9);

		_populationParametersOld[i].chiSq = calculateResidual(&_populationParametersOld[i],0);/// ***Orthorhombic YBCO67

		//_populationParametersOld[i].c11 = (randomDouble(1,400))*pow(10,9);
		//_populationParametersOld[i].c22 = _populationParametersOld[i].c11;
		//_populationParametersOld[i].c33 = _populationParametersOld[i].c11;
		//
		//_populationParametersOld[i].c44 = (randomDouble(1,400))*pow(10,9);
		//_populationParametersOld[i].c55 = _populationParametersOld[i].c44;		
		//_populationParametersOld[i].c66 = _populationParametersOld[i].c44;

		//_populationParametersOld[i].c12 = (randomDouble(1,400))*pow(10,9);	
		//_populationParametersOld[i].c13 = _populationParametersOld[i].c12; 
		//_populationParametersOld[i].c23 = _populationParametersOld[i].c12; 

		//_populationParametersOld[i].chiSq = calculateResidual(&_populationParametersOld[i],0);/// ***Cubic Nb

		//_populationParametersOld[i].c11 = (randomDouble(120,200))*pow(10,9);
		//_populationParametersOld[i].c22 = _populationParametersOld[i].c11;
		//
		//_populationParametersOld[i].c33 = (randomDouble(120,200))*pow(10,9);

		//_populationParametersOld[i].c44 = (randomDouble(10,100))*pow(10,9);
		//_populationParametersOld[i].c55 = _populationParametersOld[i].c44;
		//
		//_populationParametersOld[i].c66 = (randomDouble(10,100))*pow(10,9);

		//_populationParametersOld[i].c12 = (randomDouble(10,100))*pow(10,9);
	
		//_populationParametersOld[i].c13 = (randomDouble(10,100))*pow(10,9);
		//_populationParametersOld[i].c23 = _populationParametersOld[i].c13; 

		//_populationParametersOld[i].chiSq = calculateResidual(&_populationParametersOld[i],0);/// ***Tetragonal CeCoIn5

	
	}

		_minimumParameters.c11 = 1;
		_minimumParameters.c22 = 1;
		_minimumParameters.c33 = 1;
		_minimumParameters.c44 = 1;
		_minimumParameters.c55 = 1;
		_minimumParameters.c66 = 1;
		_minimumParameters.c12 = 1;
		_minimumParameters.c13 = 1;
		_minimumParameters.c23 = 1;

		_minimumParameters.chiSq = std::numeric_limits<double>::infinity();

		_minimumParameters.missFreq = new long[_nMissing];
}

void GeneticAlgorithm::resetParameters(int nPopulation, double scaleFactor, double crossingProbability){
	_scaleFactor = scaleFactor;
	_crossingProbability = crossingProbability;
	_nPopulation = nPopulation;
	delete [] _populationParametersOld;
	delete [] _populationParametersNew;

	_populationParametersOld = (Parameters::fitParameters *) mkl_malloc(sizeof(Parameters::fitParameters)*nPopulation,16);
	_populationParametersNew = (Parameters::fitParameters *) mkl_malloc(sizeof(Parameters::fitParameters)*nPopulation,16);

	for(int i  = 0; i < _nPopulation; i++){
		_populationParametersOld[i].c11 = (randomDouble(0.0,1.0))*pow(10,9);
		_populationParametersOld[i].c22 = _populationParametersOld[i].c11;
		_populationParametersOld[i].c33 = _populationParametersOld[i].c11;
		_populationParametersOld[i].c44 = (randomDouble(0.0,1.0))*pow(10,9);
		_populationParametersOld[i].c55 = _populationParametersOld[i].c44;
		_populationParametersOld[i].c66 = _populationParametersOld[i].c44;
		_populationParametersOld[i].c12 = (randomDouble(0.0,1.0))*pow(10,9);
		_populationParametersOld[i].c13 = _populationParametersOld[i].c12;
		_populationParametersOld[i].c23 = _populationParametersOld[i].c12;
		_populationParametersOld[i].chiSq = 1;
		_populationParametersOld[i].chiSq = calculateResidual(&_populationParametersOld[i],0);
	}

	//delete _integerDistribution;
	delete [] ints1;
	delete [] ints2;
	delete [] ints3;

	ints1 = new int[_nPopulation];
    ints2 = new int[_nPopulation];
    ints3 = new int[_nPopulation];
	
}

double GeneticAlgorithm::randomDouble(double min, double max){				//change this to return full aray: faster
	double randNum;
	 vdRngUniform(VSL_RNG_METHOD_UNIFORM_STD, stream, 1, &randNum, min, max);
	return randNum;
}


double **** GeneticAlgorithm::initElasticConstants(double * parameters){  // I shouldn't be storing this as a 4d array but it's easy this way
	double **** ctens;
		ctens = new double***[3];
		for(int i = 0; i <3; i++){
			ctens[i] = new double**[3];
				for(int j = 0; j<3; j++){
					ctens[i][j] = new double*[3];
					for(int k = 0; k<3; k++){
						ctens[i][j][k] = new double[3];
					}
				}
		}


		for(int i = 0; i < 3; i++){ //innitialize all entries to zero. this should be incorporated above obviously...
			for(int j = 0; j<3; j++){
				for(int k = 0; k<3; k++){
					for(int l = 0; l<3; l++){
						ctens[i][j][k][l] = 0;
					}
				}
			}
		}
		// note that the following takes care of symmetry, ie c_yzyz = c_zyzy = c_zyyz = c_yzzy
		ctens[0][0][0][0] = parameters[0];
	    ctens[0][0][1][1] = parameters[6];
		ctens[1][1][0][0] = parameters[6];
		ctens[0][0][2][2] = parameters[7];
		ctens[2][2][0][0] = parameters[7];
		ctens[1][1][1][1] = parameters[1];
		ctens[2][2][2][2] = parameters[2];
		ctens[2][2][1][1] = parameters[8];
		ctens[1][1][2][2] = parameters[8];

		ctens[1][2][1][2] = parameters[3];
		ctens[2][1][2][1] = parameters[3];
		ctens[2][1][1][2] = parameters[3];
		ctens[1][2][2][1] = parameters[3];
		
		ctens[2][0][2][0] = parameters[4];
		ctens[0][2][2][0] = parameters[4];
		ctens[0][2][0][2] = parameters[4];
		ctens[2][0][0][2] = parameters[4];

		ctens[0][1][0][1] = parameters[5];
		ctens[1][0][0][1] = parameters[5];
		ctens[0][1][1][0] = parameters[5];
		ctens[1][0][1][0] = parameters[5];

		return ctens;
}

