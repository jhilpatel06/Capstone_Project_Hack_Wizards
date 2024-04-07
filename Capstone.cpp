#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <mutex>

using namespace std;

class Task {
private:
    string name;
    chrono::time_point<chrono::system_clock> deadline;
    int priority; // Priority: 1 (lowest) - 3 (highest)
public:
    Task(const string& n, const chrono::time_point<chrono::system_clock>& d, int p) : name(n), deadline(d), priority(p) {}

    string getName() const {
        return name;
    }

    chrono::time_point<chrono::system_clock> getDeadline() const {
        return deadline;
    }

    int getPriority() const {
        return priority;
    }
};

class TaskManager {
private:
    vector<Task> tasks;
    mutex mtx;

public:
    void addTask(const Task& task) {
        lock_guard<mutex> lock(mtx);
        tasks.push_back(task);
    }

   void checkDeadlines() {
    while (true) {
        this_thread::sleep_for(chrono::seconds(1)); // Check every second

        lock_guard<mutex> lock(mtx);
        auto now = chrono::system_clock::now();
        for (auto it = tasks.begin(); it != tasks.end();) {
            auto timeLeft = chrono::duration_cast<chrono::seconds>(it->getDeadline() - now).count();
            if (timeLeft == 24*60*60) { // If 24 hours remaining
                string priorityReminder;
                switch(it->getPriority()) {
                    case 1:
                        priorityReminder = "Low priority task";
                        break;
                    case 2:
                        priorityReminder = "Medium priority task";
                        break;
                    case 3:
                        priorityReminder = "High priority task";
                        break;
                    default:
                        priorityReminder = "Task";
                }
                cout << "Reminder: Task is " << priorityReminder << " '" << it->getName() << "' is due tomorrow.\n";
            } else if (timeLeft == 60*60) { // If 1 hour remaining
                string priorityReminder;
                switch(it->getPriority()) {
                    case 1:
                        priorityReminder = "Low priority task";
                        break;
                    case 2:
                        priorityReminder = "Medium priority task";
                        break;
                    case 3:
                        priorityReminder = "High priority task";
                        break;
                    default:
                        priorityReminder = "Task";
                }
                cout << "Reminder: Task is " << priorityReminder << " '" << it->getName() << "' is due in 1 hour.\n";
               
            } else if (timeLeft <= 60*60) { // If deadline has passed
                cout << "Deadline is within 1 hour : '" << it->getName() << "'.\n";
                it = tasks.erase(it); // Remove the task
            } else {
                ++it;
            }
            break;
        }
    }
}

};

int main() {
    TaskManager taskManager;

    // Thread for checking deadlines
    thread deadlineThread(&TaskManager::checkDeadlines, &taskManager);

    // Thread for taking user input
    thread userInputThread([&]() {  // capture by value
        while (true) {
            string name;
            string deadlineString;
            int priority;
            cout << "Enter task name: ";
            getline(cin, name);

            cout << "Enter task deadline in format 'YYYY-MM-DD HH:MM:SS': ";
            getline(cin, deadlineString);

            cout << "Enter task priority (1-3): ";
            cin >> priority;
            cin.ignore(); // Ignore newline character

            tm tm = {};
            istringstream ss(deadlineString);
            ss >> get_time(&tm, "%Y-%m-%d %T");

            if (ss.fail() || priority < 1 || priority > 3) {
                cout << "Invalid input. Please try again.\n";
                continue;
            }

            chrono::system_clock::time_point deadline = chrono::system_clock::from_time_t(mktime(&tm));

            taskManager.addTask(Task(name, deadline, priority));
        }
    });

    deadlineThread.join();
    userInputThread.join();

    return 0;
}
