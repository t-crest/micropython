import patmos

print("Start")

num = 0
running = True
update = True

def updateLeds(num):
	bNum = bin(num)
        n = len(bNum)-1
        for i in range(n, 1, -1):
                if bNum[i] == "1":
                        patmos.setLed(n-i, True)
                else:
                        patmos.setLed(n-i, False)


def stop():
	global running
	running = False

def incLedg():
	global num, update
	num += 1
	if update:
		updateLeds(num)

def reset():
	global num
	num = 0
	#if update:
	patmos.setLeds(0)

def toggleUpdate():
	global num, update
	update = not update
	if update:
		updateLeds(num)

patmos.setIntr(patmos.KEY0, incLedg)
patmos.setIntr(patmos.KEY1, toggleUpdate)
patmos.setIntr(patmos.KEY2, reset)
patmos.setIntr(patmos.KEY3, stop)

patmos.info()
#patmos.setLed(0, True)
for i in range(9):
	print(f"LEDG{i}:", patmos.getLed(i))
	if patmos.getLed(i):
		patmos.setLed(i, False)
#print("Count!")
#for i in range(4):
#	print(f"KEY{i}:", patmos.getKey(i))

#To keep it running
while running:
	pass
"""	if patmos.getKey(0) == 0:
		print(1)
		num += 1
		print(2)
		bNum = bin(num)
		print(3)
		n = len(bNum)-1
		print(4)
		for i in range(n, 1, -1):
			if bNum[i] == "1":
				patmos.setLed(n-i, True)
			else:
				patmos.setLed(n-i, False)
		while patmos.getKey(0) == 0:
			pass
"""
#for i in range(9):
#	patmos.setLed(i, True)
#	for w in range(10000):
#		pass

#while 1:
#	pass

print("Done")
