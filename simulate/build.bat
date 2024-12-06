::compile all simulate files
g++ -I"C:\Users\Ryan Berube\Documents\Quadruped\include" -fPIC -shared -m64 -o kinecore.dll "C:\Users\Ryan Berube\Documents\Quadruped\lib\*.cpp" simlink.cpp