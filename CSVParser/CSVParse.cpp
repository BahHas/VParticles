#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <vector>
#include <stdlib.h> // srand, rand

using namespace std;

class parseIt {
	
	private:
		//Declaring Vars
		string e1x, e1y, e1z, e2x, e2y, e2z, e3x, e3y, e3z;

	public:
		vector <double> p1x, p1y, p1z, p2x, p2y, p2z, p3x, p3y, p3z;
		//number of lines
		int i = 0;

		void fillArrays() {
			ifstream eData;
			eData.open("muon5body_data.csv");

			//ignore first line
			string line;
			getline(eData, line);

			while (eData.peek() != EOF) //while the end of file is NOT reached
			{
				//I have 9 sets {e1x, e1y, e1z, e2x, e2y, e2z, e3x, e3y, e3z} so use 9 getlines
				getline(eData, e1x, ',');
				p1x.push_back(stod(e1x));
				getline(eData, e1y, ',');
				p1y.push_back(stod(e1y));
				getline(eData, e1z, ',');
				p1z.push_back(stod(e1z)); //electron 1 momenta
				getline(eData, e2x, ',');
				p2x.push_back(stod(e2x));
				getline(eData, e2y, ',');
				p2y.push_back(stod(e2y));
				getline(eData, e2z, ',');
				p2z.push_back(stod(e2z)); //electron 2 momenta
				getline(eData, e3x, ',');
				p3x.push_back(stod(e3x));
				getline(eData, e3y, ',');
				p3y.push_back(stod(e3y));
				getline(eData, e3z, '\n'); //new line after z-momentum of the third electron
				p3z.push_back(stod(e3z)); //electron 3 momenta

				i += 1; //increment number of lines
			}
			eData.close(); // closing the file

		};

		void getParticles(int timesRun, double* dataArray) {
			dataArray[0] = p1x[timesRun];
			dataArray[1] = p1y[timesRun];
			dataArray[2] = p1z[timesRun];
			dataArray[3] = p2x[timesRun];
			dataArray[4] = p2y[timesRun];
			dataArray[5] = p2z[timesRun];
			dataArray[6] = p3x[timesRun];
			dataArray[7] = p3y[timesRun];
			dataArray[8] = p3z[timesRun];

		};

		void getRandomParticles(double* dataArray) {
			srand(time(NULL));
			int electronSample = rand() % 10000 + 0; //generates random number from 0 to 10,000 (total of 10,001)

			dataArray[0] = p1x[electronSample];
			dataArray[1] = p1y[electronSample];
			dataArray[2] = p1z[electronSample];
			dataArray[3] = p2x[electronSample];
			dataArray[4] = p2y[electronSample];
			dataArray[5] = p2z[electronSample];
			dataArray[6] = p3x[electronSample];
			dataArray[7] = p3y[electronSample];
			dataArray[8] = p3z[electronSample];
		}

};

int main(int argc, char *argv[]) {
	
	parseIt pI;

	ifstream eData;
	eData.open("muon5body_data.csv");

	if (eData.is_open()) //if the file is open
	{
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
				std::cout << '\n' <<"e1 is positivly charged, e2 and e3 are the negatively charged electrons. x,y,z are momenta directions." << '\n' << endl;
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
		else std::cout << "Error: Unable to open file.  Make sure it is in the same directory or explicitly specify directory of file"; //if the file is not open output

}