import os
import sys
import subprocess
import commands

def f(file_path):
  test_file = open(file_path, 'r')
  file_data = test_file.read()

  vtt_file = file_data[file_data.find('*/\n') + 3:]
  
  print vtt_file

def main():
  f('/Users/jordanraffoul/repos/webvtt/test/spec/good/TC001_CueTextSubclass.test')

if __name__ == '__main__':
  status = main()