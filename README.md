# tema-1-SDA


In ceea ce priveste structurile am folosit:
-->structura pentru tabela hash
-->structura pentru lista in care sunt pastrate nr de elemente pentru cuvinte
-->structura pentru nod
-->structura pentru cuvinte( in wordlist sunt cuvintele care au o anumita
 lungime si in structura word am pus fiecare cuvant si nr de aparitii)

Partea de linked list:
PS: nu prea am ce explica, le avem si in laburi, am lasat comm-uri in cod
Functii elementare :
-->creare de lista
-->adaugare nod in lista
-->stergere nod
-->eliberare memorie lista
-->functie care interschimba nodurile
-->functie de sort in functie de criteriul de comparatie

Partea de hash-list:
-->functie de comparare a doua cuvinte lexicografic
-->functia de hash care face legatura dintre elementele vectorului v si 
literele alfabetului,astfel, v[0] o sa corespunda literei a sau A etc
->crearea de tabela hash, creeaza o lista pentru fiecare element din tabela
-->functie de comparare a cuvintelor, in caz ca sunt in ordine descrescatoare
 return 1, in oridine crescatoare return -1 si daca nu le comparam lexicografic
-->functie de distrugere, elibereaza memoria
-->functie de insert(steps):
-daca cuvantul are dim < 3 nu ma intereseaza
-daca este un numar din nou nu ma intereseaza
-aplic functia hash pentru cuvantul pe care vreau sa l introduc
-verific daca exista deja in tabela dimensiunea, daca nu, o adaug;
-daca avem deja cuvinte de aceeasi lungime, adaugam in lista de cuvinte,
-daca cuvantul exista deja in tabela, ii crestem frecventa primului introdus 
 si-l eliberam pe urmatorul
-->functie de print:
-primul print simplu este destul de banal, parcurgem tabela si printam
-al doilea print are in plus doar conditia ca dim cuvintelor sa fie = n 
si sa inceapa cu un c
-la al treilea print am pus conditia sa fie frecventa <= max 
si am adaugat bool uri pentru a putea printa bine virgulele si parantezele
