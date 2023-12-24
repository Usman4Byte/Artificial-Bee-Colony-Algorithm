#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <windows.h>

using namespace std;

double calculateFitness(double solution, double target) 
{
    return pow(solution + target, 2.0);
}

void initializeBees(double* positions, double* fitnessValues, int colonySize) 
{
    for (int i = 0; i < colonySize; i++) 
	{
        positions[i] = (rand() % 2000 - 1000) / 100.0; // Random values between -10 and 10
        fitnessValues[i] = calculateFitness(positions[i], 4.0);
    }
}

void employedBeePhase(double* positions, double* fitnessValues, int colonySize) 
{
    for (int i = 0; i < colonySize; i++) 
	{
        double newPosition = positions[i] + (rand() % 200 - 100) / 100.0; // Small random change
        double newFitness = calculateFitness(newPosition, 4.0);

        if (newFitness > fitnessValues[i]) 
		{
            positions[i] = newPosition;
            fitnessValues[i] = newFitness;
        }
    }
}

void onlookerBeePhase(double* positions, double* fitnessValues, int colonySize) 
{
    double totalFitness = 0.0;
    for (int i = 0; i < colonySize; i++) 
	{
        totalFitness += fitnessValues[i];
    }

    for (int i = 0; i < colonySize; i++) 
	{
        double probability = fitnessValues[i] / totalFitness;

        if ((rand() % 100) / 100.0 < probability) 
		{
            double newPosition = positions[i] + (rand() % 200 - 100) / 100.0;
            double newFitness = calculateFitness(newPosition, 4.0);

            if (newFitness > fitnessValues[i]) 
			{
                positions[i] = newPosition;
                fitnessValues[i] = newFitness;
            }
        }
    }
}

void scoutBeePhase(double* positions, double* fitnessValues, int colonySize) 
{
    for (int i = 0; i < colonySize; i++) 
	{
        if ((rand() % 100) / 100.0 < 0.05) 
		{ 	// 5% probability of scouting
            positions[i] = (rand() % 2000 - 1000) / 100.0; // Random values between -10 and 10
            fitnessValues[i] = calculateFitness(positions[i], 4.0);
        }
    }
}

int main() 
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "Muhammad Usman\n@Usman4Byte\n";
	cout << "ABC Algorithm Solving f(x) = (x+4)^2\n\n";
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    srand(static_cast<unsigned>(time(NULL)));
    const int colonySize = 10;
    const int iterations = 10;
    double positions[colonySize];
    double fitnessValues[colonySize];

    initializeBees(positions, fitnessValues, colonySize);

    for (int iter = 0; iter < iterations; iter++) 
	{
        employedBeePhase(positions, fitnessValues, colonySize);
        onlookerBeePhase(positions, fitnessValues, colonySize);
        scoutBeePhase(positions, fitnessValues, colonySize);

        int bestBeeIndex = 0;
        for (int i = 1; i < colonySize; i++) 
		{
            if (fitnessValues[i] > fitnessValues[bestBeeIndex]) 
			{
                bestBeeIndex = i;
            }
        }
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        cout << "Iteration " << iter + 1;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		cout << ": \nBest Solution = " << positions[bestBeeIndex]
             << ", Fitness = " << fitnessValues[bestBeeIndex] << endl;
        Sleep(500);
    }

    int bestBeeIndex = 0;
    for (int i = 1; i < colonySize; i++) 
	{
        if (fitnessValues[i] > fitnessValues[bestBeeIndex]) 
		{
            bestBeeIndex = i;
        }
    }
    Sleep(1000);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout << "\nBest Solution = " << positions[bestBeeIndex]
         << " with Fitness = " << fitnessValues[bestBeeIndex] << endl;
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    return 0;
}

