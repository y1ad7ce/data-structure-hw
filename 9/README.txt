HOMEWORK 9: IMDB SEARCH

resources:
http://www.cplusplus.com/reference/string/string/getline/
http://www.cplusplus.com/reference/map/map/find/
https://medium.com/@aozturk/simple-hash-map-hash-table-implementation-in-c-931965904250
https://gist.github.com/aozturk/2368896#file-hashmap-h
http://www.algolist.net/Data_structures/Hash_table/Dynamic_resizing
https://www.geeksforgeeks.org/implementing-hash-table-open-addressing-linear-probing-cpp/
http://www.partow.net/programming/hashfunctions/
https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
https://stackoverflow.com/questions/8620030/generate-all-combination-of-elements-in-2d-vector


HASH FUNCTION DESCRIPTION
http://www.partow.net/about/details.html


HASH TABLE IMPLEMENTATION
I created a HashNode class and a HashMap class. HashNode works basically like pairs. I store the 64 queries for each movie as "keys" in those HashNode. Values in the HashNodes are then the pointers to movie objects. As you may be assuming, I do have a movie class. 

The program stores movie objects' pointers in a vector when it is reading the movie file. That vector is then used for inserting in my hash table. A vector of movie objects pointers has the benefit of both being the values in HashNode and the thing I need to generate 64 queries from. 