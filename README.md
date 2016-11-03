# testdl

还未完成。。。与设想不符

gcc -shared -fPIC -o ./mylib/csapp.so ./tools/csapp.c -lpthread 
gcc -shared -fPIC -o ./mylib/mytools.so ./tools/mytools.c -lpthread 

gcc -shared -fPIC -o ./mylib/dynamicprint.so ./dynatest/dynamicprint.c 

gcc -o ./bin/myecho myecho.c ./mylib/*.so -ldl
