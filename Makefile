all: 
	gcc part11parallel.c -o part11parallel -lpthread
	
run:
	./part11parallel
