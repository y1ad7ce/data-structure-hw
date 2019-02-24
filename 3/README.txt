HOMEWORK 3: RESIZABLE TABLE

References:

https://stackoverflow.com/questions/8992853/terminating-function-template-recursion
https://stackoverflow.com/questions/14109358/correct-usage-of-exit-in-c
http://www.cplusplus.com/reference/cstdlib/exit/
https://www.geeksforgeeks.org/endl-vs-n-in-cpp/
https://stackoverflow.com/questions/37409596/how-to-check-the-type-of-variable-in-conditional-statement
https://en.cppreference.com/w/cpp/types/is_same
https://stackoverflow.com/questions/13071340/how-to-check-if-two-types-are-same-at-compiletimebonus-points-if-it-works-with
https://stackoverflow.com/questions/44284362/accessing-2d-array-elements-using-pointer-arithmetic-in-c
https://www.tutorialspoint.com/cprogramming/c_pointer_arithmetic.htm
 >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


n = the number of rows and m = the number of columns.  You should assume that calling new [] or delete [] on an array will take time proportional to the number of elements in the array.

get
O(1)

set
O(1)

numRows
O(1)

numColumns
O(1)

push_back_row
O(mn)

push_back_column
O(mn)

pop_back_row
O(mn)

pop_back_column
O(mn)

print
O(mn)

copyTableData
O(mn)

TESTING & DEBUGGING STRATEGY: 

I only used Dr. Memory for debugging. 

For corner cases, I considered remove till empty and push back to empty table.
Because those case are involved with memory re-allocations and member variables re-initializations.


EXTRA CREDIT: 
Indicate here if you implemented push_back for multiple rows or
multiple columns and/or rewrote your code using pointers instead of
subscripts for extra credit.  Also document the order notation for
your multi-row and multi-column push_back functions.

I did the functions with pointers.

v represents the table passed into the function
n(v) -> v's number of rows
m(v) -> v's number of columns

push_back_rows: 
n+v + nm + n(v)*m + nm
O(nm) or O(n(v)*m) whichever is greater

push_back_columns:
nm(v) + nm + nm
O(nm) or O(n*m(v)) whichever is greater