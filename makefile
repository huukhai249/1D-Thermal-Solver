# Makefile
# init petsc inviroment and precondition
petsc.pc := $(PETSC_DIR)/$(PETSC_ARCH)/lib/pkgconfig/petsc.pc
PACKAGES := $(petsc.pc)
OBJ_DIR = obj
SOURCE_DIR = src
SOURCE_FILES = main.cpp\
		parameters.cpp\
		solveM.cpp\
		linearSolving.c
# Object files
SOURCE_OBJ = main.o \
		$(OBJ_DIR)/linearSolving.o \
		$(OBJ_DIR)/parameters.o \
		$(OBJ_DIR)/solveM.o
# Debug
# CFLAGS_OTHER := $(shell pkg-config --cflags-only-other $(PACKAGES))
# CFLAGS := $(shell pkg-config --variable=cflags_extra $(PACKAGES)) $(CFLAGS_OTHER)
# CXXFLAGS := $(shell pkg-config --variable=cxxflags_extra $(PACKAGES)) $(CFLAGS_OTHER)
# 3.1:
CFLAGS = $(PETSC_INCLUDE) -O2
# 3.2:
CFLAGS = $(PETSC_CC_INCLUDES) -O2
##$(CLINKER)
CC = mpicc
# CC := $(shell pkg-config --variable=ccompiler $(PACKAGES))
# CXX := $(shell pkg-config --variable=cxxcompiler $(PACKAGES))
# FC := $(shell pkg-config --variable=fcompiler $(PACKAGES))
# FFLAGS := $(shell pkg-config --variable=fflags_extra $(PACKAGES))
# LDFLAGS := $(shell pkg-config --libs-only-L --libs-only-other $(PACKAGES))
# LDFLAGS += $(patsubst -L%, $(shell pkg-config --variable=ldflag_rpath $(PACKAGES))%, $(shell pkg-config --libs-only-L $(PACKAGES)))
LDLIBS := $(shell pkg-config --libs-only-l $(PACKAGES)) -lm
# print compiler is used
# the file c.cxx needs to link with a C++ standard library -lstdc++
PETSC_DIR =/home/khai/petsc
PETSC_ARCH = arch-linux-c-debug
MALLOC_CHECK_ = 0
include ${PETSC_DIR}/lib/petsc/conf/variables
include ${PETSC_DIR}/lib/petsc/conf/rules
# Executable file
EXEC=main
# file path 
VPATH = src
# Cpp flag
CPPFLAGS = -I src
#echo
main: $(SOURCE_OBJ) chkopts

	echo "     ********************************************************************"
	echo "     *     |||   ///         /////////                    //            *"
	echo "     *     |||  ///         //                           //             *"
	echo "     *     ||| ///         //                           //              *"
	echo "     *     ||////         //         /////////  /////////  /////////    *"
	echo "     *     ||\\\\   ==   //         //     //  //     //  //     //     *"
	echo "     *     ||| \\\      //         //     //  //     //  /////////      *"
	echo "     *     |||  \\\    //         //     //  //     //  //              *"
	echo "     *     |||   \\\  /////////  /////////  /////////  /////////        *"
	echo "     *                                                                  *"
	echo "     *       Self-developmemt CFD code using PETSC Framkwork            *"
	echo "     *         (Khai H. Nguyen, HUST, Oct 29 2023)                      *"
	echo "     *                                                                  *"
	echo "     ********************************************************************"
	-$(CC) -o main $(SOURCE_OBJ) ${LDLIBS}
	${RM} main.o
# Build all object files
#  main.o \
# 		$(OBJ_DIR)/linearSolving.o \
# 		$(OBJ_DIR)/parameters.o \
# 		$(OBJ_DIR)/solveM.o
$(OBJ_DIR)/linearSolving.o: linearSolving.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $(OBJ_DIR)/linearSolving.o
$(OBJ_DIR)/parameters.o: parameters.cpp
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $(OBJ_DIR)/parameters.o
$(OBJ_DIR)/solveM.o: solveM.cpp
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $(OBJ_DIR)/solveM.o
# Build the executable file
# -$(CC) -o main $(SOURCE_OBJ) ${LDLIBS}
# $(RM) main.o
# Clean all object and executable files
rm: rm -f $(OBJ_DIR)/*.o
print: *.cpp
