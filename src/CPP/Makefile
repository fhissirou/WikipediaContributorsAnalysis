.DEFAULT_GOAL := all

# location of the Python header files
PYTHON_VERSION = 2.7
PYTHON_INCLUDE = /usr/include/python$(PYTHON_VERSION)

# location of the Boost Python include files and library
BOOST_INC = /usr/include
BOOST_LIB = /usr/lib

TARGET1 = fonction
TARGET2= som
TARGET3= load

#CFLAGS = --std=c++14

$(TARGET1).so: $(TARGET1).o
	g++ -shared -Wl,--export-dynamic $(TARGET1).o $(TARGET2).o $(TARGET3).o -L$(BOOST_LIB) -l:libboost_python-py$(subst .,,$(PYTHON_VERSION)).so -L/usr/lib/python$(PYTHON_VERSION)/config -lpython$(PYTHON_VERSION) -o $(TARGET1).so

$(TARGET1).o: $(TARGET1).cpp 
	g++ -I$(PYTHON_INCLUDE) -I$(BOOST_INC) -fPIC -c $(TARGET1).cpp

$(TARGET2).o: $(TARGET2).cpp
	g++ -I$(PYTHON_INCLUDE) -I$(BOOST_INC) -fPIC -c $(TARGET2).cpp

$(TARGET3).o: $(TARGET3).cpp
	g++ -I$(PYTHON_INCLUDE) -I$(BOOST_INC) -fPIC -c $(TARGET3).cpp

all: $(TARGET1).o $(TARGET2).o $(TARGET3).o $(TARGET1).so

clean:
	-rm *.o
	-rm $(TARGET1).so