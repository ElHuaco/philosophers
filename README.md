Teoría:
- [Tutorial 1](https://hpc.llnl.gov/training/tutorials/introduction-parallel-computing-tutorial)
-	[Tutorial 2](https://computing.llnl.gov/tutorials/pthreads/)
- [Sincronización (IBM)](https://www.ibm.com/support/knowledgecenter/ssw_aix_71/generalprogramming/synch_overbmort.html)
- [Dining Philosophers](http://web.eecs.utk.edu/~mbeck/classes/cs560/560/notes/Dphil/lecture.html)

Test:
- [ ]./philo_x 5 800 200 200 -> No one should die
- [ ]./philo_x 5 800 200 200 7 -> No one should die
- [ ]./philo_x 4 410 200 200 -> No one should die
- [ x ] ./philo_x 4 310 200 100 -> One should die
- [ x ] ./philo_x 2 310 200 100 -> One should die
- [ x ] No more than 10ms from time of death to printing it.
- [socrates](https://github.com/nesvoboda/socrates)
