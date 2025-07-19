#include <iostream>
#include <fstream>
#include <cmath>

#define PI 3.14159265358979323846

using namespace std;

int main() {
    // Create and open a CSV file
    ofstream file("data.csv");
    if (!file) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    // Write header
    file << "t,x,y,z\n";

    // Generate values for t from 0 to 5 in steps of 0.001
    for (double t = 0; t <= 5; t += 0.001) {
        double x = 0.25 * t + 3;
        double y = sin(2 * PI * 50 * t);
        double z = 2 * pow(t, 3) + pow(t, 2) + 5 * t + 4;

        file << t << "," << x << "," << y << "," << z << "\n";
    }

    file.close();
    cout << "Data saved to data.csv\n";

    // Call Python script to plot the data
    system("python3 plot_graph.py");

    return 0;
}
