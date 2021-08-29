CC = g++
CC_C = gcc

PROG= app.out
TEST_PROG = test.out

ODIR := bin
SDIR := src
IDIR := include

SOURCES := $(wildcard $(SDIR)/*.cpp) 
IMGUI_SOURCES := $(wildcard $(SDIR)/imgui/*.cpp) 
OBJ := $(patsubst $(SDIR)/%,%,$(SOURCES))
OBJ += $(patsubst $(SDIR)/imgui/%,%,$(IMGUI_SOURCES))
OBJ := $(patsubst %.cpp,%.o,$(OBJ))
OBJ := $(addprefix $(ODIR)/,$(OBJ))


LIBS := -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lassimp -lpthread -lX11 

INCLUDES := -I$(IDIR) -I$(IDIR)/backends


CFLAGS := $(INCLUDES) $(LIBS) -g

$(PROG) : $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) 

# Build object files from sources
$(ODIR)/%.o : $(SDIR)/%.cpp
	$(CC) -c -o $@ $^ $(CFLAGS) 

$(ODIR)/%.o : $(SDIR)/%.c
	$(CC_C) -c -o $@ $^ $(CFLAGS) 

$(ODIR)/%.o : $(SDIR)/imgui/%.cpp
	$(CC) -c -o $@ $^ $(CFLAGS) 

$(ODIR)/%.o : $(SDIR)/imgui/%.c
	$(CC_C) -c -o $@ $^ $(CFLAGS) 


.PHONY: clean
clean:
	rm -f $(ODIR)/*.o $(ODIR)/*.out ./*.out

.PHONY: run
run:
	./$(PROG)
