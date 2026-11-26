CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra
TARGET = student_grade_sys
SRCS = main.cpp Human.cpp Student.cpp functions.cpp Calculation.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp Human.h Student.h functions.h Calculation.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all run clean