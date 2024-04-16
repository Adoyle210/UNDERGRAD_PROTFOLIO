import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

def main():
    t=0
    while(t==0):
        try:
            k=float(input("\033[0;30;46m "+"Enter thermal conductivity (k): "+"\033[0;30;0m"))
            k=float(k)
            t += 1
        except ValueError:
            print("\033[0;37;41m"+"Error bad input, Try again"+"\033[0;37;0m")
            t = 0
    while (t==1):
        try:
            c=float(input("\033[0;30;46m "+"Enter speific heat (c): "+"\033[0;30;0m"))
            c=float(c)
            t += 1
        except ValueError:
            print("\033[0;37;41m"+"Error bad input, Try again"+"\033[0;37;0m")
            t = 1
    while (t==2):
        try:
            rho=float(input("\033[0;30;46m "+"Enter density: "+"\033[0;30;0m"))
            rho=float(rho)
            t += 1
        except ValueError: 
            print("\033[0;37;41m"+"Error bad input, Try again"+"\033[0;37;0m")
            t = 2
    while(t==3):
        try:
            wire_temp=float(input("\033[0;30;46m "+"Enter the inital temp: "+"\033[0;30;0m"))
            wire_temp=float(wire_temp)
            t += 1
        except ValueError:
            print("\033[0;37;41m"+"Error bad input, Try again"+"\033[0;37;0m")
            t = 3
    while(t==4):
        try:
            temp_left=float(input("\033[0;30;46m "+"Enter the lowest temp: "+"\033[0;30;0m"))
            temp_left=float(temp_left)
            t += 1
        except ValueError:
            print("\033[0;37;41m"+"Error bad input, Try again"+"\033[0;37;0m")
            t = 4
    while(t==5):
        try:
            temp_right=float(input("\033[0;30;46m "+"Enter the hightest temp: "+"\033[0;30;0m"))
            temp_right=float(temp_right)
            t += 1
        except ValueError:
            print("\033[0;37;41m"+"Error bad input, Try again"+"\033[0;37;0m")
            t = 5
    while(t==6):
        try:
            wire_len=int(input("\033[0;30;46m "+"Enter the length of the wire:  "+"\033[0;30;0m"))
            wire_len=int(wire_len)
            t += 1
        except ValueError:
           print("\033[0;37;41m"+"Error bad input, Try again"+"\033[0;37;0m")
           t = 6
    while(t==7):
        try:
            wire_div=int(input("\033[0;30;46m "+"Enter the number of sections you want:  "+"\033[0;30;0m"))
            wire_div=int(wire_div)
            t += 1
        except ValueError:
            print("\033[0;37;41m"+"Error bad input, Try again"+"\033[0;37;0m")
            t = 7
    while(t==8):
        try:
            time=int(input("\033[0;30;46m "+"Enter the time: "+"\033[0;30;0m"))
            time=int(time)
            t += 1
        except ValueError:
            print("\033[0;37;41m"+"Error bad input, Try again"+"\033[0;37;0m")
            t = 8
    while(t==9):
        try:
            deltat=float(input("\033[0;30;46m "+"Enter the change in time:  "+"\033[0;30;0m"))
            deltat=float(deltat)
            t += 1
        except ValueError:
            print("\033[0;37;41m"+"Error bad input, Try again"+"\033[0;37;0m")
            t = 9
    deltax=wire_len/wire_div
    const=(k*deltat)/(deltax**2*c*rho)
    uold=[wire_temp]*wire_div
    uold[0]=temp_left
    uold[wire_div-1]=temp_right
    unew=[wire_temp]*wire_div
    unew[0]=temp_left
    unew[wire_div-1]=temp_right
    plotter = Wire_Plotter(wire_len, wire_div, temp_left, temp_right, True)
    for i in range(time):
        for x in range(1,wire_div-1):
            unew[x]=const*(uold[x+1]-2*uold[x]+uold[x+1])+uold[x]
        print(unew)
        uold=unew
        plotter.add_interval(unew)
    plotter.animate()
   
#wireplotter from lab
class Wire_Plotter:   
    def __init__(self, length, divisions, temp_min = 0, temp_max = 100, verbose = False):
        self.length         = length
        self.divisions      = divisions
        self.temp_min       = temp_min
        self.temp_max       = temp_max
        self.wire           = []
        self.verbose        = verbose

    def add_interval(self, wire):
        self.wire.append(list.copy(wire))
        self.out("INFO", "Added wire of length %d to plotter." % len(wire))

    def animate(self):
        if self.validate():
            self.out("INFO", "Starting diffusion animation.")
            animate1D(self.wire, self.length, self.divisions, self.temp_min, self.temp_max, smooth=True)
        else:
            self.out("ERROR", "Cannot animate, wire is not valid")

    def draw_interval(self, interval):
        self.validate()
        self.out("INFO", "Drawing wire at time interval %d" % interval)
        draw1D(self.wire[interval], self.length, self.divisions, self.temp_min, self.temp_max, smooth=True)
    
    def draw_last(self):
        self.validate() # Dont need to stop, but should show error
        self.draw_interval(-1)
    
    def validate(self):
        if len(self.wire) < 1:
            self.out("WARN","No intervals to show")
            return False

        size = len(self.wire[0])
        if not all(len(arr) == size for arr in self.wire):
            self.out("WARN","Not all intervals are the same size")
            return False
        return True

    def out(self, state, msg):
        if self.verbose:
            print("PLT-LIB::%-5s|| %s" % (state, msg))

def draw1D(values, wire_length, wire_divisions, temp_min = 0, temp_max = 100, **kwargs):

    smooth = 'none'
    if "smooth" in kwargs and kwargs['smooth'] == True:
            smooth = 'bilinear'

    plt.rcParams["figure.figsize"]  = 10, 4
    x = np.linspace(0,wire_length, wire_divisions)
    y = np.asarray(values)

    fig, (ax,ax2) = plt.subplots(nrows=2, sharex=True)

    imgCoords = [
        x[0]-(x[1]-x[0])/2.,    # Left
        x[-1]+(x[1]-x[0])/2.,   # Right
        0,                      # Bottom
        1]                      # Top
    
    ax.imshow(y[np.newaxis,:], cmap="plasma", aspect="auto", extent =imgCoords, interpolation = smooth, vmin = temp_min, vmax = temp_max)
    ax.set_yticks([])
    ax.set_xlim(imgCoords[0], imgCoords[1])
    

    ax2.plot(x,y)
    plt.tight_layout()
    plt.show()


def animate1D(all_values, wire_length, wire_divisions, temp_min = 0, temp_max = 100, timeModifier = 5, **kwargs):
    smooth = 'none'
    if "smooth" in kwargs and kwargs['smooth']:
            smooth = 'bilinear'

    plt.rcParams["figure.figsize"] = 10, 4
    x = np.linspace(0, wire_length, wire_divisions)
    y = np.asarray(all_values[0])

    fig, (ax,ax2) = plt.subplots(nrows=2, sharex=True)

    imgCoords = [
        x[0]-(x[1]-x[0])/2.,    # Left
        x[-1]+(x[1]-x[0])/2.,   # Right
        0,                      # Bottom
        1]                      # Top
    
    image = ax.imshow(y[np.newaxis,:], cmap="viridis", aspect="auto", extent = imgCoords, interpolation = smooth, vmin = temp_min, vmax = temp_max)
    ax.set_yticks([])
    ax.set_xlim(imgCoords[0], imgCoords[1])
    
    linePlot, = ax2.plot(x,y)
    
    def animate(i):
        y = np.asarray(all_values[i])
        
        image.set_array(y[np.newaxis,:])
        linePlot.set_ydata(y)
        return [image]
    
    ani = FuncAnimation(fig, animate, np.arange(0, len(all_values)), interval = 100, blit = False, repeat=False)

    plt.tight_layout()
    plt.show()
    del ani
    plt.close()



main()