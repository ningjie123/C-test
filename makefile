main.out:libgenbank.so libfasta.so main.o
	gcc -lstdc++ -o main.out main.o -L./ -lgenbank -lfasta
libgenbank.so:first_line.o fopen.o getall.o
	gcc -lstdc++ -fPIC -shared -o libgenbank.so $^
libfasta.so:writetofasta.o
	gcc -lstdc++ -fPIC -shared -o libfasta.so $^
first_line.o:libgenbank.h first_line.c
	gcc -lstdc++ -c $^ -fPIC
fopen.o:libgenbank.h fopen.c
	gcc -lstdc++ -c $^ -fPIC
getall.o:getall.c libgenbank.h
	gcc -lstdc++ -c $^ -fPIC
writetofasta.o:libfasta.h writetofasta.c
	gcc -lstdc++ -c $^ -fPIC
main.o:main.c libgenbank.h libfasta.h
	gcc -lstdc++ -c $^
test:libgenbank.so libfasta.so main.o
	gcc -lstdc++ -o test main.o -L./ -lgenbank -lfasta
.PHONY:clean
clean:
	rm -f *.o
