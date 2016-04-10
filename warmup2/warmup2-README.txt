Documentation for Warmup Assignment 2
=====================================

+-------+
| BUILD |
+-------+

Comments: Use "make" command to create the executable

+---------+
| GRADING |
+---------+

(A) Basic running of the code : +100 points (+10 points for each run)

Missing required section(s) in README file: None
Cannot compile : None
Compiler warnings : None
"make clean" : use "make clean" to Clean all .o files and executable
Segmentation faults : None
Separate compilation : None
Using busy-wait : None. Code checked on nunki using "top" command. warmup2 uses less than 1% of CPU.
Handling of commandline arguments:
    1) -n : Handled as per Specification
    2) -lambda : Handled as per Specification
    3) -mu : Handled as per Specification
    4) -r : Handled as per Specification
    5) -B : Handled as per Specification
    6) -P : Handled as per Specification

Trace output :
    1) regular packets: 7 Line output for the regular packets as per Specification
    2) dropped packets: 1 Line output for the dropped packets as per Specification
    3) removed packets: 1 Line output for the removed packets as per Specfication
    4) token arrival (dropped or not dropped): 1 Line output for the dropped tokens as per Specification

Statistics output :
    1) inter-arrival time : As per Specification
    2) service time : As per Specification (in seconds)
    3) number of customers in Q1 : As per Specification
    4) number of customers in Q2 : As per Specification
    5) number of customers at a server : As per Specification
    6) time in system : As per Specification (in seconds)
    7) standard deviation for time in system : As per Specification (in seconds)
    8) drop probability : As per Specification

Output bad format :  None, Handled as per Specification (-0)
Output wrong precision for statistics (should be 6-8 significant digits) : None, Handled as per Specification (-0)
Large service time test : As per Specification (-0)
Large inter-arrival time test : As per Specification (-0)
Tiny inter-arrival time test : As per Specification (-0)
Tiny service time test : As per Specification (-0)
Large total number of customers test : As per Specification (-0)
Large total number of customers with high arrival rate test : As per Specification (-0)
Dropped tokens test : As per Specification (-0)
Cannot handle <Cntrl+C> at all (ignored or no statistics) : <Cntrl+C> Handled as per Specification (-0)
Can handle <Cntrl+C> but statistics way off : <Cntrl+C> Handled as per Specification (-0)
Not using condition variables and do some kind of busy-wait : No
Synchronization check : Yes. All threads are Synchronized to perform the operation as per Specification.
Deadlocks : No

+------+
| BUGS |
+------+

Comments: No bugs

+-------+
| OTHER |
+-------+

None
