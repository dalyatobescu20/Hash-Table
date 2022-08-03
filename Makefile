build: 
	gcc -o tema1 hash_table.c linked_list.c main.c -std=gnu11
run:
	./tema1

clean:
	rm -rf tema1

