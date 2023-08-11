import scribl
import unittest


tests =[(b'pat', b'\x00\x00\x00',b'\x70\x61\x74'), \
        (b'pat', b'\x01\x01\x01', b'\x71\x60\x75'), \
        (b'pat', b'\x01', b'\x71\x60\x75'), \
        (b'pat', b'\x00\x01\x02\x03\x04', b'\x70\x60\x76'), \
        (b'patrick', b'\x00\x00\x00', b'\x70\x61\x74\x72\x69\x63\x6B'), \
        (b'patrick', b'\x01\x01\x01', b'\x71\x60\x75\x73\x68\x62\x6A'), \
        (b'patrick', b'\x01', b'\x71\x60\x75\x73\x68\x62\x6A'), \
        (b'patrick', b'\x00\x01\x02\x03\x04', b'\x70\x60\x76\x71\x6D\x63\x6A')]

tests2 = ['This is a secret message.', 'Hello World!', 'echo \'Hello World!\'']

TEST_FILE = 'img/snowman.png'


def check_end_of_file():
    f = open(TEST_FILE, mode='rb')
    f.seek(-128, 2)
    print(f.read())
    f.close()


class read_from_file_test(unittest.TestCase):
    
    def test_read_from_file(self):
        
        print('\nBEGIN TEST READ_FROM_FILE')
        for t in tests2:
            scribl.write_to_file(TEST_FILE, t)
            msg = scribl.read_from_file(TEST_FILE).decode()
            self.assertEqual(msg, t)
            print(f'written: {t} decoded: {msg}')

        print('END TEST READ_FROM_FILE')

class write_to_file_test(unittest.TestCase):
    
    def test_write_to_file(self):
        print('\nBEGIN TEST WRITE_TO_FILE')
    
        check_end_of_file()
        scribl.write_to_file(TEST_FILE, 'This is a test')
        check_end_of_file()
    
        print('END TEST WRITE_TO_FILE')


class encode_msg_test(unittest.TestCase):
    
    def test_encode_msg(self):
        print('\nBEGIN TEST ENCODE_MSG')

        for t in tests:
            encoded_msg = scribl.encode_msg(t[1], t[0])
            print(f'msg: {t[0]} otp: {t[1]} test: {t[2]} encoded_msg: \
{encoded_msg}')
            self.assertEqual(encoded_msg, t[2]) 

        print('END TEST ENCODE_MSG')


class decode_msg_test(unittest.TestCase):

    def test_decode_msg(self):
        print('\nBEGIN TEST DECODE_MSG')

        for t in tests:
            decoded_msg = scribl.decode_msg(t[1], t[2])
            print(f'msg: {t[2]} otp: {t[1]} test: {t[0]} decoded_msg: \
{decoded_msg}')
            self.assertEqual(decoded_msg, t[0]) 

        print('END TEST DECODE_MSG')


class generate_otp_test(unittest.TestCase):
   
    def test_generate_otp(self):
        print('\nBEGIN TEST GENERATE_OTP')

        for t in tests:
            otp = scribl.generate_otp(t[1], t[2])
            self.assertEqual(len(t[0]), len(otp))

        print('END TEST GENERATE_OTP')


if __name__ == '__main__':
    unittest.main()
