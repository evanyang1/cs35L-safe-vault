#!/usr/bin/python

import random, sys, string
from optparse import OptionParser
from argparse import * 

class shuf:
	def __init__(self, filename):
		try:
			#if(options.input_lines): # if -e 
				#self.lines = sys.stdin.readLines() # read std input
			#else:
				f = open(filename, 'r')
				self.lines = f.readlines()
				f.close()
		except OSError as err:
			parser.error("File cannot be opened: {0}".format(err))
	def shuffle(self, list):
		random.shuffle(list)
		for j in range(0,len(list)):# ex: shuf assign1.html
			print list[j]
			print '\n'
	def shuffle_r(self, list): # ex: shuf -n 2 -r assign1.html
		while():
			random.shuffle(list)
			print list[0]
			print '\n'
	def shuffle_n(self, list, i):
		random.shuffle(list)
		for j in range(0,i):
			print list[j]
			print '\n'
	def shuffle_nr(self, list, i):
		for j in (0,i):
			random.shuffle(list)
			print list[0]
			print '\n'

	def chooseline(self):
		return random.choice(self.lines)

def main():
	
	version_msg = "%prog 2.0"
	usage_msg = """%prog [OPTION]... FILE

Output randomly selected lines from FILE."""

	parser = ArgumentParser("""version=version_msg,""")
	#parser.add_argument("--spongebob", nargs="+")
	parser.add_argument("-n", "--head-count", dest="numlines", help="output NUMLINES lines (default 1)")
	parser.add_argument("-r", "--repeat", action="store_true", dest="repeat", help="Lines can be outputted more than once. It's like drawing cards with replacement.")
	parser.add_argument("-e", "--echo", dest="input_lines", nargs='*', help="takes in arguments from the command line rather from a text file.")
	parser.add_argument("file", nargs='*') # for input file, 0 or more
	options = parser.parse_args()

	if len(options.file) > 1:
		print("shuf: too many file arguments")

	#if len(arguments) != 1 and options.input_lines == False:
		#parser.error("wrong number of operands")
	#input_file = arguments[0]

	try:
		if len(options.file) >= 1:
			generator = shuf(options.file[0]) # file array, only get first item
		#for index in range(numlines):
			#sys.stdout.write(generator.chooseline())
	except IOError as (errno, strerror):
		parser.error("I/O error({0}): {1}".format(errno, strerror))
	if options.input_lines:
		arr = options.input_lines
		random.shuffle(arr)
		for j in range(0,len(arr)):
			sys.stdout.write(str(arr[j]) + '\n')
	else:
		arr = []
		if options.repeat:
			# if n is not specified. With r
			
			if options.numlines or options.numlines == 0: # r with n
				try: # making sure we don't have letters
					options.numlines = int(options.numlines)
				except:
					parser.error("invalid NUMLINES: {0}".format(options.numlines))
				if options.numlines < 0:
					parser.error("negative count: {0}".format(options.numlines)) 
				for line in generator.lines:
					arr.append(line)
				for j in range(0,options.numlines):
					random.shuffle(arr)
					sys.stdout.write(arr[0])
				
				
				
				
					
			else: # r without n, like shuf -r  foo.txt
				
					
					
					
				try:
					while True:
						for line in generator.lines:
							arr.append(line)
							random.shuffle(arr)
							sys.stdout.write(arr[0])
				except KeyboardInterrupt:
					return
				
		if options.numlines or options.numlines == 0: # shuf -n 3 foo.txt
			try: # making sure we don't have letters
				options.numlines = int(options.numlines)
			except:
				parser.error("invalid NUMLINES: {0}".format(options.numlines))
			if options.numlines < 0:
				parser.error("negative count: {0}".format(options.numlines)) 				
			for line in generator.lines:
				arr.append(line)
			random.shuffle(arr)
			if options.numlines > len(arr):
				
				for j in range(0,len(arr)):
					sys.stdout.write(arr[j])
			else:
				for j in range(0,options.numlines):
					sys.stdout.write(arr[j])
		else: # -n only
			for line in generator.lines:
				arr.append(line)
			random.shuffle(arr)
			for j in range(0,len(arr)):
				sys.stdout.write(arr[j])
			
if __name__ == "__main__":
	main()
