import os
import glob
import subprocess


path = os.path.join(os.getcwd(),'sudokus')
# subprocess.Popen('"C:\\Program Files (x86)\\CodeBlocks\\MinGW\\bin"\\gcc.exe sudoku.c -o sudoku.exe',shell=True)

file_number = 1
for filename in glob.glob(os.path.join(path, '*.dat')):
	f = open(filename, 'r')
	i = 0
	sudoku_str = "{"
	sudoku_str2 =""
	for line in f:
		if (i>1):
			sudoku_str+= "{"
			line = line.split()						
			# print(line)
			aux = 0
			for number in line:
				sudoku_str += str(number)
				sudoku_str2 += str(number)
				if(aux < 8):
					sudoku_str+=","
				aux = aux + 1
			sudoku_str += "}"
			if(i<10):
				sudoku_str+=","
		i+=1
	sudoku_str += "}"
	print(sudoku_str2)
	subprocess.Popen('sudoku.exe '+sudoku_str2+'>> output\\output_'+str(file_number)+'.txt',shell=True)
	
	print('\n')
	f.close()
	file_number += 1
