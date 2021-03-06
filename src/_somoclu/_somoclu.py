# -*- coding: utf-8 -*-

import pandas as pd
import somoclu
import numpy as np
import matplotlib.pyplot as plt


StrPathfileExtract="../../data/output/extract_pages_infos.csv"
#StrPathfileExtract="../../data/output/text.csv"

df = pd.read_csv(StrPathfileExtract)
night= df["night"]
morning= df["morning"]
afternoon= df["afternoon"]
evening= df["evening"]
data = df[["night","morning","afternoon","evening"]].as_matrix()

#data= np.float32(np.concatenate((night, morning, afternoon))) #, df["afternoon"], df["evening"])))
#print(data)

"""n_rows, n_columns = 100, 150
som = somoclu.Somoclu(n_columns, n_rows, data=data, maptype="planar",gridtype="rectangular")
som.train(epochs=100)
#som.view_umatrix()
som.view_umatrix(bestmatches=True)
"""

colors = ["red"] * 400
colors.extend(["green"] * 400)
colors.extend(["blue"] * 400)

n_rows, n_columns = 150, 180
som = somoclu.Somoclu(n_columns, n_rows, maptype="toroid",
                      compactsupport=False, initialization="pca")


som.train(data)
som.cluster()

print("plane")
som.view_component_planes()
print("U-matrix BMU")
som.view_umatrix(bestmatches=True)
print("U-matrix sans BMU")
som.view_umatrix()