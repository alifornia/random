
"""
df = pd.read_csv("timeseries_events.csv") ## 
df1 = pd.read_csv("timeseries_users.csv") ##
df.head()
event_date = df['event_date'].astype('datetime64[ns]')
s1 = pd.merge(df, df1, how ='left', on=['user_id'])  ## merge casedf and demodf 
s2 = s1[['user_id', 'event_date', 'age', 'gender']].groupby(['user_id', 'event_date']).agg(['mean', 'count'])
counts = s1.groupby('user_id').size()
counts
d1f = counts.to_frame().reset_index()
d1f.head()
d1f = d1f.rename(columns={'user_id': 'USER-ID', 0: 'TOTAL-EVENTS'})
d1f.head() 
d2f = pd.read_csv("timeseries_users.csv") 
# df2.head()
d2f = d2f.rename(columns={'age': 'AGE', 'gender': 'GENDER', 'user_id': 'USER-ID'})
d2f.head()
d1 = pd.merge(d1f, d2f, how ='left', on=['USER-ID'])  
d1.head()
d2m = d1[(d1["AGE"] > 30) & (d1["GENDER"] == 'm')]
print(d2m)
x = d2m['TOTAL-EVENTS'].groupby([0])

num_bins = 30
n, bins, patches = plt.hist(x, num_bins, facecolor='blue', alpha=0.5)
plt.show()

data_users = pd.read_csv("timeseries_users.csv")
data_events = pd.read_csv("timeseries_events.csv")
print(" The user data set has", len(data_users), "rows") 
print(" The event data set has", len(data_events), "rows")

data_events["event_date"] = data_events["event_date"].astype("datetime64")

print(data_users.head())
print(data_events.head())

age_threshold = 30
gender = "m"


fig, ax = plt.subplots()
plt.show()

"""
deaths = pd.read_csv("deaths.csv")
#deaths=deaths.drop(['MMWR YEAR'], axis=1)
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


#regions Total (seasons)
regions = deaths.loc[0:8, "area"].tolist()
deaths = deaths[deaths["area"].isin(regions)]

deaths_season = deaths.copy()
deaths_season = deaths_season[(deaths_season['area'].isin(regions))]
deaths_season = deaths_season[['area', 'week', 'all']]


#cond = np.where(deaths_season['week'] <= 10, 'SEASON1' , 'SEASON2')
#deaths_season1['SEASON1'] = deaths_season[deaths_season['week'] <= 10].groupby('area')['all'].transform(sum)


for i in range(1,4):
    deaths_season['SEASON'+str(i)] = deaths_season[(deaths_season['week']>13*(i-1)) & (deaths_season['week']<=13*i)].groupby('area')['all'].transform(sum)

deaths["date"] = pd.to_datetime(deaths.year.astype(str), format='%Y') + \
                     pd.to_timedelta((deaths.week-1).mul(7).astype(str) + ' days')

deaths_Q = deaths.groupby(["area", pd.PeriodIndex(deaths.date, freq='Q')])["all"].sum()
#deaths_Q.plot(kind='bar', stacked=True, rot=90, edgecolor='black')

deaths_Q = deaths_Q.unstack().rename(columns = {
            "2016Q1" : "2016Q1",
            "2016Q2" : "2016Q2",
            "2016Q3" : "2016Q3",
        })

deaths_Q.plot(kind='bar', stacked=True, rot=90, edgecolor='black')
plt.show()
exit()


deaths_season = deaths_season[['area', 'SEASON1', 'SEASON2', 'SEASON3']]
deaths_season=deaths_season.drop_duplicates()
deaths_season = deaths_season.fillna(0)
deaths_season = deaths_season.groupby(['area'])[['SEASON1','SEASON2','SEASON3']].sum()

##plt.bar(x=deaths_season['area'], stacked=True height=deaths_season['SEASON1'])
deaths_season.plot(kind='bar', stacked=True, rot=90, edgecolor='black')
plt.xlabel('area')
plt.ylabel('deaths')
plt.tight_layout(pad=0., w_pad=-16.5, h_pad=0.0)


##my_colors = [(x/10.0, x/20.0, 0.75) for x in range(len(deaths_season))] # <-- Quick gradient example along the Red/Green dimensions.
##from matplotlib import cm
##my_colors2 = cm.inferno_r(np.linspace(.4,.8, 30))

deaths_season.T.plot(kind='bar', stacked=True, rot=0, edgecolor='black')
plt.xlabel('area')
plt.ylabel('deaths')

##Age wise in Big Areas Total (seasons)
##df for different age buckets
deaths_65 = deaths.groupby(["area", pd.PeriodIndex(deaths.date, freq='Q')])["65+"].sum().reset_index()
print(deaths_65)
exit()

deaths_45_64 = deaths.groupby(["area", pd.PeriodIndex(deaths.date, freq='Q')])["45-64"].sum()
deaths_25_44 = deaths.groupby(["area", pd.PeriodIndex(deaths.date, freq='Q')])["25-44"].sum()
deaths_1_24 = deaths.groupby(["area", pd.PeriodIndex(deaths.date, freq='Q')])["1-24"].sum()
deaths_1 = deaths.groupby(["area", pd.PeriodIndex(deaths.date, freq='Q')])["LT 1"].sum()

from functools import reduce
deaths_age = [deaths_65.to_frame() , deaths_45_64.to_frame()]
df_final = reduce(lambda left,right: pd.merge(left,right,on=['area', 'date']), deaths_age)

#deaths_age = pd.merge(deaths_65.to_frame(), deaths_45_64.to_frame(), how='left', on=['area', 'date'])
print(df_final)
exit()
deaths_age2 = deaths_age[['area']].drop_duplicates()
print(deaths_age2)
deaths_age = deaths_age[['area', 'week', 'all']]
deaths_age2







deaths_season['SEASON'] = deaths_season.groupby('area')['all'].transform(sum)
print(deaths_season.head())
exit()
df_events_users = df_events_users[(df_events_users["age"] > 30) & (df_events_users["gender"] == 'm')].reset_index()

print(deaths.head())
exit()

for area in big_areas:
    deaths[area] = deaths[(deaths['area']==area)]
    print(area)
    plt.bar(x=deaths_area['week'], height=deaths_area['all'])


df_events_count_age.groupby('age')['event_date'].transform('count') 

fig = plt.figure(figsize=(12,8))
for col in deaths.columns[deaths.columns.area.isin(big_areas) & deaths.columns.week=='1' & ~deaths.columns.isin(['area']) & ~deaths.columns.isin(['week']) & ~deaths.columns.isin(['all'])]:
    plt.bar(deaths.area, deaths[col], bottom=cumval, label=col)
    cumval = cumval+deaths[col]
plt.show()
exit()


for col in deaths.columns[deaths.columns.week.isin(big_areas)]:
    print(col)
exit()

print(deaths.head())
cumval=0
fig = plt.figure(figsize=(12,8))
for col in deaths.columns[deaths.columns.area.isin(big_areas) & deaths.columns.week=='1' & ~deaths.columns.isin(['area']) & ~deaths.columns.isin(['week']) & ~deaths.columns.isin(['all'])]:
    plt.bar(deaths.area, deaths[col], bottom=cumval, label=col)
    cumval = cumval+deaths[col]
plt.show()

exit()
#deaths_ne[['abuse','nff']].plot(kind='bar', stacked=True)

for area in big_areas:
    deaths_area = deaths[(deaths['area']==area)]
    print(area)
    plt.bar(x=deaths_area['week'], height=deaths_area['all'])
plt.xlabel('week')
plt.ylabel('all')
plt.show()



exit()

#Citys Total

#Big Area Week

#Weeks

#  

exit()


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
df_events_count_age['events_count_age'] = df_events_count_age.groupby('age')['event_date'].transform('count') 
df_events_count_age = df_events_count_age[['age','events_count_age']]
df_events_count_age = df_events_count_age.drop_duplicates()
plt.bar(x=df_events_count_age['age'], height=df_events_count_age['events_count_age'])
plt.xlabel('age')
plt.ylabel('events_count_age')
plt.figure()


#number of users for each event
df_users_count_event=df_events_users.copy()
df_users_count_event['users_count_event'] = df_users_count_event.groupby('event_date')['user_id'].transform('count')
df_users_count_event = df_users_count_event[['event_date','users_count_event']]
df_users_count_event = df_users_count_event.drop_duplicates()
plt.bar(x=df_users_count_event['event_date'], height=df_users_count_event['users_count_event'])
plt.xlabel('event_date')
plt.ylabel('users_count_event')
plt.figure()

#number of users for each bin-event (a user may have been in multiple events in this bin)
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
df_avg_interevent_intervals_event['inter_events_avg'] = df_avg_interevent_intervals_event.groupby('event_date')['inter_events'].transform(np.mean)
df_avg_interevent_intervals_event = df_avg_interevent_intervals_event[['event_date','inter_events_avg']]
df_avg_interevent_intervals_event.drop_duplicates()
plt.bar(x=df_avg_interevent_intervals_event['event_date'], height=df_avg_interevent_intervals_event['inter_events_avg'])
plt.xlabel('event_date')
plt.ylabel('inter_events_avg')
plt.figure()


#average of inter-event duration for each bin-event (start time)
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


#s3.hist(column=['user_count'], bins=8, align= 'mid', rwidth=0.8, range = (0,100))





#s3.hist(column=['user_count'], bins=8, align= 'mid', rwidth=0.8, range = (0,100))

#s3.plot(x='user_id',y='event_count',kind='hist')
#plt.show()
#print(s3)

#print(s2)
# Plot histogram using pd.plot()

#s2.plot(x='user_id',y='event_count',kind='hist')
#plt.show()






df_events_count_age['events_count_age'] = df_events_count_age.groupby('age')['event_date'].transform('count') 
df_events_count_age = df_events_count_age[['age','events_count_age']]
df_events_count_age = df_events_count_age.drop_duplicates()
plt.bar(x=df_events_count_age['age'], height=df_events_count_age['events_count_age'])
plt.xlabel('age')
plt.ylabel('events_count_age')