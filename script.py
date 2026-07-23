import subprocess
n = 0
for i in range(1000):
	subprocess.run("./codexion 50 91 300 10 200 13 0 edf | wc -l", shell=True)