esim: hsim.o 
	gcc -Wall -std=c99 hsim.o  -o esim -lm 

hsim.o: hsim.c 
	gcc -Wall -std=c99 -c hsim.c  -lm 

clean:
	-rm -f *.o esim hsimData.txt core
