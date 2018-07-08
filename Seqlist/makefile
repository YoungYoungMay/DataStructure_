.PHONY :clean
.PHONY : Seqlist

Seqlist : Seqlist.o
	gcc $^ -o $@

%.o : %.c
	gcc -c $^ -o $@

clean:
	rm -f *.o Seqlist
