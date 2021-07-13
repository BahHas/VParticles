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
		if (eData.is_open()) //if the file is open
		{
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
		}
		else std::cout << "Error: Unable to open file.  Make sure it is in the same directory or explicitly specify directory of file"; //if the file is not open output
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