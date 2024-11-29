```python
def calculate_serial(username):
    # Ensure username has at least 4 characters to avoid index errors
    if len(username) < 4:
        raise ValueError("Username must be at least 4 characters long.")

    # Calculate the initial serial value using the 4th character of the username
    calculated_serial = (ord(username[3]) ^ 0x1337) + 6221293

    # Loop through each character in the username
    for char in username:
        # Check for control characters
        if ord(char) <= 31:
            raise ValueError("Username contains control characters, which are not allowed.")

        # Update `calculated_serial` based on each character in username
        calculated_serial += (calculated_serial ^ ord(char)) % 0x539

    return calculated_serial

# Example usage
username = input("Enter username: ")
try:
    serial = calculate_serial(username)
    print(f"Calculated serial for '{username}': {serial}")
except ValueError as e:
    print(e)
```

## Other method

There is a canary catching with ptrace any debugger
We can bypass this in gdb: https://gist.github.com/poxyran/71a993d292eee10e95b4ff87066ea8f2

```
catch syscall ptrace
Catchpoint 1 (syscall 'ptrace' [26])
```

Then we can specify a list of actions to perform when we hit the catchpoint:

```
commands 1
> set $eax=0
> continue
> end
```

These lines will be executed when catching the syscall allowing us to continue debugging

Later in the function, right before we exit the function we check if the value of the serial is equal to the one we entered

```
0x8048866 <auth+286>    cmp    -0x10(%ebp), %eax
0x8048869 <auth+289>    je     0x8048872 <auth+298>
0x804886b <auth+291>    mov    $0x1,%eax
0x8048870 <auth+296>    jmp    0x8048877 <auth+303>
0x8048872 <auth+298>    mov    $0x0,%eax
```

We should be able to print the value compared to eax:

```
b* auth+286
commands 2
> x/x $ebp-0x10
> end
```

We obtain:

```
Catchpoint 1 (call to syscall ptrace), 0xf7fdb440 in __kernel_vsyscall ()
Catchpoint 1 (returned from syscall ptrace), 0xf7fdb440 in __kernel_vsyscall ()
Breakpoint 2, 0x08048866 in auth ()
0xffffd618:	0x005f1afc
(gdb) quit
```

0x005f1afc in decimal = 6232828 (for user dylann)

FLAG
```
GbcPDRgsFK77LNnnuh7QyFYA2942Gp8yKj9KrWD8
```
