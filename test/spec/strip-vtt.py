#!/usr/bin/env python
"""
strip-vtt.py

This program will Rip the WebVTT section out of the .test file whose path is passed via the first system argument.
It will then copy that WebVTT information to a .vtt file under an object directory which mirrors the directory structure of the .text file. 
The path of the object directory is pass in the second system argument.
"""

import os
import sys
import errno
import re

def main():
	# Fail if missing arguments
	if len(sys.argv) < 3:
		print >> sys.stderr, "error: missing input/output filenames.\nusage: strip-vtt.py {infile} {outfile}\n"
		return -1

	# Open the .test file and read it
	try:
		testFile = open(sys.argv[1], 'rb')
		fileData = testFile.read()
		# Rip the VTT
        # The RegEx below searches for all characters between /* and */,
        # followed by a possible Windows carriage return, followed by
        # a newline character.
		res = re.search(r"/\*.*\*/\r?\n", fileData, re.M | re.S)
		if res == None:
			print "Malformed test file at:", sys.argv[1]
			return -1

		vttInfo = fileData[res.end():]

		# Get the directory path where the new .vtt file will be stored
		vttFileDirPath = os.path.dirname(sys.argv[2])

		# If the directory path of the .vtt file does not exist then create it
		try:
			os.makedirs(vttFileDirPath)
		except OSError as e:
			if e.errno == errno.EEXIST:
				pass
			else:
				print >> sys.strerr, "error: failed to create directory `{0}':\n{1}\n".format(vttFileDirPath,e.strerror)
				
		# Write vtt file
		try:
			vttFile = open(sys.argv[2], 'w')

			for fileLine in vttInfo:
				vttFile.writelines(fileLine)
		except IOError as e:
			print >> sys.stderr, "error: failed to open output file `{0}':\n{1}\n".format(sys.argv[1], e.strerror)
		finally:
			if vttFile:
				vttFile.close()
		
	except IOError as e:
		print >> sys.stderr, "error: failed to open input file `{0}':\n{1}\n".format(sys.argv[1], e.strerror)
	finally:
		if testFile:
			testFile.close()
			
if __name__ == '__main__':
	status = main()
	sys.exit(status)
