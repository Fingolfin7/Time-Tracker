from matplotlib import pyplot as plt

read = open("C:\\Users\\Kuda\\Documents\\Programming\\C++\\Time-subj tracker\\Time-subj tracker\\Saves.txt", "r")
subj = []
time_totals = []
lines = list(read.readlines())

for line in lines:
    partitions = str(line).partition(": ")
    print(partitions)
    subj.append(partitions[0])
    time_totals.append(float(partitions[2]) / 60)



plt.bar(subj, time_totals, label = "Total hours") 

plt.title("Time Subject Tracker")
plt.xlabel("Subjects")
plt.ylabel("Time (in hours)")

plt.legend()

plt.show()
