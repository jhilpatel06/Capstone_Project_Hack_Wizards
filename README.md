
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

- Remainder statement "Task <taskname> is due in 1 hour." before an hour to the deadline if task is enqueued in in less then a day from deadline.

###

1. Create a class named Task with attributes name, deadline and priority.
