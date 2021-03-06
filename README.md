_"The challenge in the dining philosophers problem is to design a protocol so that the philosophers do not deadlock (i.e. the entire set of philosophers does not stop and wait indefinitely), and so that no philosopher starves (i.e. every philosopher eventually gets his/her hands on a pair of chopsticks)."_ Without allowing them to talk to each other, that is, they do not know whether another philosopher is either thinking, eating or sleeping.

![](https://miro.medium.com/max/544/1*kTNv4zAJfdhvM9l0LiwUaA.png)

Teoría:
- [Tutorial 1](https://hpc.llnl.gov/training/tutorials/introduction-parallel-computing-tutorial)
-	[Tutorial 2](https://computing.llnl.gov/tutorials/pthreads/)
- [Sincronización (IBM)](https://www.ibm.com/support/knowledgecenter/ssw_aix_71/generalprogramming/synch_overbmort.html)
- [Dining Philosophers](http://web.eecs.utk.edu/~mbeck/classes/cs560/560/notes/Dphil/lecture.html)

Test:
- [x] ./philo_x 5 800 200 200 -> No one should die
- [x] ./philo_x 5 800 200 200 7 -> No one should die
- [x] ./philo_x 4 410 200 200 -> No one should die.
- [x] ./philo_x 4 310 200 100 -> One should die
- [x] ./philo_x 2 310 200 100 -> One should die
- [x] No more than 10ms from time of death to printing it.
- [socrates](https://github.com/nesvoboda/socrates)
