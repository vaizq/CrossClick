CC = g++
CC_C = gcc

PROG= app.out
TEST_PROG = test.out

ODIR :=bin
SDIR :=src

SOURCES := $(wildcard $(SDIR)/*.cpp)
OBJ := $(patsubst $(SDIR)/%,%,$(SOURCES))
OBJ := $(patsubst %.cpp,%.o,$(OBJ))
OBJ := $(addprefix $(ODIR)/,$(OBJ))

LIBS := -lpthread -lX11
INCLUDES := 


CFLAGS := $(INCLUDES) $(LIBS) -g

$(PROG) : $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) 

# Build object files from sources
$(ODIR)/%.o : $(SDIR)/%.cpp
	$(CC) -c -o $@ $^ $(CFLAGS) 

$(ODIR)/%.o : $(SDIR)/%.c
	$(CC_C) -c -o $@ $^ $(CFLAGS) 

.PHONY: clean
clean:
	rm -f $(ODIR)/*.o $(ODIR)/*.out ./*.out

.PHONY: run
run:
	./$(PROG)
