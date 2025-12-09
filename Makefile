CC = gcc 
CFLAGS = -Wno-trigraphs
main : genevilx.c 
	$(CC) $(CFLAGS) -o main genevilx.c
clean: 
	rm -rf *.o main