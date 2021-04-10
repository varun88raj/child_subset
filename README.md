In this project, you will solve a number of subset sum problems, with each child solving one instance of the problem. A simple definition of the subset sum problem is: Given a set of integers and a value sum, determine if there is a subset of the given set with sum equal to the given sum. Your project should consist of one program, which will fork off versions of itself to do some file processing. To do this, it will start by taking some command line arguments. Your executable should be called log Parse. You must implement at least the following command line arguments using getopt:-h-i inputfilename-o outputfilename-t time The option –h should display all legal command line options and how it is expected to run, as well as the default behavior. If input and output filenames are not specified, the defaults should be input.dat and output.dat. time specifies the maximum duration the code should run (default 10 seconds).Once you have parsed the command line arguments and validated them, then you should attempt to open the input file. It will start with a number on a line by itself, with that number indicating the amount of subtasks your program will have to solve using copies of your process created with fork. Every other line of the file will contain a subtask, which will consist of a list of integers. 
An example of this input file is below:

3

9 3 34 4 12 5 2

6 3 2 7 1

256 3 5 7 8 9

Your data file has the number of problems to be solved on the first line (3 in the example), and one instance of the problem on each subsequent line. The original process should read the first line of the file. Once it has read that line, it should then go into a loop based on that number, with each iteration of the loop forking off a copy that will then process the next line. Once that child has finished its work (defined below), it will write some data to the output file and then terminate. At that point, the parent detects that its child has terminated, and it should initiate another iteration of the loop until all instances have been solved. After all children have terminated. the parent should write the pids of all of its children that it launched, as well as its own pid to the output file. When a child process starts, it should read the next line of the file. We see in our example file that the first forked child would read the line with 7 numbers. The task the child must complete with these numbers is the subset sum problem. In particular, your process must find if any subset of numbers in that list sum to the first number. If it does, it should output the set of numbers that sums to that value to the output file, starting with its pid. 13278: 4 + 5 = 9 .Note that the set of numbers might not contain a set of numbers that sums to the specified number (example 3aboev). If the numbers are small, this might be quickly discovered. In that case, output as follows:13278: No subset of numbers summed to 256.However, given a sufficiently large list, this might take too long for our needs. I want your individual child processestogive upafter 1 second of clock time. In addition to the above time limit, your overall project should have a maximum duration oftseconds (default 10seconds).
Explanation videos with link

Main function expalnantion: 
https://drive.google.com/file/d/1bClGyjuasSmzL0SO31CAiVtIYYXp_vrl/view?usp=sharing

Other functions explanation:
https://drive.google.com/file/d/1-g4q4PYNZGlbFqavWbDguHnmIatBaxFp/view?usp=sharing
