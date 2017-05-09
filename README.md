COEN 283 Project 2
==================

Members
-------
Jiaoni Zhou jzhou@scu.edu
Chenjun Ling cling@scu.edu

Results
-------
### In what order were the integers printed?
Answer: The printed number order is the same as the producer generates, but the corresponding consumer order is random.
```
Thread1 0
Thread0 1
Thread1 2
Thread0 3
......
Thread0 664
Thread1 665
Thread0 666
Thread0 668
......
```

Discussion
----------
1. How many of each integer should you see printed?
  Answer: One time printed per integer.

2. In what order should you expect to see them printed? Why?
  Answer: Randomly. Because consumer threads are competing to read the buffer, which order is controlled by the OS, not the code.

3. Did your results differ from your answers in (1) and (2)? Why or why not?
  Answer: No different.
