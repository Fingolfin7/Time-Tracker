from matplotlib import pyplot as plt


def showBarGraphs(subj_names=[], subj_totals=[]):
    plt.bar(subj_names, subj_totals, label="Total hours")

    plt.title("Time Subject Tracker")
    plt.xlabel("Subjects")
    plt.ylabel("Time (in hours)")

    plt.legend()

    plt.show()


read = open("Saves.txt", "r")
lines = list(read.readlines())
read.close()

subj = []
time_totals = []


for line in lines:
    partitions = str(line).partition(": ")
    print(partitions)
    if float(partitions[2]) > 0:
        subj.append(partitions[0])
        time_totals.append(float(partitions[2]) / 60)


showBarGraphs(subj, time_totals)
