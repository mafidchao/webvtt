#!/usr/bin/env python

"""
Loops through the directory path passed to it in sys.argv[1], finds any .test files, strips the .vtt file from it, and
saves it to a mirrored directory structure under webvtt/objdir/spec
"""

import os
import sys
import errno

def main():
	# Fail if missing arguments
	if len(sys.argv) < 3:
		print >> sys.stderr, "error: missing input/output filenames.\nusage: strip-vtt.py {infile} {outfile}\n"
		return -1

	# Open the .test file and read it
	try:
		testFile = open(sys.argv[1], 'r')
		fileData = testFile.read()

		# Rip the VTT
		vttInfo = fileData[fileData.find('*/\n') + 3:]

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