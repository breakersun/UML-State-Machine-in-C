cd ../demo\simple_state_machine
md build
cd build
del /s/q Unix
md Unix
cd Unix
cmake -G "Unix Makefiles" ../..
cmake --build .
pause
