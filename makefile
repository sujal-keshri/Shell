# main:
# 	gcc -g main.c prompt.c

output: main.o pwd.o prompt.o warp.o peek.o proclore.o seek.o input_requirement.o execute.o utilities.o iman.o activities.o signals.o io_redirection.o neonate.o fg_bg.o pastevents.o
	gcc main.o pwd.o prompt.o warp.o peek.o proclore.o seek.o input_requirement.o execute.o utilities.o iman.o activities.o signals.o io_redirection.o neonate.o fg_bg.o pastevents.o

main.o: main.c headers.h
	gcc -c main.c

pwd.o: pwd.c pwd.h
	gcc -c pwd.c

prompt.o: prompt.c prompt.h
	gcc -c prompt.c

warp.o: warp.c warp.h
	gcc -c warp.c

peek.o: peek.c peek.h
	gcc -c peek.c

proclore.o: proclore.c proclore.h
	gcc -c proclore.c

seek.o: seek.c seek.h
	gcc -c seek.c

input_requirement.o: input_requirement.c input_requirement.h
	gcc -c input_requirement.c

execute.o: execute.c execute.h
	gcc -c execute.c

utilities.o: utilities.c utilities.h
	gcc -c utilities.c

iman.o: iman.c iman.h
	gcc -c iman.c

activities.o: activities.c activities.h
	gcc -c activities.c

signals.o: signals.c signals.h
	gcc -c signals.c

io_redirection.o: io_redirection.c io_redirection.h
	gcc -c io_redirection.c

neonate.o: neonate.c neonate.h
	gcc -c neonate.c
	
fg_bg.o: fg_bg.c fg_bg.h
	gcc -c fg_bg.c

pastevents.o: pastevents.c pastevents.h
	gcc -c pastevents.c

clean:
	rm *.o a.out