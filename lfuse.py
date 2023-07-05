import sys

if (len(sys.argv) == 5 and (sys.argv[1] == "1" or sys.argv[1] == "2")):
    f1 = open(sys.argv[2], "r")
    f2 = open(sys.argv[3], "r")
    f1_lines = f1.readlines()
    f2_lines = f2.readlines()

    with open(sys.argv[4], "w") as out_file:

        if sys.argv[1] == "1":
            for f1_l in f1_lines:
                f1_l=f1_l.replace('\n', '')
                out_file.write(f"{f1_l}:{f1_l}\n")
                for f2_l in f2_lines:
                    out_file.write(f"{f1_l}:{f2_l}")
                out_file.write(f"\n{f1_l}:\n")

        elif sys.argv[1] == "2":
            if len(f2_lines) >= len(f1_lines):
                for i in range(len(f1_lines)):
                    f1_l=f1_lines[i].replace('\n', '')
                    out_file.write(f"{f1_l}:{f2_lines[i]}")
            else:
                for i in range(len(f2_lines)):
                    f1_l=f1_lines[i].replace('\n', '')
                    out_file.write(f"{f1_l}:{f2_lines[i]}")
else:
    print('\n####\n\nFuses two files into one. A:B format.\n\n\
MODES:\n1 - Every line in F1 gets fused to every line in F2.\n\
2 - F1 and F2 are fused line by line. The smallest list determines output size.\n\n\
USAGE: lfuse.py <MODE> <F1> <F2> <OUT-FILE>\n\n####\n')