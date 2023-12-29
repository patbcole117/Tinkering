import logging
import math
import sys

def main():
    argc = len(sys.argv)
    if argc < 4 or argc > 5:
        print(f'{sys.argv[0]} 6 -30 24 DEBUG')
        return
    
    if argc == 5:
        logging.basicConfig(level=sys.argv[4])

    solve(int(sys.argv[1]), int(sys.argv[2]), int(sys.argv[3]))


def solve(A,B,C):
   # Ax^2 + Bx + C
    msg = "INPUT: "
    msg += 'x^2' if A == 1 else '-x^2' if A == -1 else f'{A}x^2'
    msg += " + " if B >= 0 else " - "
    msg += 'x' if B == 1 or B == -1 else f'{abs(B)}x'
    msg += " + " if C >= 0 else " - "
    msg += f'{abs(C)}'
    logging.info(msg)

    factor = A * C
    factors = helper_get_factors(factor)
    logging.info(f'ALL FACTORS {factors}')

    answers = []
    for f in factors:
        if f[0] + f[1] == B:
            answers.append(f)
    if len(answers) == 0:
        print("Cannot factor.")
        return
    logging.info(f'GOOD FACTORS: {answers}')

    msg = ""
    for answer in answers:
        msg = 'x^2' if A == 1 else '-x^2' if A == -1 else f'{A}x^2'
        msg += " + " if answer[0] >= 0 else " - "
        msg += 'x' if abs(answer[0]) == 1 else f'{abs(answer[0])}x'
        msg += " + " if answer[1] >= 0 else " - "
        msg += 'x' if abs(answer[1]) == 1 else f'{abs(answer[1])}x'
        msg += " + " if C >= 0 else " - "
        msg += f'{abs(C)}'
        logging.info(msg)

    if A == 1:
        logging.debug("A == 1")
        for answer in answers:
            msg = "(x"
            msg += " + " if answer[0] >= 0 else " - "
            msg += f'{abs(answer[0])})(x'
            msg += " + " if answer[1] >= 0 else " - "
            msg += f'{abs(answer[1])})'
            print(msg)
        return
    
    # A != 1 && len(answers) != 0
    logging.debug("A != 1 && len(answers) != 0")
    for answer in answers:
        gcd1 = int(math.gcd(A, answer[0])   if A >= 0   else -1 * math.gcd(A, answer[0]))
        gcd2 = int(math.gcd(C, answer[1])   if C >= 0   else -1 * math.gcd(C, answer[1]))
        if A/gcd1 < 0: gcd1 *= -1
        if answer[1]/gcd2 < 0: gcd2 *= -1
        gcd3 = int(math.gcd(gcd1, gcd2)     if gcd1 >= 0   else -1 * math.gcd(gcd1, gcd2))
        logging.debug(f'GCD [({gcd1}, {gcd2}, {gcd3})]')

        ans1_div_gcd2   = int(answer[1]/gcd2)
        c_div_gcd2      = int(C/gcd2)
        gcd1_div_gcd3   = int(gcd1/gcd3)
        gcd2_div_gcd3   = int(gcd2/gcd3)
        
        msg = 'x(' if abs(gcd1) == 1 else f'{gcd1}x('
        msg += 'x' if abs(int(A/gcd1)) == 1 else f'({int(A/gcd1)}x'
        msg += " + " if answer[0]/gcd1 >= 0 else " - "
        msg += f'{abs(int(answer[0]/gcd1))})'
        msg += " | "
        msg += f'{gcd2}(x' if abs(ans1_div_gcd2) == 1 else f'{gcd2}({ans1_div_gcd2}x'
        msg += " + " if C/gcd2 >= 0 else " - "
        msg += f'{abs(c_div_gcd2)})'
        logging.info(msg)

        msg = '(x' if abs(gcd1) == 1 else f'({gcd1}x'
        msg += " + " if gcd2 >= 0 else " - "
        msg += f'{abs(gcd2)})'
        msg += " (x" if abs(ans1_div_gcd2) == 1 else f' ({ans1_div_gcd2}x'
        msg += " + " if C/gcd2 >= 0 else " - "
        msg += f'{abs(c_div_gcd2)})'

        # gcd1 and gcd2 share a common factor other than 1 which can be pulled out.
        if gcd3 != 1:
            logging.debug("gcd1 and gcd2 share a common factor other than 1 which can be pulled out.")
            logging.info(msg)
            msg = f'{gcd3}(x' if abs(gcd1_div_gcd3) == 1 else f'{gcd3}({gcd1_div_gcd3}x'
            msg += " + " if gcd2/gcd3 >= 0 else " - "
            msg += f'{abs(gcd2_div_gcd3)})'
            msg += ' (x' if abs(ans1_div_gcd2) == 1 else f'({ans1_div_gcd2}x'
            msg += " + " if C/gcd2 >= 0 else " - "
            msg += f'{abs(c_div_gcd2)})'
        
        # The answer is a square.
        if gcd1_div_gcd3 == ans1_div_gcd2 and gcd2_div_gcd3 == c_div_gcd2:
            logging.debug("The answer is a square.")
            logging.info(msg)
            msg = "(" if abs(gcd3) == 1 else f'{gcd3}(' 
            msg += "x" if abs(gcd1_div_gcd3) == 1 else f'{gcd1_div_gcd3}x'
            msg += " + " if gcd2/gcd3 >= 0 else " - "
            msg += f'{abs(gcd2_div_gcd3)})^2' 

        print(msg)


def helper_get_factors(number):
    factors = []
    limit = int(math.sqrt(abs(number))) + 1
    for i in range(1, limit):
        if number % i == 0:
            factors.append((i, (int)(number/i)))
            if number < 0:
                factors.append((-i, abs((int)(number/i))))
            else:
                factors.append((-i, -(int)(number/i)))
    return factors


if __name__ == "__main__":
    main()