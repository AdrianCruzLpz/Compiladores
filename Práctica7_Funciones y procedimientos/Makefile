Gram=y.tab.c y.tab.h

all: $(Gram) 
	@gcc -o pr7 y.tab.c symbol.c init.c math.c vector_cal.c code.c -lm
	@echo Compiled

$(Gram): hoc6.y
	@yacc -d hoc6.y

clean:
	@rm -f  *.tab.* *.yy.* calc
	@echo Clean
