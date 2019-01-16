import random
import string
import os
import sys

def randstring():
	x = random.randint(10, 100);
	return ''.join(random.choice(string.ascii_uppercase + string.digits + string.ascii_lowercase) for _ in range(x))

def error(err):
	print(err)
	sys.exit()

while 1:
	print(randstring())
	x = random.randint(0, 10);
	i = 0;
	algo = "md5" if random.randint(0, 1) == 0 else "md5"
	command = "";
	file = 0;
	while (i < x):
		o = random.randint(0, 4)
		option = ""
		if (o == 0 and file == 0):
			option = "-s " + randstring()
		elif (o == 1 and file == 0):
			option = "-q"
		elif (o == 2 and file == 0):
			option = "-r"
		elif (o == 3 and file == 0):
			option = "-p"
		elif (o == 4):
			name = str(i) + '_test.test'
			f = open(name, 'w')
			f.close()
			f = open(name, 'w')
			f.write(randstring())
			f.close()
			option = name
			file = 1
		command += option + " "
		i += 1
	s = randstring()
	os.system("echo \"" + s + "\" | ./ft_ssl " + algo + " " + command + " > mine_test.test")
	print("echo \"" + s + "\" | ./ft_ssl " + algo + " " + command + " > mine_test.test")
	if (algo == "md5"):
		os.system("echo \"" + s + "\" | md5 " + command + " > real_test.test")
	elif (algo == "sha256"):
		os.system("openssl sha -sha256 " + command + " > real_test.test")
	f = open("mine_test.test", 'r')
	mine = f.read()
	f.close()
	f = open("real_test.test", 'r')
	real = f.read()
	f.close()
	if (mine != real):
		error('Error: ' + command)
	else:
		print("OK")
	os.system('rm -rf *_test.test')
