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
