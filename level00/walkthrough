We can see a ./level00 executable how show a prompt asking for a password.

We choose to decompile the program and in the source code we saw that the input is handle by a scanf called expecting an integer.
The line following this call will check if the password provided by the user match the harcoded password in the executable.
If the password match a block of code call the function system with "/bin/sh" as parameters.
Sadly the executable have access to the user called level01

So after passing the right password (5276), we get a shell where we get the password of the user level01

```bash
cat /home/user/level1/.pass
uSq2ehEGT6c9S24zbshexZQBXUGrncxn5sD5QfGL
```
