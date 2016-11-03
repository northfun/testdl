
cstestall: so cstest

so:
	gcc -shared -fPIC -o ./mylib/csapp.so ./tools/csapp.c -lpthread
	gcc -shared -fPIC -o ./mylib/mytools.so ./tools/mytools.c -lpthread 

cstest:
	gcc -o ./c_s_test/c ./c_s_test/c.c ./mylib/*.so -ldl
	gcc -o ./c_s_test/s ./c_s_test/s.c ./mylib/*.so -ldl

cleancstest:
	rm ./c_s_test/c ./c_s_test/s

dynatestso:
	gcc -shared -fPIC -o ./mylib/dynamicprint.so ./dynatest/dynamicprint.c

dynatest:
	gcc -o ./dynatest/changedlopen ./dynatest/changeDlopen.c ./mylib/*.so -lpthread -ldl

cleandynatest:
	rm ./dynatest/changedlopen
