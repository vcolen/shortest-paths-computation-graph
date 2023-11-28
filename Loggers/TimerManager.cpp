#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;

auto startTimer() {
    return high_resolution_clock::now();
}

auto endTimer(const time_point<high_resolution_clock>& start) {
    return duration_cast<milliseconds>(high_resolution_clock::now() - start).count();
}

int main() {
    // Record the start time
    auto startTime = startTimer();

    // Your code goes here

    // Record the end time and calculate the duration in milliseconds
    auto duration = endTimer(startTime);

    // Calculate hours, minutes, seconds, and milliseconds
    auto hours = duration / 3600000;
    auto minutes = (duration % 3600000) / 60000;
    auto seconds = (duration % 60000) / 1000;
    auto milliseconds = duration % 1000;

    // Print the total runtime
    cout << "Total runtime: " << hours << " hours, " << minutes << " minutes, "
         << seconds << " seconds, " << milliseconds << " ms; Total milliseconds: " << duration << endl;

    return 0;
}
