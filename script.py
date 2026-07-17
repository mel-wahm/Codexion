import subprocess
y = 0
n = 0
for i in range(100):
	out = subprocess.run("./a.out 44 33 1465105 55 660 10 0 edf | wc -l",
					  capture_output=True, shell=True, text=True)
	if (int(out.stdout) == 44):
		y += 1
	else:
		n += 1

print(y//10, "%", n//10, "%")