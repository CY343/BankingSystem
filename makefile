# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -g

# Output executable
TARGET = BankingSystem

# Source files
SRCS = main.cpp Customers.cpp BankAccount.cpp CreditCard.cpp DebitCard.cpp Services.cpp Card.cpp Transaction.cpp SavingAccount.cpp CheckingAccount.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Libraries
LIBS = -lmysqlcppconn

# Default target
all: $(TARGET)

# Linking
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

# Compilation
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target
clean:
	rm -f $(OBJS) $(TARGET)
