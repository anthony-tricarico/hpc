import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("../data/scatter.csv")

# print(df.head())

df.plot("n", "ttime (sec)") 
plt.show()
