import random
import string
import os
import sys

def randstring():
	x = random.randint(0, 9999);
	return ''.join(random.choice(string.ascii_uppercase + string.digits + string.ascii_lowercase) for _ in range(x))

def error(err):
	print(err)
	sys.exit()

while 1:
	algo = "md5" if random.randint(0, 1) == 0 else "sha256"
	command = ""
	s = randstring()
	os.system("printf \"" + s + "\" | ./ft_ssl " + algo + " " + command + " > mine_test.test")
	if (algo == "md5"):
		os.system("printf \"" + s + "\" | md5 " + command + " > real_test.test")
	elif (algo == "sha256"):
		os.system("printf \"" + s + "\" | openssl sha -sha256 > real_test.test")
	f = open("mine_test.test", 'r')
	mine = f.read()
	f.close()
	f = open("real_test.test", 'r')
	real = f.read()
	f.close()
	if (mine != real):
		error('Error: ' + algo + " " + s)
	else:
		print("OK")
	os.system('rm -rf *_test.test')
