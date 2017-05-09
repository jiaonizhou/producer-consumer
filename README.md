COEN 283 Project 2
==================

Members
-------
Jiaoni Zhou jzhou@scu.edu
Chenjun Ling cling@scu.edu

Results
-------
### In what order were the integers printed?
Answer: The integers should be printed in the order of being added to the buffer.

>>> ./prodcon 5 1000
```
Thread1 0
Thread0 1
Thread3 2
Thread5 3
......
Thread4 664
Thread1 665
Thread0 666
Thread2 668
......

Thread3 998
Thread4 999 
```

Discussion
----------
1. How many of each integer should you see printed?
  Answer: One per integer.

2. In what order should you expect to see them printed? Why?
  Answer: We expect to see the integers to be printed in the sequence of being added to the buffer. In our case, it starts from 0 and continues as 1, 2, 3, 4, ..., depending on the second argument: the number of values to be added to the buffer. It is because each time the consumer thread always removes one value from the buffer head. However, it is utterly random which consumer thread has the turn to do the removal each time.

3. Did your results differ from your answers in (1) and (2)? Why or why not?
  Answer: Our result is consistent with our answers to (1) and (2).
