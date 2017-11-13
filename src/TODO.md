# To do

- Implement arc queries; e.g tree, forward, back, cross

- Implement BFS 

- Support node labeling with letters and improve the zero node implementation

- Import from csv adjacency matrix 

- Query vertices for density, order, degree, whether or not is source or sink

- Work out how to implement checking if it is source in less than O(n)

- Support undirected graphs

- Support a new Graph type; this would contain an array of vertices, but 
also associated metadata that will speed up calculations and mean that the 
graph object is more containerised and not a convenient alias

- For searching adjacency lists, if the graph is over a specific size/density,
it would be good to implement it as a binary search

- HOLY FUCK fix the build environment - namely, find a pretty simple way of
changing the ldconfig path. 

- Make sure that when you make no changes to the C library files make doesn't 
recompile the whole lot

- Fix the header dependency hell that has been created
