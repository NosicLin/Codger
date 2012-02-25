main:a1 b1 merge

a1:lexical_driver.o sl_a.o lexical.o a1.o
	gcc -o a1 lexical_driver.o sl_a.o lexical.o a1.o

b1:lexical_driver.o sl_b.o lexical.o b1.o
	gcc -o b1 lexical_driver.o sl_b.o lexical.o b1.o
merge:lexical_driver.o sl_merge.o lexical.o merge.o
	gcc -o merge lexical_driver.o sl_merge.o lexical.o merge.o sl_b.o sl_a.o
rm:
	rm -f *.o a1 b1 merge

