from matplotlib import pyplot as plt


def showPieChart(subj_names=[], subj_totals=[], colours=[]):
    if len(colours) > 0:
        plt.pie(subj_totals, labels=subj_names, autopct="%1.1f%%", colors=colours)
    else:
        plt.pie(subj_totals, labels=subj_names, autopct="%1.1f%%")

    plt.title("Subject Totals")
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


showPieChart(subj, time_totals)
