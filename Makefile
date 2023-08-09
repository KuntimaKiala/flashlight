

NVCC = nvcc
NVCC_FLAGS = -g -G -Xcompiler "-Wall -Wno-deprecated-declarations"
LDFLAGS= -lglut -lGL -lGLU -lGLEW
PROJECT=run
OBJ=-o
FILES=flashlight.cu interactions.cpp

$(PROJECT) : $(FILES)
	$(NVCC) $(NVCC_FLAGS) $(LDFLAGS) $(FILES) $(OBJ) $(PROJECT)

