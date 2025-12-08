from tonsdk.boc import Cell, begin_cell, Slice
from tonsdk.contract import Address
import bitarray

def bit_parsing(address: str): 
    message = begin_cell()\
        .store_uint(15, 32)\
        .store_address(Address(address))\
        .store_coins(20000)\
    .end_cell()

    array = message.bits.array
    x = bitarray.bitarray()
    x.frombytes(array) 
    return x 

def cell_parsing(x): 
    op_code = int(x[:32].to01(), 2)
    print(op_code)
    del x[:32]
    del x[:3]
    wc = int(x[:8].to01(), 2)
    del x[:8]
    hash_part = hex(int(x[:256].to01(), 2))
    address = str(wc) + ':' + str(hash_part.split('0x')[1])
    print(Address(address).to_string(True, True,True))
    del x[:256]
    l = int(x[:4].to01(), 2)
    del x[:4]
    amount = int(x[:l * 8].to01(), 2)
    print(amount)


def main():
    address = 'EQBUI264Vxn-MtRYrh7RlZTJkKj58B77kibcvoyojpskJP2u'

    x_bit = bit_parsing(address)

    cell_parsing(x_bit)


if __name__ == '__main__':
    main()
