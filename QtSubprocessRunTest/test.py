import time
import numpy as np
import matplotlib.pyplot  as polt
if __name__ == "__main__":
    print('subprocess test start')
    time.sleep(2)
    x = np.arange(0, 5, 0.1)
    y = np.sin(x)
    polt.plot(x, y) 
    # polt.show()
    print('subprocess test end')
    pass