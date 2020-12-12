from matplotlib import pyplot as plt

read = open("LogTime.txt", "r")
readSubs = open("Subject Names.txt", "r")
subj = []
time_totals = []

subj = readSubs.readlines()

for line in read.readlines():
    time_totals.append(float(line) / 60)


if(len(time_totals) < len(subj)):
    difference = len(subj) - len(time_totals)
    for i in range(difference):
        time_totals.append(0)



plt.bar(subj, time_totals, label = "Total hours") 

plt.title("Time Tracker")
plt.xlabel("Activities")
plt.ylabel("Hours")

plt.legend()

plt.show()

