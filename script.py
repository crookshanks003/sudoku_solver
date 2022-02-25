#format input grid

f = open("grid.txt", "r")
stri = f.read()
n = stri.split("\n")

new = ""

for line in n:
    for w in line.split(" "):
        new += w
        new += "\t"
    new += "\n"

print(new)

f = open("test16x16.txt", "a")
f.write(new)
f.close()
