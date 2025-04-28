# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -g

# Output executable
TARGET = BankingSystem

# Source and object files
SRCS = main.cpp Customers.cpp BankAccount.cpp CreditCard.cpp Services.cpp Card.cpp
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
