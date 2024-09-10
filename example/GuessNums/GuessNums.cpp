#include "SIMPLE-LOG.hpp"
#include <limits>
#include <sstream>
using namespace std;

bool should_exit = false;

int main() {
    srand(time(NULL));
    Log LOG("gamelog.log");

    LOG.set_ERROR_Callback([](const string& msg) {
        cerr << "ERROR: " << msg << endl;
        should_exit = true;
    });

    LOG.Write(LogLevel::INFO, "Game Start Successful\n");

    int num = rand() % 100 + 1;
    string buffer_str;
    int current_num = 0;

    while (!should_exit) {
        buffer_str.clear();
        current_num = 0;

        // Read input as a string
        cin >> buffer_str;

        // Convert string to integer
        stringstream ss(buffer_str);
        if (!(ss >> current_num) || !ss.eof()) {
            LOG.Write(LogLevel::ERROR, "Invalid number format\n");
        } else if (current_num > 2147483647 || current_num < 0) {
            LOG.Write(LogLevel::ERROR, "Current_num is out of range\n");
        } else {
            string msg_str = "Player Guess:" + to_string(current_num) + "\n";
            LOG.Write(LogLevel::INFO, msg_str);

            if (current_num != num) {
                if (current_num > num) {
                    cout << "too big!" << endl;
                } else {
                    cout << "too small!" << endl;
                }
            } else {
                cout << "You guessed it!" << endl;
                break;
            }
        }
    }

    LOG.Write(LogLevel::INFO, "Game Exit Successful\n");
    return 0;
}
