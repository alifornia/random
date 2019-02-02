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
from functools import reduce



deaths = pd.read_csv("deaths.csv")
deaths = deaths[deaths.columns.drop(list(deaths.filter(regex='flag')))]
deaths = deaths[deaths.columns.drop(list(deaths.filter(regex='Location')))]

deaths.rename(columns = {'Reporting Area':'area',
                         'MMWR YEAR': 'year',
                         'MMWR WEEK':'week',
                         'All causes, by age (years), All Ages**':'all',
                         'All causes, by age (years), LT 1':'LT 1',
                         'All causes, by age (years), 1–24':'1-24',
                         'All causes, by age (years), 25–44':'25-44',
                         'All causes, by age (years), 45–64':'45-64',
                         'All causes, by age (years), ≥65':'65+',
                         'P&I† Total':'total'},
                         inplace = True)

#totals in regions (quarters)
regions = deaths.loc[0:8, "area"].tolist()
deaths = deaths[deaths["area"].isin(regions)]

deaths["date"] = pd.to_datetime(deaths.year.astype(str), format='%Y') + \
                     pd.to_timedelta((deaths.week-1).mul(7).astype(str) + ' days')
deaths_Q = deaths.groupby(["area", pd.PeriodIndex(deaths.date, freq='Q')])["all"].sum()
deaths_Q = deaths_Q.unstack().rename(columns = {
            "2016Q1" : "2016Q1",
            "2016Q2" : "2016Q2",
            "2016Q3" : "2016Q3",
        })

deaths_Q.plot(kind='bar', stacked=True, rot=90, edgecolor='black')
plt.xlabel('area')
plt.ylabel('deaths')
plt.tight_layout(pad=0., w_pad=-16.5, h_pad=0.0)

deaths_Q.T.plot(kind='bar', stacked=True, rot=0, edgecolor='black')
plt.xlabel('area')
plt.ylabel('deaths')


##age in regions(quarter)
##df for different age buckets
deaths_65 = deaths.groupby(["area", pd.PeriodIndex(deaths.date, freq='Q')])["65+"].sum()
deaths_45_64 = deaths.groupby(["area", pd.PeriodIndex(deaths.date, freq='Q')])["45-64"].sum()
deaths_25_44 = deaths.groupby(["area", pd.PeriodIndex(deaths.date, freq='Q')])["25-44"].sum()
deaths_1_24 = deaths.groupby(["area", pd.PeriodIndex(deaths.date, freq='Q')])["1-24"].sum()
deaths_1 = deaths.groupby(["area", pd.PeriodIndex(deaths.date, freq='Q')])["LT 1"].sum()

deaths_age = [deaths_65.to_frame() , deaths_45_64.to_frame(), deaths_25_44.to_frame(), deaths_1_24.to_frame(), deaths_1.to_frame()]
deaths_age_all = reduce(lambda left,right: pd.merge(left,right,on=['area', 'date']), deaths_age)

deaths_age_all = deaths_age_all.unstack().rename(columns = {
            "2016Q1" : "2016Q1",
            "2016Q2" : "2016Q2",
            "2016Q3" : "2016Q3",
        })

deaths_age_all.plot(kind='line')
plt.xlabel('area')
plt.ylabel('deaths')
plt.tight_layout(pad=0., w_pad=-16.5, h_pad=0.0)
plt.figure()

#Q2

events = pd.read_csv("timeseries_events.csv")
users  = pd.read_csv("timeseries_users.csv")
events = events.drop_duplicates() #many duplocates! idk if it was intentionally (to have same event for a user) or not I removed them, simply comment
users  = users.drop_duplicates()

#P1
df_events_users = pd.merge(events, users, how ='left', on=['user_id']) 
df_events_users.dropna(inplace=True)
df_events_users = df_events_users[(df_events_users["age"] > 30) & (df_events_users["gender"] == 'm')].reset_index()

#number of events for each age
df_events_count_age=df_events_users.copy()
df_events_count_age.groupby('age')['event_date'].count().plot.bar()
plt.figure()

#number of users for each event
df_users_count_event=df_events_users.copy()
df_users_count_event.groupby('event_date')['user_id'].count().plot.bar()
plt.figure()



#number of users for each bin-event (a user may have been in multiple events in this bin)
##temp
df_users_count_event['users_count_event'] = df_users_count_event.groupby('event_date')['user_id'].transform('count')
df_users_count_event = df_users_count_event[['event_date','users_count_event']]
df_users_count_event = df_users_count_event.drop_duplicates()
##temp
bins_dt = pd.date_range('2014-01-01', freq='1M', periods=20) #bins
bins_str = bins_dt.astype(str).values
labels = ['({}, {}]'.format(bins_str[i-1], bins_str[i]) for i in range(1, len(bins_str))]
df_users_count_event['event_date'] = df_users_count_event['event_date'].astype('datetime64[ns]')
df_users_count_event['event_date_range'] = pd.cut(df_users_count_event.event_date.astype(np.int64)//10**9,bins=bins_dt.astype(np.int64)//10**9,labels=labels)
df_users_count_event['event_date_range_count'] = df_users_count_event.groupby('event_date_range')['users_count_event'].transform('sum') # Adds new column for count of events
df_users_count_event = df_users_count_event[['event_date_range','event_date_range_count']]
df_users_count_event = df_users_count_event.drop_duplicates()
plt.bar(x=df_users_count_event['event_date_range'], height=df_users_count_event['event_date_range_count'])
tick_labels = [labels[i][3:8] for i in range(0, len(labels))]
plt.xticks(df_users_count_event['event_date_range'], tick_labels, rotation='vertical')
plt.tight_layout()
plt.xlabel('event_date_range')
plt.ylabel('event_date_range_count')
plt.figure()





###2
df_events_users_interevent_intervals=df_events_users.copy()
df_events_users_interevent_intervals['event_date_casted'] = df_events_users_interevent_intervals['event_date'].astype('datetime64[ns]')
df_events_users_interevent_intervals=df_events_users_interevent_intervals.sort_values(['user_id','event_date_casted'])
df_events_users_interevent_intervals_o = df_events_users_interevent_intervals[['user_id','event_date']] #needed for numpy and pandas cast issue
df_events_users_interevent_intervals = df_events_users_interevent_intervals[['user_id','event_date_casted']]

df_events_users_interevent_intervals_diff=df_events_users_interevent_intervals.diff()
df_events_users_interevent_intervals_diff.rename(columns = {'user_id':'user_id_diff'}, inplace = True)
df_events_users_interevent_intervals_diff.rename(columns = {'event_date_casted':'inter_events'}, inplace = True)
df_events_users_interevent_intervals = pd.concat([df_events_users_interevent_intervals_o,df_events_users_interevent_intervals_diff], axis=1)
df_events_users_interevent_intervals.dropna(inplace=True)
df_events_users_interevent_intervals=df_events_users_interevent_intervals[df_events_users_interevent_intervals.user_id_diff==0.0]


#http://en.citizendium.org/wiki/Interspike_interval_histogram
#http://www.tqmp.org/RegularArticles/vol10-1/p068/p068.pdf
#average of inter-event duration for a user (all events)


#average of inter-event duration for each event (start time)
df_avg_interevent_intervals_event = df_events_users_interevent_intervals.copy()
df_avg_interevent_intervals_event['inter_events'] = (df_avg_interevent_intervals_event['inter_events']).dt.days

df_avg_interevent_intervals_event.groupby('event_date')['inter_events'].mean().plot.bar()
plt.figure()




#average of inter-event duration for each bin-event (start time)
#temp
df_avg_interevent_intervals_event['inter_events_avg'] = df_avg_interevent_intervals_event.groupby('event_date')['inter_events'].transform(np.mean)
df_avg_interevent_intervals_event = df_avg_interevent_intervals_event[['event_date','inter_events_avg']]
df_avg_interevent_intervals_event.drop_duplicates()
#temp
df_avg_interevent_intervals_event['event_date'] = df_avg_interevent_intervals_event['event_date'].astype('datetime64[ns]')
df_avg_interevent_intervals_event['event_date_range'] = pd.cut(df_avg_interevent_intervals_event.event_date.astype(np.int64)//10**9,bins=bins_dt.astype(np.int64)//10**9,labels=labels)
df_avg_interevent_intervals_event['event_date_range_inter_events_avg'] = df_avg_interevent_intervals_event.groupby('event_date_range')['inter_events_avg'].transform(np.mean) # Adds new column for count of events
df_avg_interevent_intervals_event = df_avg_interevent_intervals_event[['event_date_range','event_date_range_inter_events_avg']]
df_avg_interevent_intervals_event = df_avg_interevent_intervals_event.drop_duplicates()
plt.bar(x=df_avg_interevent_intervals_event['event_date_range'], height=df_avg_interevent_intervals_event['event_date_range_inter_events_avg'])
tick_labels = [labels[i][3:8] for i in range(0, len(labels))]
plt.xticks(df_avg_interevent_intervals_event['event_date_range'], tick_labels, rotation='vertical')
plt.tight_layout()
plt.xlabel('event_date_range')
plt.ylabel('event_date_range_inter_events_avg')


plt.show()

exit()

