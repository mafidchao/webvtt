#!/usr/bin/env python

"""
Loops through the directory path passed to it in sys.argv[1], finds any .test files, strips the .vtt file from it, and
saves it to a mirrored directory structure under webvtt/objdir/spec
"""

import os
import sys

def stripVTT(file_path):
  test_file = open(file_path, 'r')
  file_data = test_file.read()

  # Rip the VTT
  vtt_file = file_data[file_data.find('*/\n') + 3:]

def findTestFiles(root, fileList):
	#List the directory
	dirList = os.listdir(root)

	for d in dirList:
		#Join the folder and/or file name that has been listed to the root path
		dir_path = os.path.join(root, d)
		#If the path is a directory than recursivley walk the directory tree
		if os.path.isdir(dir_path):
			findTestFiles(dir_path, fileList)
		#If the file path is for a .test file than append it to the file list
		elif os.path.splitext(dir_path)[1] == ".test":
			fileList.append(dir_path)

def main():
	#List that will contain the file paths of the .test files
	fileList = list()
	findTestFiles(os.path.realpath(sys.argv[1]), fileList)

	for f in fileList:
		pass

if __name__ == '__main__':
	status = main()
	sys.exit(status)