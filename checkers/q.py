import os
import subprocess

def main():
	# filename = input("paste .s file:\n")
	for filename in 'Car.s      Gagnant.s  Gagnant2.s bee_gees.s bigzork.s  ex.s       new.s      zork.s'.split():
		filename = os.path.join("champions", filename)
		subprocess.call(["./vm_champs/asm", filename])
		with open(filename[:-2] + '.cor', 'rb') as f:
			correct_bytecode = f.read()
		subprocess.call(["./asm", filename])
		with open(filename[:-2] + '.cor', 'rb') as f:
			my_bytecode = f.read()
		if len(correct_bytecode) != len(my_bytecode):
			print("different length: " + "\ncorrect len: " + str(len(correct_bytecode)) + "\nmy len: " + str(len(my_bytecode)))
		# print()
		num = 0
		for correct_byte, my_byte in zip(correct_bytecode, my_bytecode):
			# print(str(num) + ':', correct_byte, my_byte)
			if correct_byte != my_byte:
				print("number of byte: " + str(num))
				print("correct byte: " + str(correct_byte) + "\nmy byte: " + str(my_byte))
				break
			num += 1

if __name__ == '__main__':
	main()