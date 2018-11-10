CC=clang

AB: AB.o file.o
	$(CC) -o $@ $^ 

%o:%c %h
	$(CC) -c  $< 

AB.o : file.h
