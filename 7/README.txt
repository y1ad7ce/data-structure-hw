HOMEWORK 7: SPATIALLY-EMBEDDED ADJACENCY MAPS

ORDER NOTATION ANALYSIS:


n: The total number of users
l: The total number of users with a location
d: The total number of users with degree >= 1
m: The total number of connections
p: The number of users that a function will print out

a: The number of friends this particular user has

loadConnections():
O(m)
loadLocations():
O(l)
printAllUsersWithinDistance():
O(l)
printDegreesHistogram():
O(d)
printDegreesOfAll():
O(l)
printFriendsWithDegree():
O(a)
printFriendsWithinDistance():
O(a)
printUsersWithinIDRange():
O(p)