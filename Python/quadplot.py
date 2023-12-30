import sys
import logging

def main():
    argc = len(sys.argv)
    if argc < 4 or argc > 5:
        print(f'{sys.argv[0]} -4 16 -16 | DEBUG')
        return
    
    if argc == 5:
        logging.basicConfig(level=sys.argv[4])

    solve((float(sys.argv[1])), (float(sys.argv[2])), (float(sys.argv[3])))

def solve(A, B, C):
    logging.debug(f'A = {A}, B = {B}, C = {C}')
    xvert = ((-B)/(2*A))
    yvert = A*(xvert)**2 + B*(xvert) + C
    logging.debug(f'XVERT = {xvert}, YVERT = {yvert}')
    answers = [(xvert, yvert)]

    
    for i in range(1,10):
        y1 = round(A*(xvert + i)**2 + B*(xvert + i) + C, 2)
        y2 = round(A*(xvert - i)**2 + B*(xvert - i) + C, 2)
        answers.append((xvert+i, y1))
        answers.append((xvert-i, y2))

    print(*answers, sep="\n")

if __name__ == "__main__":
    main()