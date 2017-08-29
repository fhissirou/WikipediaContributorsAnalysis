# -*- coding: utf-8 -*-




import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
plt.style.use('fivethirtyeight')

StrPathfileExtract="../data/output/extract_pages_infos.csv"
df = pd.read_csv(StrPathfileExtract)

df.values


bins = np.arange(100, 500, 100)

#df['category'] = np.digitize(df.Age, bins, right=True)

counts = df.groupby(['day', 'typeEdition']).typeEdition.count().unstack()
print(counts)

ax = counts.plot(kind='bar',stacked = False, colormap = 'Paired')

for p in ax.patches:
        ax.annotate(np.round(p.get_height(),decimals=0).astype(np.int64), (p.get_x()+p.get_width()/2., p.get_height()), ha='center', va='center', xytext=(1, 10), textcoords='offset points')

plt.xlabel ('jours')
plt.ylabel ('type edition')
plt.title("Comparaison des jours / type edition",fontsize=20)


#----------------------------------------------
count2s = df.groupby(['timeDay','typeEdition']).typeEdition.count().unstack()
print(counts)

ax = count2s.plot(kind='bar',stacked = False, colormap = 'Paired')

for p in ax.patches:
        ax.annotate(np.round(p.get_height(),decimals=0).astype(np.int64), (p.get_x()+p.get_width()/2., p.get_height()), ha='center', va='center', xytext=(1, 10), textcoords='offset points')

plt.xlabel ('time of Day')
plt.ylabel ('type edition')
plt.title("Comparaison time of Day / type edition",fontsize=20)


plt.show()