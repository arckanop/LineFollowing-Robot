#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int error = 0;
    int lastError = 0;
    long long integral = 0;
    long long derivative = 0;
    double Kp = 0;
    double Ki = 0;
    double Kd = 0;
    double drive;

    // vector <int> sensor;
    int sensor[2];

    // <--- End of Setup --->

    error = sensor[0] - sensor[1];

    integral += error;
    derivative = error - lastError;

    return 0;
}