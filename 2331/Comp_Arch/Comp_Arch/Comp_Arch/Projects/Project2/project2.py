"""
Project 2 - 8 Bit Number Representations
COSC 2331 | Spring 2025
Instructor: Megan Avery

Hello Adventurer! This program prompts the user for an 8-bit binary number (string) and 
displays its interpretation in four formats:
  1. Signed Magnitude
  2. One's Complement
  3. Two's Complement
  4. Custom Floating Point (1 sign bit, 3 exponent bits with bias = 3, 4 mantissa bits)

Usage:
  1) Run this script: python project2.py
  2) Enter an 8-bit binary string when prompted.
  3) View each interpretation printed to the console.
"""

def parse_signed_magnitude(binary_str: str) -> int:
    """
    Interprets the 8-bit binary string as a Signed Magnitude value.

    - The first bit is the sign bit (0 = '+', 1 = '-').
    - The remaining 7 bits represent the magnitude.
    """
    sign_bit = binary_str[0]
    magnitude_bits = binary_str[1:]
    magnitude = int(magnitude_bits, 2)

    if sign_bit == '1':
        return -magnitude
    else:
        return magnitude

def parse_ones_complement(binary_str: str) -> int:
    """
    Interprets the 8-bit binary string as a One's Complement value.

    - The first bit is the sign bit (0 = positive, 1 = negative).
    - For a negative number, the value is -((2^7 - 1) - magnitude_of_lower_7_bits).
    """
    sign_bit = binary_str[0]
    magnitude_bits = binary_str[1:]
    magnitude = int(magnitude_bits, 2)

    if sign_bit == '0':
        return magnitude
    else:
        # Negative range is -(127 - magnitude)
        return -((2**7 - 1) - magnitude)

def parse_twos_complement(binary_str: str) -> int:
    """
    Interprets the 8-bit binary string as a Two's Complement value.

    - If the leading bit is 0, the value is just int(binary_str, 2).
    - If the leading bit is 1, subtract 2^8 from that value to get the negative number.
    """
    value = int(binary_str, 2)
    if binary_str[0] == '1':
        value -= 2**8  # 256
    return value

def parse_custom_float(binary_str: str) -> float:
    """
    Interprets the 8-bit binary string as a custom floating-point number with:
      - 1 sign bit
      - 3 exponent bits (with bias = 3)
      - 4 mantissa bits

    The layout is: [ sign | exponent(3 bits) | mantissa(4 bits) ]

    We assume no special handling for denormals or infinity/NaN cases.
    The 'hidden bit' (leading 1) is used as usual for normalized numbers.
    """
    sign_bit = binary_str[0]
    exponent_bits = binary_str[1:4]
    mantissa_bits = binary_str[4:]

    # Determining the sign
    sign = 1.0 if sign_bit == '0' else -1.0

    # Calculating exponent (with bias = 3)
    exponent_val = int(exponent_bits, 2) - 3

    # Constructing the mantissa (1 + fraction from the bits)
    mantissa = 1.0
    for i, bit_char in enumerate(mantissa_bits, start=1):
        mantissa += int(bit_char) * (2 ** -i)

    # Computing the final float value
    float_value = sign * (mantissa * (2 ** exponent_val))
    return float_value

def format_with_sign(value: float) -> str:
    """
    Formats the numeric value with an explicit '+' sign for non-negative values,
    and a '-' sign for negative values, matching the sample output style.
    """
    if value >= 0:
        return f"+{value}"
    else:
        return f"{value}"

def main():
    """
    Main driver of the program:
      1) Prompt user for an 8-bit binary string.
      2) Calculate the interpretations.
      3) Print the results according to the project's requirements.
    """
    binary_input = input("Enter a binary number (8 bits): ").strip()

    # Basic validation just cause its nice
    if len(binary_input) != 8 or any(b not in "01" for b in binary_input):
        print("Error: Please enter exactly 8 bits (0 or 1).")
        return

    # Calculating each interpretation
    signed_mag_val = parse_signed_magnitude(binary_input)
    ones_comp_val = parse_ones_complement(binary_input)
    twos_comp_val = parse_twos_complement(binary_input)
    float_val = parse_custom_float(binary_input)

    # Print results to match the sample runs
    print(f"Signed Magnitude: {format_with_sign(signed_mag_val)}")
    print(f"One's Complement: {format_with_sign(ones_comp_val)}")
    print(f"Two's Complement: {format_with_sign(twos_comp_val)}")

    # We format the float to avoid long decimals.
    # but let's use a small rounding just in case.
    float_str = f"{float_val:.5g}"  # up to 5 significant digits
    # Re-add sign explicitly
    if float_val >= 0:
        float_str = f"+{float_str}"
    print(f"Floating Point: {float_str}")

if __name__ == "__main__":
    main()