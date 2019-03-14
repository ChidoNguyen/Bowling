# Bowling
Bowling Score Tracker App

# Information
Bowling program is done in C++ on a Windows 10 x64, and Visual Studio 2017 Enterprise.

# To Run
-  Option 1: Download project files and load the solution into Visual Studio on a Windows machine then at the top Debug > Start Debugging ( F5 for shortcut). Follow on screen prompt to enter data into the program.
-  Option 2: On root github project page navigate to root/Bowling/Release and download "Bowling.exe" then run the executable on a Windows machine.

# Misc:
-  Coded under the assumption that all inputs by the user are within the valid constraints. i.e. [0-9, '/', 'X'] and format is as [@,@,@ / @ / @,@] where @ can be any of the valid characters
  -  All frames require at least 2 data points i.e. 0 if you guttered it 9,0 and not 9 except for strikes(1) and frame 10 (up to 3) 
-  bowling.cpp houses the main function along with commented out test functions. Uncomment to see console output of some basic test functions.
-  bowlinghelper.h : 3 main components of the program processInput => for processing user input and populating frames , process_Score => updates the score of each frame when new data becomes available, and printScore which prints the score as the game progresses
-  testbowling.h: has test functions which unit tests each of the bowlinghelper.h functions. 

