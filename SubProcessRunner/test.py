import time
import numpy as np
import matplotlib.pyplot  as polt
import threading
def threadTestThread():
	for i in range(0,100):
		time.sleep(1)
		print("thread print i:{0}".format(i))
	pass
if __name__ == "__main__":
	t = threading.Thread(target=threadTestThread)
	t.start()
	for i in range(0,100):
		print('subprocess test start:{0}'.format(i))
		time.sleep(1)
		print('subprocess test end:{0}'.format(i))
	print('matplot draw...')
	x = np.arange(0, 5, 0.1)
	y = np.sin(x)
	polt.plot(x, y) 
	polt.show()
	pass