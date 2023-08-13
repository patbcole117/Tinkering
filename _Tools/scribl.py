import sys

MSG_SIZE_MAX_BYTES = 4

def encode_msg(otp_map, msg):
    otp = generate_otp(otp_map, msg)
    encoded_msg = bytearray()

    for i in range(len(msg)):
        encoded_msg.append(msg[i] ^ otp[i])
    
    return encoded_msg


def decode_msg(otp_map, msg):
    otp = generate_otp(otp_map, msg)
    decoded_msg = bytearray()

    for i in range(len(msg)):
        decoded_msg.append(msg[i] ^ otp[i])
    
    return decoded_msg


def write_to_file(file, msg):
    with open(file, mode='rb') as f:
        otp_map = f.read()
    with open(file, mode='ab') as f:
        f.write(encode_msg(otp_map, msg.encode('utf-8')))
        f.write(len(msg).to_bytes(MSG_SIZE_MAX_BYTES, 'big'))


def read_from_file(file):
    with open(file, mode='rb') as f:
        f.seek(-MSG_SIZE_MAX_BYTES, 2)
        msg_size = int.from_bytes(f.read(), 'big')
        msg_start = -(msg_size + 4)
        f.seek(msg_start, 2)
        encoded_msg = f.read()[:-MSG_SIZE_MAX_BYTES]
        
        f.seek(0)
        decoded_msg = decode_msg(f.read(), encoded_msg)

    return decoded_msg


def remove_from_file(file):
    pass


def generate_otp(otp_map, msg):    
    otp = bytearray(otp_map[:len(msg)])
    i = 0
    while len(otp) < len(msg):
        otp.append(otp[i])
        i +=1

    return otp


if __name__ == '__main__':
    pass
