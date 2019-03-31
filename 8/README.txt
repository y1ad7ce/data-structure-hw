HOMEWORK 8: ROPES


BALANCED/WORST CASE RUNNIG TIME ANALYSIS:
n = characters in the string of the current Rope (*this)
m = characters in the string of the Rope passed in (for functions that take
    a second rope)
v = longest "value" of a leaf
p = longest path from root to a leaf
Using these variables, state and explain the big-O running time of each 
of the following operations two ways: 1) with a balanced Rope, 2) with an 
extremely unbalanced Rope. Explain what you considered an extremely 
unbalanced rope for the string "Hello my name is Simon".

extremely unbalanced:

				_
			       /
			      _
			     / \
			    _   _Simon
			   / \
			  _   s
			 / \
			_   me_i
		       / \
		      _   na
		     / \
		    _   my_
		   / 
		  Hello_



Copy Constructor:
3 member variable assignments for each node, and it has to go through all the nodes in tree.
1. O(3 * p * log (n))
2. O(3 * p * log(p) * log(n))

Construct from Node*:
it uses weightTotal function to get size of the Rope, and weightTotal traverse through the entire tree with one visit for each node. 
1. O(p * log (n))
2. O(p * log(p) * log(n))

Index:
1. O(p)
2. O(p)

Report:
substr() is linear complexity
1. O(p * log(n) * log(n))
2. O(p * log(p) * log(n) * log(n))

iterator operator++:
1. O(1)
2. O(1)

Split:
1. O(p * log(n)) or O(1) for single node Rope
2. O(p * log(p) * log(n)) or O(1) for single node Rope

Concat:
Use a copy function(3a) and combine(constant time)
1. O(3 * p * log (m))
2. O(3 * p * log(p) * log(m))


TESTING & DEBUGGING STRATEGY: 
Briefly describe the tests in your StudentTests() function.
How did you test the "corner cases" of your implementation?

I think the BasicTest is good enough for all the operations except split. Therefore in my custom tests, i only test split operation.

I tested some examples included in hw8_split_solutions.pdf that are not included in BasicTest. 

My tree's leaves start with a right only child. I had that to debugg for my operator++ and begin(). It tests spliting at the end of a string in a leaf node. BasicTest has splitting at the beginning version so i didn't test that. It tests splitting at the very beginning and very end of the rope. It also tests splitting at a single character string leaf node for debugging indexing in my code. Finally, i considered a coner case which the tree has only one node. I also debugged split for that case. 