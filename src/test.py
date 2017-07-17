import somoclu
import numpy as np
import matplotlib.pyplot as plt

c1 = np.random.rand(50, 2)/5
print("C1", c1)
c2 = (0.2, 0.5) + np.random.rand(50, 2)/5
print("C2", c2)
c3 = (0.4, 0.1) + np.random.rand(50, 2)/5
print("C3", c3)
data = np.float32(np.concatenate((c1, c2, c3)))
print(data)
colors = ["red"] * 50
colors.extend(["green"] * 50)
colors.extend(["blue"] * 50)

print(colors)

labels = list(range(150))
#labels[2] = None
#labels[41] = None
#labels[40] = None
n_rows, n_columns = 30, 50
som = somoclu.Somoclu(n_columns, n_rows, data=data, maptype="planar",gridtype="rectangular")
som.train(epochs=10)
som.view_umatrix(bestmatches=True, bestmatchcolors=colors, labels=labels)
som.view_umatrix(bestmatches=True,labels=labels)