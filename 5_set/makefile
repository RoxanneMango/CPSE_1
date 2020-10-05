CXX = g++
CATCH2 = ..\Catch2\single_include
CXXFLAGS = -g -Os -Wall -Wextra -std=gnu++17 
EXEC = test

.PHONY: src clean all

src:
	$(CXX) $(CXXFLAGS) -I$(CATCH2) -o $(EXEC) tests.c

exec:
	@$(EXEC)

clean: 
	@echo ("Initiating lemon pledge . . .");
	del *.o *.exe
	@echo ("I clean . . .");
	
all: src exec