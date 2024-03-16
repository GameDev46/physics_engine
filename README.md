<a href="https://github.com/GameDev46" title="Go to GitHub repo">
    <img src="https://img.shields.io/static/v1?label=GameDev46&message=|&color=Green&logo=github&style=for-the-badge&labelColor=1f1f22" alt="GameDev46 - grass_sim">
    <img src="https://img.shields.io/badge/Version-0.4.1-green?style=for-the-badge&labelColor=1f1f22&color=Green" alt="GameDev46 - CPP_Projects">
</a>


![Static Badge](https://img.shields.io/badge/--1f1f22?style=for-the-badge&logo=Cplusplus&logoColor=6060ef)
    
<a href="https://github.com/GameDev46/physics_engine/stargazers">
    <img src="https://img.shields.io/github/stars/GameDev46/physics_engine?style=for-the-badge&labelColor=1f1f22" alt="stars - physics_engine">
</a>
<a href="https://github.com/GameDev46/physics_engine/forks">
    <img src="https://img.shields.io/github/forks/GameDev46/physics_engine?style=for-the-badge&labelColor=1f1f22" alt="forks - physics_engine">
</a>
<a href="https://github.com/GameDev46/physics_engine/issues">
    <img src="https://img.shields.io/github/issues/GameDev46/physics_engine?style=for-the-badge&labelColor=1f1f22&color=blue"/>
 </a>

<br>
<br>

<p align="left">
<a href="https://twitter.com/gamedev46" target="blank"><img align="center" src="https://raw.githubusercontent.com/rahuldkjain/github-profile-readme-generator/master/src/images/icons/Social/twitter.svg" alt="gamedev46" height="30" width="40" /></a>
<a href="https://instagram.com/oliver_pearce47" target="blank"><img align="center" src="https://raw.githubusercontent.com/rahuldkjain/github-profile-readme-generator/master/src/images/icons/Social/instagram.svg" alt="oliver_pearce47" height="30" width="40" /></a>
<a href="https://www.youtube.com/c/gamedev46" target="blank"><img align="center" src="https://raw.githubusercontent.com/rahuldkjain/github-profile-readme-generator/master/src/images/icons/Social/youtube.svg" alt="gamedev46" height="30" width="40" /></a>
</p>

# physics_engine

A 2D physics engine programmed in C++ that makes use of verlet integration to solve differential equations

# Usage

You may use any version of the physics engine you would like, but I reccomend using the [newest version](/Physics%20Engine%20V0.4.1) as it will be less buggy and probably have mre features than the versions before it!

Instructions are included within the application and can be toggle on and off with the H key:

**P Key** - Pause / Play the simulation
**Left Click and Hold** - Pan camera / Move node
**Right Click on Node and then Right Click on another Node** - Creates a spring joint between the 2 nodes
**Right Click twice on Node** - Switches the node between being frozen in place and being able to move
**Middle Mouse Button / F Key over node** - View any connected springs properties
**Front Side Mouse Button / Q Key** - Create a new node
**Back Side Mouse Button / E Key over node** - Destroy the node

If you wish to edit the program or just change the UI or colours to your liking, open the [main C++ file](/Physics%20Engine%20V0.4.1/main.cpp) using an appropriate code editing software and then when you are finished editing the code simply run the command...

<pre>g++ main.cpp -o physicsEngineModded.exe -O1 -Wall -std=c++11 -Wno-missing-braces -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm</pre>

...to compile your new code into an exe file. You will however need to install the g++ compiler if you haven't already done so, but a useful tutorial can be found on the [official VS code website](https://code.visualstudio.com/docs/cpp/config-mingw) (note that this is for both C and C++). Once this is done simply run the physicsEngineModded.exe file and watch as your changes come to life in your new version!

# Screenshots

<p>
  <img src="https://github.com/GameDev46/physics_engine/assets/76485006/d313adc0-f2b4-42ff-a223-2bc998def855" height="300">
  &nbsp;
  <img src="https://github.com/GameDev46/physics_engine/assets/76485006/a3265fe3-a8b2-4650-a899-66294f30a7e4" height="300">
</p>

# Update Log

[**V0.3.1**](/Physics%20Engine%20V0.3.1)

- Initial release

[**V0.3.2**](/Physics%20Engine%20V0.3.2)

- Bug fixes
- UI changes and fixes
- More customisation options (spring constant)

[**V0.4.1**](/Physics%20Engine%20V0.4.1)

- Bug fixes (again)
- Some more UI changes + fixes
- Natural length of springs can now be edited
- More stable simulation
