
# Capstone Project : Hack_Wizards

**P11 : Reminder and Task Scheduler:-**  
Create a application that manages tasks and schedule using data structure to prioritise and track tasks based on deadline or importance levels it should also have reminder functionality as the deadline is approaching.


## Authors


- [Mitwa Ninama - 202301162](https://github.com/mitwaaaaaa)
- [Jhil Patel - 202301090](https://github.com/jhilpatel06)
- [Radhika Sangandhiya - 202301184](https://github.com/Radhikapatel-code)
- [Nandini Gadhvi - 202301193](https://github.com/NandiniGadhvi)





# Documentation
***Features we aim to provide :***
###

    1. Add task
    2. Remove task
    3. Display list of tasks when asked for removal
    4. Reminder 'before a day or an hour' depending on the diffence of time of enqueuing and deadline.
    5. Reminder note displayed in 'distinct colors' according to different priority values.

###
**Algorithm to manage a To do List with a reminder feature**
###

***Input***:

- Task name  
- Task deadline  (MM-DD-YYYY HH:MM:SS)  
- Task Priority  (1-3 with highest 1 and lowest 3)

***Output***

- Reminder statement "Task <taskname> is due tommorow." a day   before the deadline if task is enqueued atleast a day before the deadline.  

- Remainder statement "Task <taskname> is due in 1 hour." before an hour to the deadline if task is enqueued in less then a day from deadline.

###
```
1. Create a class named 'Task' with attributes :
    - TaskName, 
    - TaskDeadline
    - TaskPriority
2. Create another class named 'TaskManager' with attributes :
    - vector 'tasks' 
    - mutex 'mtx'
3. Methods of TaskManager:
    a. AddTask : Add task in vector as per description provided by the user.
    b. PrintTask : Displays list of tasks along with their indices.
    c. RemoveTask : Removes task at index entered by the user.
    d. CheckDeadline : Checks deadlines periodically and displays remainder statement.
        - Sleeps for 1 second and compares current time with deadline periodically.
        - If current time is a day less than the deadline then it displays note "Task <taskname> is due tommorow." and dequeues the task.
        - If current time is an hour less than the deadline then it displays note "Task <taskname> is due in 1 hour." and dequeues the task.
        *(This is specially for those tasks that were enqueued at time less than 24 hours to deadline.)
        -Else if the task is enqueued in less than an hour to the deadline it will immidiately display "Task due within an hour".
4. Class Color with attributes :
    - Reset
    - Red
    - Blue
    - Green
    (Used in CheckDeadline function to display reminder statement in 'Red' color for tasks with priority 1, 'Blue' for 2 and 'Green' for 3.)
5. In main function :
    - Create an object for TaskManager.
    - Ask user to Add or remove tasks : 
        a.if input='add', call AddTask function.
        b.if input='remove',call RemoveTask function.
    - Thread and join the CheckDeadline and UserInput function for them to run parallely.
6.End
```

###

***Choice of data structure :- <VECTOR>***

###

- Vector is a ***'dynamic array'*** and hence is advantageous over both simple array and linked list.
- **Space complexity** = **'O(n)'** where n the number of tasks present in the 'To do list'
- **Time complexity** :  In reference to our code.
    - Searching or Accessing element (tasks) by index = **O(1)**
    - Add task = **O(1)** since new task is by default appended to the end.
    - Remove task = **O(1)** since we are deleting task by index.
    - Comparing time for Reminder = **O(n)**
- **Advantages over priority queue** :
    - Space complexity : 
        - Unlike priority queue implemented using linked list in vector we don't have to waste extra memory for next node while still having the dynamic property of linked list.
    - Time complexity :
        - Time complexity of priority queue for enqueuing is **O(n)** and dequeueing is **O(1)** which is reverse in case of vector.
        - However since adding tasks may be more frequent than removing tasks in our case on request or after reminder, vector stands as a better option.

###
***Few other justifications for use of STLs***
###

    1. <vector> : For using vector data structure.
    2. <chrono> : For storing and comparing time.
    3. <sstream> : To convert a string representing a deadline into a chrono time format.
    4. <iomanip> : To ignore extra space or padding while entering deadline
    4. <thread> : To enable concurrent execution of tasks, allowing for simultaneous checking of deadlines and handling user input.
    5. <mutex> :  Ensures of only one thread accessing the list at a time preventing simultaneous modifications and potential conflicts between threads.
- Besides, we have used infinite while loops to enable users to enter tasks for as many times they desire while simontaneously checking over deadlines for reminders.

###



## Contributing

| Names   | Contribution areas                       |Percentage|
|---------|------------------------------------------|:--------:|
| Radhika | Reminder Function and UserInput Function |25        |
| Nandini | Reminder Function and UserInput Function |25        |
| Jhil    | Classes and Readme                       |25        |
| Mitwa   | Classes and Readme                       |25        |


## Running test case

- [Running Test Case screenshot](https://docs.google.com/document/d/1wK7gexoB1Cjia5XnYXwZDY4xTUlnWphOzp8InErIwjI/edit?usp=sharing)




