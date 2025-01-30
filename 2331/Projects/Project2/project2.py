def signed_magnitude(binary):
    sign = int(binary[0])
    magnitude = int(binary[1:], 2)
    return -magnitude if sign else magnitude

def ones_complement(binary):
    sign = int(binary[0])
    if sign:
        flipped = ''.join('1' if b == '0' else '0' for b in binary[1:])
        return -int(flipped, 2)
    return int(binary[1:], 2)

def twos_complement(binary):
    sign = int(binary[0])
    if sign:
        flipped = ''.join('1' if b == '0' else '0' for b in binary[1:])
        return -((int(flipped, 2)) + 1)
    return int(binary[1:], 2)

def floating_point(binary):
    sign = -1 if int(binary[0]) else 1
    exponent_bits = binary[1:4]
    mantissa_bits = binary[4:]

    exponent = int(exponent_bits, 2) - 3  # Bias is 3
    mantissa = 1 + sum(int(mantissa_bits[i]) * (2 ** -(i + 1)) for i in range(len(mantissa_bits)))

    return sign * mantissa * (2 ** exponent)

def main():
    binary = input("Enter an 8-bit binary number: ")
    if len(binary) != 8 or any(b not in '01' for b in binary):
        print("Invalid input.")
        return

    print("Signed Magnitude:", signed_magnitude(binary))
    print("One's Complement:", ones_complement(binary))
    print("Two's Complement:", twos_complement(binary))
    print("Floating Point:", floating_point(binary))

if __name__ == "__main__":
    main()
