<br>- create structure, list, main:
<br>- I created a structure that contains the link to the previous node, to the node
next and two data fields, one with the timestamp, and the other with
the value.
-initializing the list, instead, I did it by hand, allocating the first node,
then linking the two links to NULL
-then I created a function to add values to the list, which has been transmitted
as parameters the list (list head) and the values for timestamp and value,
like this: I took an auxiliary node, in which I put the values to be added and I have it
linked to NULL with the next link, then I checked if the list is empty, and if so
e, then that node becomes the first; if it is not empty, then the list is traversed
until the end (with another auxiliary node) and, thus, the first auxiliary node, the
to be added, becomes the last.
-follows a function to delete a node with a certain timestamp, this one
help to solve from 2.1 the function scrolls to the end of the list and if
in this journey it meets a node that has a value in the timestamp field
transmitted as a parameter, then, with the help of an auxiliary node, the respective node
is released
-follows a function to release an entire list. I took an auxiliary node q
to mitigate the sudden release of memory of the first node in list s, the first
progressively becoming the next until reaching a single node in the list.
<br>- the display function goes through the list from beginning to end and displays along the way
the values in the related node
<br>- for all resolved points, it is assumed that the list has already been initialized and
that it has values in it.

for 2.1: I take a node starting from the actual first node of the list
(s->next, because s has a random value so that it is the head of the list) and se
stop at the fifth node from the end, because q helps to take sublists of
five elements each, because the node in the middle is taken from the calculation
sigma values. I calculate xaverage according to the formula; it remains unchanged
regardless of the five-item sublist
<br>- according to the formula, I also calculate sigma, subtracting from each element on xmediu
and then I do the average and remove the radical
<br>- where it happens that the condition in the requirement is not fulfilled, I mark somehow
delete node; since the timestamp is always positive, I thought of making it -1
-then, I take each sublist and delete the significant nodes

at 2.2.1: I try to delete the initial list, to put the new values in it, the new ones
values being the median, as required
<br>- in the same way I take sublists of five elements, this time even creating a sublist
<br>- I sort the newly created sublist with the bubble method
<br>- the median value resulting from ordering is placed in the big list
<br>- clear everything I allocated
at 2.2.2:
<br>- this function follows the principle of twoone (doca 2.2.1), only not anymore
arranges the elements, makes their arithmetic average and inserts it into the big list
<br>- I try to delete the initial list, to put the new values in it, the new values being
the median ones, according to the requirement
<br>- in the same way I take sublists of five elements, this time even creating a sublist
<br>- the value resulting from ordering is placed in the big list
<br>- the timestamp remains the same, but I put it in a variable toadd1, so that it is mine
somewhat easier with the function of adding to the list
<br>- release everything I allocated; tried with valgrind and it works, that's why I released it like this

at 2.3: here I go through the list without an auxiliary node and average the values from
neighboring nodes, as required by the requirement, when a timestamp difference occurs
between 100 and 1000

at 2.5:
<br>- take a minimum and a maximum function, which calculates the minimum and maximum values
from the list, depending on the value field in the structure;
-delta1 and delta2 initially have the minimum and delta values
<br>- the two delta1 and delta2 increase along the delta, until the maximum value is reached
-every time, how many values from the list are counted between delta1 and delta2
<br>- and if there is at least one, the interval and the number of elements are displayed

in hand:
-allocate the list, better said the head of the list and tie it to null
<br>- I read the number of nodes and the elements on the keyboard and insert them
<br>- function functions one, twoone, twotwo, three, five (I didn't succeed in four) correspond
an argument
-ok=1 is not statistics, so the big list is displayed => not ok=1, so it is not displayed
the list, but only the statistics
-and at the end the elements from the big list are freed
