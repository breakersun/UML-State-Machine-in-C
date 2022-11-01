cd ../demo\simple_detection_loop
md build
cd build
del /s/q Unix
md Unix
cd Unix
cmake -G "Unix Makefiles" ../..
cmake --build .
pause
