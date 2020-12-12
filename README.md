# Time-Tracker
A simple time tracking program I made to track my study time using the <chrono> library

## Getting Started
Visual Studio 2019 is recommended,

Start by cloning the repository or downloading the zip file.

Once downloaded, open folder and run the `GenerateProject.bat` file, which will be inside the "Generate Project" folder. This will run the "premake5.lua" and create a Visual Studio 2019 solution.

Alternatively, you can enter this command on the command prompt within the folder -> `premake5.exe vs2019`
You can generate solutions for vs2019, vs2017, vs2010 etc.

## How to use it
Included is a .txt file called `Subject Names` this contains a list of all the activities you want to keep track of. Just add the activities you want to keep a track of to the file. Each activity should be on a new line. For example:

`Mathematics`

`Physics`

`Chemistry`

Once you compile and run the program you will be greated with the options to 1)create a New Session, 2) Show Totals, and 3) exit.
A bell sound (loaded from the `clock-chimes-daniel_simon.wav` file) will ring every 30 minutes.

Press any key during a new session to stop the counter and save the time total. 

Time totals are saved in a .txt file called `LogTime`

You can view a bar graph of your activities and the total hours for each by running the `Time-tracker_graphs` python file.

## Contribute to the project

Take a look, run the code, and contribute if you'd like!
