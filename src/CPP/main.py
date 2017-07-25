import fonction


from pylab import imshow, show, get_cmap
import numpy as np
import matplotlib.pyplot as plt
import numpy as np
# In vecpython.cpp we expose hello() function, and it now exists in the vecpython module.
#assert 'hello' in dir(vecpython)
# vecpython.hello is a callable.
#assert callable(vecpython.hello)
# Call the C++ hello() function from Python.
data = fonction.runs()

print("dans le python")







l_x=[]
l_y=[]
color=[]
taile= len(data)
nx= 0; 
for x in data:
    ny=0
    for y in x:
        cc=[]
        for c in y:
            cc.append(c)
        color.append(cc)

        l_y.append(ny)
        ny+=1
        l_x.append(nx)
    nx+=1



#print(color)
#color=[0.2,0.7,0.1]

#mat= np.matrix(lm)
"""
plt.figure(figsize=(1,1))
x = [1,2,3]
#plt.plot(x, x)
#plt.show()
plt.xlim(-200, 200)
plt.ylim(-50, 50)
plt.imshow(lm, cmap=get_cmap("Spectral"), interpolation='nearest')
plt.show()
"""



x, y = np.random.random((2, 10))
#color = np.random.random((10, 3))

color= np.array(color)

fig, ax = plt.subplots()

ax.scatter(l_x, l_y,s=24, facecolors=color)
plt.show()