#!/usr/bin/env python

"""
Loops through the directory path passed to it in sys.argv[1], finds any .test files, strips the .vtt file from it, and
saves it to a mirrored directory structure under webvtt/objdir/spec
"""

import os
import sys

def findTestFiles(root):

	dirList = os.listdir(root)

	for d in dirList:

		dir_path = os.path.join(root, d)

		if os.path.isdir(dir_path):
			findTestFiles(dir_path)
		elif os.path.splitext(dir_path)[1] == ".test":
			#call jordan function here. pass dir_path as file path
			print dir_path

def main():
	findTestFiles(os.path.realpath(sys.argv[1]))

if __name__ == '__main__':
	status = main()
	sys.exit(status)
