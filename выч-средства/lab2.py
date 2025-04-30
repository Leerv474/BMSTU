def float_to_binary64(value):
    import struct

    packed = struct.pack('>d', value)  
    integers = struct.unpack('>Q', packed)[0]  
    binary_string = f'{integers:064b}'  
    return binary_string

def binary64_to_float(binary_string):
    import struct

    as_int = int(binary_string, 2)
    packed = struct.pack('>Q', as_int)
    value = struct.unpack('>d', packed)[0]
    return value


def unpack_binary64(binary_string):
    sign = int(binary_string[0], 2)
    exponent = int(binary_string[1:12], 2)
    mantissa = int(binary_string[12:], 2)
    return sign, exponent, mantissa

def pack_binary64(sign, exponent, mantissa):
    binary_string = f'{sign:1b}{exponent:011b}{mantissa:052b}'
    return binary_string


def add_binary64(bin_a, bin_b):
    sign_a, exp_a, mant_a = unpack_binary64(bin_a)
    sign_b, exp_b, mant_b = unpack_binary64(bin_b)

    
    if exp_a != 0:
        mant_a |= (1 << 52)
    if exp_b != 0:
        mant_b |= (1 << 52)

    
    if exp_a > exp_b:
        shift = exp_a - exp_b
        mant_b >>= shift
        exp_result = exp_a
    else:
        shift = exp_b - exp_a
        mant_a >>= shift
        exp_result = exp_b

    
    if sign_a == sign_b:
        mant_result = mant_a + mant_b
        sign_result = sign_a
    else:
        if mant_a >= mant_b:
            mant_result = mant_a - mant_b
            sign_result = sign_a
        else:
            mant_result = mant_b - mant_a
            sign_result = sign_b
    
    if mant_result == 0:
        return '0' * 64  
    while mant_result >= (1 << 53):
        mant_result >>= 1
        exp_result += 1
    while mant_result < (1 << 52):
        mant_result <<= 1
        exp_result -= 1

    
    mant_result &= ((1 << 52) - 1)

    return pack_binary64(sign_result, exp_result, mant_result)


def multiply_binary64(bin_a, bin_b):
    sign_a, exp_a, mant_a = unpack_binary64(bin_a)
    sign_b, exp_b, mant_b = unpack_binary64(bin_b)

    
    if exp_a != 0:
        mant_a |= (1 << 52)
    if exp_b != 0:
        mant_b |= (1 << 52)

    
    sign_result = sign_a ^ sign_b

    
    mant_result = mant_a * mant_b

    
    exp_result = exp_a + exp_b - 1023

    
    while mant_result >= (1 << 105):
        mant_result >>= 1
        exp_result += 1
    while mant_result < (1 << 104):
        mant_result <<= 1
        exp_result -= 1

    
    mant_result >>= 52

    
    mant_result &= ((1 << 52) - 1)

    return pack_binary64(sign_result, exp_result, mant_result)

import argparse

parser = argparse.ArgumentParser(description='Perform binary operations on floating point numbers.')
parser.add_argument('a', type=float, help='First float number')
parser.add_argument('b', type=float, help='Second float number')


args = parser.parse_args()


a = args.a
b = args.b

bin_a = float_to_binary64(a)
bin_b = float_to_binary64(b)
bin_b_neg = float_to_binary64(b * (-1))
print(a, " = ", bin_a)
print(b, " = ", bin_b)


print("sum:")
bin_sum = add_binary64(bin_a, bin_b)
print(binary64_to_float(bin_sum), " = ", bin_sum)  

print("difference:")
bin_difference = add_binary64(bin_a, bin_b_neg)
print(binary64_to_float(bin_difference), " = ", bin_difference)

print("product:")
bin_product = multiply_binary64(bin_a, bin_b)
print(binary64_to_float(bin_product), " = ", bin_product) 

