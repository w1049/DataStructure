#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>

#include "LinkedQueue.h"
using namespace std;

int totalTime;

// Arrival time
LinkedQueue<int> carQue, truckQue;

// Arrive interval in [Low, High]
int carLow, carHigh;
int truckLow, truckHigh;

// Waiting time
int carWait, truckWait;

// Counter
int carNum, truckNum;

// not shipped
int carRemain, truckRemain;

void generate_queue() {
    srand(time(0));
    int currentTime = 0, maxNum = carLow ? totalTime / carLow : totalTime;
    for (int i = 1; i <= maxNum; i++) {
        currentTime += carLow + (carHigh - carLow + 1) * rand() / (RAND_MAX + 1);
        if (currentTime <= totalTime) carQue.enQueue(currentTime);
        else break;
    }
    
    currentTime = 0, maxNum = truckLow ? totalTime / truckLow : totalTime;
    for (int i = 1; i <= maxNum; i++) {
        currentTime += truckLow + (truckHigh - truckLow + 1) * rand() / (RAND_MAX + 1);
        if (currentTime <= totalTime) truckQue.enQueue(currentTime);
        else break;
    }
}

void calculate_waiting_time() {
    // every 10 min
    for (int currentTime = 10; currentTime <= totalTime; currentTime += 10) {
        int onBoard;
        for (onBoard = 0; onBoard < 8; onBoard++) {
            if (carQue.isEmpty() || carQue.getHead() > currentTime) break;
            carWait += currentTime - carQue.deQueue();
            ++carNum;
        }
        for (; onBoard < 10; onBoard++) {
            if (truckQue.isEmpty() || truckQue.getHead() > currentTime) break;
            truckWait += currentTime - truckQue.deQueue();
            ++truckNum;
        }
        // if not full
        for (; onBoard < 10; onBoard++) {
            if (carQue.isEmpty() || carQue.getHead() > currentTime) break;
            carWait += currentTime - carQue.deQueue();
            ++carNum;
        }
    }
}

int main() {
    cout << "Please enter the total simulation time (in minutes, e.g. 100):" << endl;
    cin >> totalTime;
    cout << "Please enter lower and upper bound for car arrival interval (in minutes, e.g. 0 3):" << endl;
    cin >> carLow >> carHigh;
    cout << "Please enter lower and upper bound for truck arrival interval (in minutes, e.g. 1 6):" << endl;
    cin >> truckLow >> truckHigh;
    generate_queue();
    calculate_waiting_time();
    while (!carQue.isEmpty())carQue.deQueue(), ++carRemain;
    while (!truckQue.isEmpty())truckQue.deQueue(), ++truckRemain;
    cout << "Statistics: " << endl;
    cout << " \t\tCar\tTruck" << endl;
    cout << "Number:\t\t" << carNum << '\t' << truckNum << endl;
    cout << "Mean waiting:\t" << setprecision(3) << 1.0 * carWait / carNum << '\t'
                              << setprecision(3) << 1.0 * truckWait / truckNum << endl;
    cout << "Remaining:\t" << carRemain << '\t' << truckRemain << endl;
}