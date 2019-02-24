HOMEWORK 5: UNROLLED LINKED LISTS

References:

http://www.cplusplus.com/reference/vector/vector/insert/
http://www.cplusplus.com/reference/list/list/erase/


Number of nodes: n
Number of elements in a node: m

size()
O(nm)

nodeNum()
O(1)

empty()
O(1)

print()
O()

front()
O(1)

back()
O(1)

push_front()
O(m)

pop_front()
O(m)

push_back()
O(m)

pop_back()
O(1)

erase()
O(m)

insert()
O(m)

begin()
O(1)

end()
O(1)

copy_list()
O(nm)

destroy_list()
O(n)

dslist is more similar to STL list. Unrolled linked list, in most cases, takes more memory to store the same amount of information because Node will always allocate a full size array in each node, sometimes information in the arrays aren't useful.

Unrolled linked list would benefit in tasks like indexing since each node stores the number of elements. It can help the program to jump through the list to a certain location quicker. 

Iterator works differently in Unrolled linked list too. It's not pointing to any element directly. Instead, it is pointing to a node with an "offset". iterator will need to get through node to the array to access values.

Push and pop functions are doing different things too. Different "Nodes" are being created and deleted. Unrolled linked list would use extra memory to keep the empty(useless) elements. While dslist or STL list don't have to worry about this

Example of worst case: 
Erasing elements[0] in each nodes: moving all the elements one step forwards

Inserting an element at the first location of a full array: move all the elements to a new node

EXTRA CREDIT:
For the worst case of insert, instead of moving all the existing element to the next node just created, I put the inserting value in a new node and link it to the prev_ of the node iterator is pointing at.