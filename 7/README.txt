HOMEWORK 7: SPATIALLY-EMBEDDED ADJACENCY MAPS

ORDER NOTATION ANALYSIS:


n: The total number of users
l: The total number of users with a location
d: The total number of users with degree >= 1
m: The total number of connections
p: The number of users that a function will print out

a: The number of friends this particular user has

loadConnections():
O(m*log(d)) OR O(m*log(d)*log(X)) where X=m or n, depending on vector/set implementation
loadLocations():
O(l*log(l))
printAllUsersWithinDistance():
O(l)
printDegreesHistogram():
O(d)
printDegreesOfAll():
O(d)
printFriendsWithDegree():
O(log(d) * m) OR O(log(d) * n)
printFriendsWithinDistance():
O(log(n) + m*log(l)) OR O(log(n) + n*log(l))
printUsersWithinIDRange():
O(n)
