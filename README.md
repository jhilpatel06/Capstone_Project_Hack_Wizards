
# Capstone Project : Hack_Wizards

**P11 : Reminder and Task Scheduler:-**  
Create a application that manages tasks and schedule using data structure to prioritise and track tasks based on deadline or importance levels it should also have reminder functionality as the deadline is approaching.


## Authors


- [Mitwa Ninama - 202301090](https://github.com/mitwaaaaaa)
- [Jhil Patel - 202301090](https://github.com/jhilpatel06)
- [Radhika Sangandhiya - 202301090](https://github.com/Radhikapatel-code)
- [Nandini Gadhvi - 202301090](https://github.com/NandiniGadhvi)





# Documentation

**Algorithm to manage a To do List with a reminder feature**

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
    - Initialize an object for TaskManager.
    - Ask user to Add or remove tasks : 
        a.if input='add', call AddTask function.
        b.if input='remove',call RemoveTask function.
    - Thread and join the CheckDeadline and UserInput function for them to run parallely.
6.End
