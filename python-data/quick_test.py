"""
==================
Animated histogram
==================

This example shows how to use a path patch to draw a bunch of
rectangles for an animated histogram.

"""
import numpy as np
import pandas as pd

import matplotlib.pyplot as plt
import matplotlib.patches as patches
import matplotlib.path as path
import matplotlib.animation as animation

events = pd.read_csv("timeseries_events.csv")
users  = pd.read_csv("timeseries_users.csv")
events = events.drop_duplicates() #many duplocates! idk if it was intentionally (to have same event for a user) or not I removed them, simply comment
users  = users.drop_duplicates()

###1
df_events_users = pd.merge(events, users, how ='left', on=['user_id']) 
df_events_users.dropna(inplace=True)
df_events_users = df_events_users[(df_events_users["age"] > 30) & (df_events_users["gender"] == 'm')].reset_index()


#number of events for each age
df_events_count_age=df_events_users.copy()
df_events_count_age = df_events_count_age.groupby('age')['event_date'].count()
#df_events_count_age.groupby('age')['event_date'].count().plot.bar()
print(df_events_count_age)

plt.show()