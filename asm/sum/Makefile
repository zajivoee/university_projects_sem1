all: run

RESULT=main

compile: main.S Makefile sum.S
	gcc -g -no-pie sum.S main.S -I. -o $(RESULT)

run: compile
	./$(RESULT)

clean:
	rm -f $(RESULT)
