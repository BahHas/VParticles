#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <vector>
#include <stdlib.h> // srand, rand
#include "parseIt.h"


int main(int argc, char* argv[]) {

	parseIt pI;

	pI.fillArrays();

	if (argc == 1) // non-randomized output
	{
		int indexTimesRun = 0;
		double arr[9];

		pI.getParticles(indexTimesRun, arr);

		std::cout << '\n' << "Non-random electron sample:" << '\n';
		std::cout << "e1 px" << "\t" << "\t" << "e1 py" << "\t" << "\t" << "e1 pz" << "\t" << "\t" << "e2 px" << "\t" << "\t" << "e2 py" << "\t" << "\t" << "e2 pz" << "\t" << "\t" << "e3 px" << "\t" << "\t" << "e3 py" << "\t" << "\t" << "e3 pz" << endl;
		//std::cout << p1x[0] << "\t" << p1y[0] << "\t" << p1z[0] << "\t" << p2x[0] << "\t" << p2y[0] << "\t" << p2z[0] << "\t" << p3x[0] << "\t" << p3y[0] << "\t" << p3z[0] << '\n' << endl;

		for (int k = 0; k < 9; k++) {
			std::cout << arr[k] << "\t";
		}
		std::cout << endl;
	}

	else if (argc > 1)
	{
		string randomFlag = "rn"; // flags
		string theBank = "bank";
		string howTo = "usage";

		// randomized output
		if (argv[1] == randomFlag) {
			double randArr[9];

			pI.getRandomParticles(randArr);

			std::cout << '\n' << "Random electron sample:" << endl;
			std::cout << "e1 px" << "\t" << "\t" << "e1 py" << "\t" << "\t" << "e1 pz" << "\t" << "\t" << "e2 px" << "\t" << "\t" << "e2 py" << "\t" << "\t" << "e2 pz" << "\t" << "\t" << "e3 px" << "\t" << "\t" << "e3 py" << "\t" << "\t" << "e3 pz" << endl;
			for (int k = 0; k < 9; k++) {
				std::cout << randArr[k] << "\t";
			}
			std::cout << endl;
		}

		// Printing the electron bank
		else if (argv[1] == theBank) {
			std::cout << '\n' << "e1 px" << "\t" << "\t" << "e1 py" << "\t" << "\t" << "e1 pz" << "\t" << "\t" << "e2 px" << "\t" << "\t" << "e2 py" << "\t" << "\t" << "e2 pz" << "\t" << "\t" << "e3 px" << "\t" << "\t" << "e3 py" << "\t" << "\t" << "e3 pz" << endl;
			for (int j = 0; j < pI.i; j++)
			{
				std::cout << pI.p1x[j] << "\t" << pI.p1y[j] << "\t" << pI.p1z[j] << "\t" << pI.p2x[j] << "\t" << pI.p2y[j] << "\t" << pI.p2z[j] << "\t" << pI.p3x[j] << "\t" << pI.p3y[j] << "\t" << pI.p3z[j] << endl;
			}
			std::cout << endl;
		}

		// help menu
		else if (argv[1] == howTo) {
			std::cout << "-----------------------------------------------------------------------------------------------------" << endl;
			std::cout << '\n' << "e1 is positivly charged, e2 and e3 are the negatively charged electrons. x,y,z are momenta directions." << '\n' << endl;
			std::cout << "The bank of electron decay momenta currently has " << pI.p1x.size() << " events in it." << '\n' << endl;
			std::cout << "Flags/Options: " << '\n' << "rn" << '\t' << "For a random set of electron momenta." << '\n' << "bank" << '\t' << "To print the entire 10,000 bank of electron momenta." << '\n' << "usage" << '\t' << "Brings up this help section." << '\n' << endl;
			std::cout << "With no flag, program will return a non-random set of electron momenta." << '\n' << endl;
			std::cout << "-----------------------------------------------------------------------------------------------------" << endl;
		}

		//user mistake
		else
		{
			std::cout << "Unknown flag used" << endl;
		}

	}

}