This executable expect a password, when decompiled we can see three principal function.

The main, test and decrypt.

In the main we can follow the call to test with the user input and a magic number.

Then this magic number is substracted with the user input and should fall in the range from 1 to 21, otherwise a random value is choosen.

Finally the value is passed to decrypt where a XOR operation is applied on each character upon a magic string (Q}|u`sfg~sf{}|a3).

This operation must lead to the string "Congratulation!" in order to get acces to a /bin/sh

So the goal is to find with witch value the XOR operation is proceded.

Since all character is operated with the same value we just have to do the inverse operation XOR on the first character of the magic string and the expected string "Congratulation!"

To reverse the operation we just have to applied XOR expect string on magic string.

Q XOR C = 18

So the value is 18, let's reverse enginer test. In order to get the value 18 on the input of decrypt the substraction of the magic number with the user input must be 18.

The magic number is 322424845 so 322424845-18 = 322424827

Run the program, pass the password and get the passzord of user level04

```bash
~$ ./level03 
***********************************
*		level03		**
***********************************
Password:322424827
$ cat /home/users/level04/.pass
kgv3tkEb9h2mLkRsPkXRfc2mHbjMxQzvb2FrgKkf
```
