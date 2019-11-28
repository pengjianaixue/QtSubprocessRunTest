import time
import numpy as np
import matplotlib.pyplot  as polt
import threading as thread
def run():
    for i in range(1,1000):
        time.sleep(0.3)
        print('thread print')
    pass
if __name__ == "__main__":
    print('subprocess test start')
    t = thread.Thread(target=run)
    t.setDaemon(False)
    t.start()
    time.sleep(2)
    x = np.arange(0, 5, 0.1)
    y = np.sin(x)
    polt.plot(x, y) 
    # polt.show()
    time.sleep(2)
    print('subprocess test end')
    pass