#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <mutex>
#include <limits>
using namespace std;

// ANSI color codes for text color
namespace Color {
    const char* Reset = "\033[0m";
    const char* Red = "\033[31m";
    const char* Green = "\033[32m";
    const char* Blue = "\033[34m";
}

class Task {
private:
    string name;
    chrono::time_point<chrono::system_clock> deadline;  //chrono STL is used for taking deadline in YYYY-MM-DD HH:MM:SS format
    int priority;
    
    
public:
    Task( string& n,chrono::time_point<chrono::system_clock>& d, int p ) : name(n), deadline(d), priority(p){} //constructor for class task

    string getname(){ //getter method for name 
        return name;
    }

    chrono::time_point<chrono::system_clock> getdeadline(){ //getter method for deadline
        return deadline;
    }

    int getPriority(){  //getter method for priority
        return priority;
    }

   
     
};

class TaskManager {
private:
    vector<Task> tasks;  //vector(dynamic array) for task storage
    mutex mtx;  //for threading 

public:
    void addTask(const Task& task) { //function for adding task in vector
        lock_guard<mutex> lock(mtx); //to prevent multiple threading 
        tasks.push_back(task);
    }

    void removeTask(int i) {  //function to remove task from the vector
        if (i >= 0 && i < tasks.size()) {
            lock_guard<mutex> lock(mtx);
            tasks.erase(tasks.begin()+i);
        }
    }

    void printTasks() {
        lock_guard<mutex> lock(mtx);
        cout << "Tasks:\n";
        for (int i = 0; i < tasks.size(); ++i) {
            cout << i << ": " << tasks[i].getname() << endl;
        }
    }

   void checkDeadlines() {     //function for checking deadlines 
    while (true) {
        this_thread::sleep_for(chrono::seconds(1));   // Check every second

        lock_guard<mutex> lock(mtx);
        auto now = chrono::system_clock::now();    //takes current time

        for (auto i = tasks.begin(); i != tasks.end();) {   //check for reminder in whole vector(list of tasks)
            auto timeLeft = chrono::duration_cast<chrono::seconds>(i->getdeadline() - now).count();    //calculating time left for deadline
            if (timeLeft == 24*60*60) {    // If 24 hours remaining for deadline
                
                switch(i->getPriority()) {
                    case 1:
                       
                        cout << "Reminder: Task with " <<Color::Blue<< "Low priority task"<<Color::Reset << " '" << i->getname() << "' is due tomorrow.\n";
                        break;
                    case 2:
                       
                        cout << "Reminder: Task with " <<Color::Green<< "Medium priority task" <<Color::Reset<< " '" << i->getname() << "' is due tomorrow.\n";
                        break;
                    case 3:
                        
                        cout << "Reminder: Task with " <<Color::Red<< "High priority task" <<Color::Reset<< " '" << i->getname() << "' is due tomorrow.\n";
                        break;
                    default:
                        cout<<"enter proper priority!!"<<endl;
                }
               i = tasks.erase(i); //remove task after showing reminder
              
            } 
             if (timeLeft <=60*60 && timeLeft>=60*53) { // If 1 hour remaining for deadline
               switch(i->getPriority()) {
                    case 1:
                       
                        cout << "Reminder: Task with " <<Color::Blue<< "Low priority task"<<Color::Reset << " '" << i->getname() << "' is due in 1 hour.\n";
                        break;
                    case 2:
                       
                        cout << "Reminder: Task with " <<Color::Green<< "Medium priority task" <<Color::Reset<< " '" << i->getname() << "' is due in 1 hour.\n";
                        break;
                    case 3:
                        
                        cout << "Reminder: Task with " <<Color::Red<< "High priority task" <<Color::Reset<< " '" << i->getname() << "' is due in 1 hour.\n";
                        break;
                    default:
                        cout<<"enter proper priority!!"<<endl;
                }
                i = tasks.erase(i); //remove task after showing reminder
               
            } 
             if (timeLeft < 60*55) { // If deadline has passed
                cout << "Deadline is within 1 hour : '" << i->getname() << "'.\n";
                i = tasks.erase(i); // Remove the task

            } else {
                ++i;
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
            cout << "Do you want to add or remove a task? (add/remove): "; 
            string choice;
            getline(cin, choice);

            if (choice == "add") {
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

                chrono::system_clock::time_point deadline = chrono::system_clock::from_time_t(mktime(&tm)); //convert deadline string to chrono date format 

                taskManager.addTask(Task(name, deadline, priority));  //insert task input taken from user 
            } else if (choice == "remove") {
                taskManager.printTasks();
                cout << "Enter the index of the task you want to mark as done and remove: ";
                int index;
                cin >> index; //if index is greater than the size of vector then the user will be asked again for add/remove task without removing any tasks
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore rest of the input buffer
                taskManager.removeTask(index);
            } else {
                cout << "Invalid choice. Please try again.\n";
            }
        }
    });

    deadlineThread.join();  //to make checkdeadline function and useInput function to work in parallel
    userInputThread.join();

    return 0;
}
