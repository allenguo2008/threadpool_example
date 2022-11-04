# define the Cpp compiler to use
CXX = g++

# define any compile-time flags
CXXFLAGS	:= -std=c++11 -lpthread -Wall -Wextra -g

# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like:
LFLAGS =

# define output directory
OUTPUT	:= ../Bin

# define source directory
SRC		:= .

# define include directory
INCLUDE	:= ../include

# define lib directory
LIB		:= ../Bin

# 通过shell获取当前目录，然后通过nodir获取当前目录名
CUR_DIR_NAME := $(notdir $(shell pwd))
OBJ 	:= ../Obj/$(CUR_DIR_NAME)

MAIN	:= main
# 通过shell命令find找到当前目录中所有目录包括子目录
SOURCEDIRS	:= $(shell find $(SRC) -type d)
INCLUDEDIRS	:= $(shell find $(INCLUDE) -type d)
# 找到所有的.so动态库
LIBDIRS		:= $(shell find $(LIB) -name "*.so")
FIXPATH = $1
RM = rm -f
MD	:= mkdir -p

# define any directories containing header files other than /usr/include
INCLUDES	:= $(patsubst %,-I%, $(INCLUDEDIRS:%/=%))

# 通过patsubst函数获取所有目录中的所有.cpp文件并赋给SOURCES
SOURCES		:= $(wildcard $(patsubst %, %/*.cpp, $(SOURCEDIRS)))

# 遍历存在的.cpp文件生成对应的.o文件
OBJECTS		:= $(patsubst $(SRC)/%, $(OBJ)/%, $(SOURCES:.cpp=.o))

# define the C libs
LIBS		:= $(LIBDIRS)

#
# The following part of the makefile is generic; it can be used to 
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#
OUTPUTMAIN	:= $(call FIXPATH,$(OUTPUT)/$(MAIN))

# 在make解析规则之前展开执行
OBJ_DIR	:= $(dir $(OBJECTS))

# 顶级目标
all: $(OUTPUT) $(OBJ_DIR) $(MAIN)
	@echo Executing 'all' complete!

# 创建输出目录
$(OUTPUT):
	$(MD) $(OUTPUT)

# 多目标规则,自动遍历符合规则的所有目标目录
$(OBJ)/%:
	$(MD) $@

# 生成main
$(MAIN): $(OBJECTS) 
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(OUTPUTMAIN) $(OBJECTS) $(LFLAGS) $(LIBS)

# 利用静态模式规则，遍历所有的目标文件并调用相应的.cpp文件
$(OBJ)/%.o:$(SRC)/%.cpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) $< -o $@

# 伪目标,只能手动调用
.PHONY:clean
clean:
	find $(OBJ) -name "*.o" | xargs rm -rf
	rm -rf $(OUTPUTMAIN)

