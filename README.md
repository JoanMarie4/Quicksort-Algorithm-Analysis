# Quicksort-Algorithm-Analysis
Analysis of four different types of Quicksort strategies: Hoares and Lomutos with random and first element partitions

Project compiled by typing make

makeInput executable:
* takes an integer parameter which will indicate how much numbers the input file will have
* creates three txt files with the number of numbers indicated by the integer parameter
* each file will contain sequences of numbers that the quicksort strategies will be analyzing, one will have the
  numbers already sorted, the other will have the reverse sorted, and the last will have them randomized

quicksort executable:
* takes two parameters, first paramater is an input file created with makeInput
* second parameter is the name of the file the output will be outputted to
* executable runs the four different quicksotyr strategies and outputs the time it took to sort the numbers and
  the number of swaps it took

Input file contains all the input txt files used in the analysis
