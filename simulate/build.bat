::compile all simulate files
g++ -I"C:\Users\Ryan Berube\Documents\Quadruped\include" -fPIC -shared -o kinecore.dll "C:\Users\Ryan Berube\Documents\Quadruped\lib\*.cpp" simlink.cpp