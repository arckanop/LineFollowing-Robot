#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // int Target = 35;
    float Error = 0;
    float lastError = 0;
    long long integral = 0;
    long long derivative = 0;
    double Kp = 0;
    double Ki = 0;
    double Kd = 0;
    double drive;

    int count = 2;

    while (true) {
        vector <int> sensor;
        sensor.resize(count);

        for (int i = 0; i < count; i++) {
            int x;
            cin >> x;
            sensor[i] = (int) x;
        }

        Error = sensor[0] - sensor[1];

        integral += Error;

        derivative = Error - lastError;

        drive = (Kp * Error) + (Ki * integral) + (Kd * derivative);

        printf("%.2f\n", drive);
    }

    return 0;
}