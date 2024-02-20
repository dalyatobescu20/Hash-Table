build: 
	gcc -o hash hash_table.c linked_list.c main.c -std=gnu11
run:
	./hash

clean:
	rm -rf hash

