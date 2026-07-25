import subprocess
n = 0
yes = True
arr = []
for i in range(1000):
	s = []
	r = subprocess.run("./codexion 10 91 300 10 200 13 0 edf",
					text=True, shell=True, capture_output=1)
	
	arr = r.stdout.split("\n")
	arr.remove("")
	s = [int(line[-2:]) for line in arr]
	if s == sorted(s):
		yes = False
		print(i)
		print([line for line in s])
		break

print(yes)