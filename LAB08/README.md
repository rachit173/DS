Name : Rachit Tibrewal
Functions Used
make_set : Creates a new set with the key being a counter which was initially set to 0.	
		For future access(like find_set ,union_set) the key must be used rather than the 			satellite data.The satellite data can be easily be used as reference by creating
		a dictionary based on hashing or binary tree.
find_set : The function finds the main root of the tree to which the query set belongs.
		The recursive function also sets the parent of all members in the path from the query 			element to the root as the root, thus shortening the height of the tree.
uni(union_set) :The function takes two arguments and find the root of the tree to which both 				the arguments belong.
		If the roots are diffferent then the trees are different. The root with the higher 			rank is taken as the new root and the other root is linked to it as a child.
Using The Driver Programme:
	Queries:
	0 is the make set query which takes the satellite data as input value.
	1 is the find parent query which takes the key as the input.
	2 or anything else : This will result in union of the two keys taken as input.  
