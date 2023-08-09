

NVCC = nvcc
NVCC_FLAGS = -g -G -Xcompiler "-Wall -Wno-deprecated-declarations"
LDFLAGS= -lglut -lGL 
PROJECT=flashlight
OBJ=-o
FILES=main.cpp FlashlightApp.cpp kernel.cu
LAUNCH=&& ./flashlight
$(PROJECT) : $(FILES)
	$(NVCC) $(NVCC_FLAGS) $(LDFLAGS) $(FILES) $(OBJ) $(PROJECT) $(LAUNCH)

