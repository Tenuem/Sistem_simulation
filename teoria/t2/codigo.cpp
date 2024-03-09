#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>
// Function to generate a random sample from a triangular distribution
double getFromDistribution(double a, double b, double c) { 
    double u = (double)rand() / RAND_MAX; // Uniform random variable
    bool leftRange = false;
    if (u <= (c - a) / (b - a)) leftRange = true; // a <= x <= c
    double x = u;
    double result;
    if (leftRange){
        result = a + sqrt(x * (b - a) * (c - a));
    }
    else {
        result = b - sqrt((1 - x) * (b - a) * (b - c));
    }
    return result;
}


int main(int argc, char* argv[]) {

    int numSimulations = atoi(argv[1]);
    srand(time(NULL));

    // Monte Carlo simulation
    double sales, patentImpact, totalSales;
    bool patentAccepted;

    double totalProfit = 0.0;
    int overProfit = 0; // counter for worth keeping company simulations

    for (int i=0; i<numSimulations; i++){
        sales = getFromDistribution(1.0, 9.0, 3.0);
        patentImpact = getFromDistribution(0.25, 0.75, 0.50);
        patentAccepted = (getFromDistribution(0.0, 100.0, 50.0)) < 50.0 ? false : true;

        totalSales = sales * (1.0 + (patentAccepted ? patentImpact : 0.0)); // decide if multiply with bonus according to having patent or not

        double profit = totalSales - 6.0;

        // Accumulate results
        totalProfit += profit;

        // Check if profit is over 6 million euros
        if (profit > 0) {
            overProfit++;
        }
    }
    double averageProfit = totalProfit / numSimulations;
    double percent = (double)overProfit / numSimulations;

    printf("Average Profit: %.2f million euros\nAverage difference between keeping and selling the company: %f\n", averageProfit+6, averageProfit);
    printf("Probability of cases when it is worth to keep the company: %.2f%%\n", percent * 100);

    return 0;
}
