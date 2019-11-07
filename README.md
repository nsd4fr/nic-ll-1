# Nic Linked List

This is an idea for a Linked List optimization I had and decided to implement in C++. 


# The Big Idea
One of the biggest downsides of the linked list structure is that searching or accessing an indexed member of the linked list is a linear time operation. Some ways of overcoming this are the LRU Cached Linked List, which stores items in order of most recent access in a hash table as well, which is very time efficient, but memory slow. One can also move most recently accessed items to the front of the linked list, which improves search times for elements that are requested or queried often. 

My optimization is to create an iterator that is stored by the linked list that knows its own position and resides on the last indexed item. Thusly, if a certain index is queried repeatedly, then the fetch time for that element becomes O(1). The search time for nearby elements also decreases dramatically. 

However, the overall runtime classification for non-repeated indexed access is still O(n). 

Use cases where this optimization is useful is obviously when one needs a linked list backbone, but the primary method of access is indexing into the list. Then, it is more useful when indexes tend to be close together. 


# Example 

One example where this would be useful is iteratively accessing the entire list. 

```
//Say we have a linked list "list1" with "n" elements
for (int i = 0; i < list1.size(); i++){
    int element = list1[i];
    //Do something with element
}
```

In the standard linked list implementation, the above algorithm would be O(n^2). With my optimization, the algorithm is only O(n).

# Installation
I believe the only requirement on compilation is that due to the use of `nullptr`, the C++ STD11 standard must be used. To use, include the LinkedList header and get going!

# TODO
- Abstract the use of null
- Finish the full implementation and flesh out testing


# Credits
The base implementation of Linked List is heavily drawn from the UVA PDR repository, with my own additions to create the optimization. Their code is released under the [CC BY-SA 4.0](https://creativecommons.org/licenses/by-sa/4.0/) license. 

# License
I release this code under the [Creative Commons Attribution-ShareAlike 4.0 International License](https://creativecommons.org/licenses/by-sa/4.0/)