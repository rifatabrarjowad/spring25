def signed_magnitude(binary):
    sign = int(binary[0])
    magnitude = int(binary[1:], 2)
    return -magnitude if sign else magnitude

def main():
    binary = input("Enter an 8-bit binary number: ")
    if len(binary) != 8 or any(b not in '01' for b in binary):
        print("Invalid input. Please enter an 8-bit binary number.")
        return

    print("Signed Magnitude:", signed_magnitude(binary))

if __name__ == "__main__":
    main()
