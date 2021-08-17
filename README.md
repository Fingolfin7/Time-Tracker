# Time-Tracker
A simple time tracking program I made to track my study time using the `<chrono>` library

## Getting Started
Visual Studio 2019 is recommended,

Start by cloning the repository or downloading the zip file.

Once downloaded, open folder and run the `GenerateProject.bat` file, which will be inside the "Generate Project" folder. This will run the "premake5.lua" and create a Visual Studio 2019 solution.

Alternatively, you can enter this command on the command prompt within the folder -> `premake5.exe vs2019`
You can generate solutions for vs2019, vs2017, vs2010 etc.

## How to use it
Included is a .txt file called `Saves.txt` this contains a list of all the activities you want to keep track of. Just add the activities you want to keep a track of to the file. Each activity should be on a new line. For example:

`Chess: 0`

`Programming: 0`

`Chess Engine: 0`

### Home Screen

![image](https://user-images.githubusercontent.com/63872314/129780552-e20ffd57-cdeb-49ea-82d9-f7ae1c99cc09.png)

Once you compile and run the program you will be greated with the options to:

1. Create a New Session,

2. Show Totals,

3. Edit Subjects,

4. Change Settings and,

5. Exit.


A bell sound (loaded from the `clock-chimes-daniel_simon.wav` file) will ring every 30 minutes.

Press `Enter` during a new session to stop the counter and save the time total. 

Time totals are saved in the same `Saves.txt` file

### Totals Page

Shows a pie char or bar graph of your activities and the total hours from the "show totals" page:

![image](https://user-images.githubusercontent.com/63872314/129787418-0d0bb675-1605-4033-98fa-253287169c09.png)

#### Bar Graph

![Figure_1](https://user-images.githubusercontent.com/63872314/129788297-bd8c3d71-4c64-483c-bde3-773a94e760d6.png)

The chart is created with the `Bar Graph.py` python script

#### Pie Chart

![Figure_2](https://user-images.githubusercontent.com/63872314/129788326-1060b88a-7be4-4005-b88d-da1595ecd631.png)

The pie chart is created with the `Pie Chart.py` python script

## Contribute to the project

Take a look, run the code, and contribute if you'd like!
