bc : bc.o ../lib/bclib.o ../lib/ballistics.o
	gcc -o bc bc.o ../lib/bclib.o ../lib/ballistics.o -lm
     
bc.o : bc.c
	gcc -c bc.c
             
bclib.o : ../lib/bclib.c ../include/bclib.h
	gcc -c ../lib/bclib.c
	
ballistics.o : ../lib/ballistics.c ../include/ballistics.h
	gcc -c ../lib/ballistics.c
	
clean :
	@find ../ -name "*.o" -exec rm -rf {} \;
	@rm bc

