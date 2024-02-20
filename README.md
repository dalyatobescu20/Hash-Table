# Hash Table Section

In terms of structures, the following were utilized:

- **Hash Table Structure:** Represents the hash table.
- **Word Count List Structure:** Stores the number of elements for words.
- **Node Structure:** Fundamental unit for linked lists.
- **Word Structure:** Contains words of a certain length and their occurrences.

# Linked List Section

PS: Basic functions are present as used in labs. Comments are left in the code.

Basic Functions Include:
- List creation
- Node insertion
- Node deletion
- Memory deallocation for the list
- Node swapping function
- Sorting function based on comparison criteria

# Hash-List Section

- **Word Comparison Function:** Compares two words lexicographically.
- **Hash Function:** Establishes a connection between the elements of the vector and the alphabet letters, where `v[0]` corresponds to the letter 'a' or 'A', and so on.
- **Hash Table Creation:** Creates a list for each element in the hash table.
- **Word Comparison Function:** Compares words; if in descending order, returns 1; if in ascending order, returns -1; otherwise, compares lexicographically.
- **Destruction Function:** Frees memory.
- **Insert Function (Steps):**
  - Ignore words with a length less than 3 or numerical values.
  - Apply the hash function to the word.
  - Check if the size already exists in the table; if not, add it.
  - If words of the same length already exist, add to the word list.
  - If the word already exists in the table, increase the frequency of the first occurrence and free the subsequent occurrence.
- **Print Function:**
  - The first print is straightforward, traversing the table and printing.
  - The second print additionally requires the condition that word length is `n` and starts with 'c'.
  - The third print has the condition that frequency is <= `max`, with added boolean variables for proper comma and parentheses printing.
