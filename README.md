# MINIX-3-operating-system
implement various algorithms used in operating systems that have been studied in class on MINIX 3 operating system. MINIX 3 is a free open-source operating system based on a tiny microkernel running in kernel mode with the rest of the operating system running as a number of isolated, protected, processes in user mode




in the primary Interface you will se a folder called (mnt) 
this contain all the files we Modified to meet All the Requirments for the Project


you will Find the files:

1- REQ 1
2- REQ 2
3- REQ 3


each file has differnet prupose in MINIX 3 OS System 

we only uploaded the primary folders ( servers & mnt ) you can replace them by using SSH 

you can download the SSH using this tutorial link : https://www.youtube.com/watch?v=lwAEwkD0WZU&t=805s


finally you put this command to access the MINIX files: /usr/pkg/etc/rc.d/sshd start

to run these files you need to go the place where are they originally exist and replace them 

i'm providing an Example to how to do that and compile these files: 
 

This is an example on how to compile one part of Req 1 ( MFQ Algo)


this apply to all the files to compile them and see if there any errors that happens.

./MFQ

Change the following files:
/usr/src/servers/sched/schedule.c
/usr/src/servers/sched/schedproc.h
/usr/src/include/minix/config.h

cp /mnt/Algorithms/MFQ/schedule.c /usr/src/servers/sched/schedule.c
cp /mnt/Algorithms/MFQ/schedproc.h /usr/src/servers/sched/schedproc.h
cp /mnt/Algorithms/MFQ/config.h  /usr/src/include/minix/config.h

To run the scheduler:
	in /usr/src/include/minix/
		# make 
		# make install
	in /usr/src/servers/sched
		# make
		# make install

Then, go to /usr/src
	# make clean
	# make build
	# make install

Then,
	# reboot


To test the algorithm
This can be done within the shared folder. 
cc test.c -o test
./test
