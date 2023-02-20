# importing modules
import pandas as pd
import os
import matplotlib.pyplot as plt

players_df = {}

path = "../doc/csv/";
for filename in os.listdir(path): #Read all sensor data
    if (filename.endswith('.csv')):
        # read (x,y) columns of csv file using Pandas
        df = pd.read_csv(path+filename, usecols = ['x','y'])
        players_df[filename] = df
        print(players_df[filename])

for player, df in players_df.items(): #Simple plot visualisation
    plt.plot(df['x'], df['y'], label = player)

plt.legend()
plt.show()
	

