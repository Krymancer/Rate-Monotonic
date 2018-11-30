# Rate-Monotonic Algorithm

This is a simple implementation of the Rate-Monotonic Alhorithm in C++ to read a Random Set of Tasks and indetificate if the Set are Scalable or not

## Usage
> ./rm "path/to/task/set"
## Task Set File

The task set file shoud contains the Exectuion Time, Period and Deadline of each task
Example:
> 6.0 25.0 25.0  
> 10.0 50.0 50.0  
> 15.0 100.0 100.0  

The implementation works better when the Period and Deadline are equals.

# Compile

Just use the makefile

>make 

