# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -O2 -g
CXXFLAGS += -I/usr/include/boost -I/usr/include/openssl

# Output executable
TARGET = BankingSystem

# Source files
SRCS = main.cpp Customers.cpp BankAccount.cpp CreditCard.cpp DebitCard.cpp \
       Services.cpp Card.cpp Transaction.cpp SavingAccount.cpp CheckingAccount.cpp \
       SecurityHelper.cpp CardGenerator.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Library paths and linking
LDFLAGS = -L/usr/lib/x86_64-linux-gnu -L/usr/local/lib
LIBS = -lcrypto -lssl -lmysqlcppconn -lboost_system -lboost_filesystem -pthread

# Security hardening flags
HARDEN_FLAGS = -D_FORTIFY_SOURCE=2 -fstack-protector-strong -Wformat -Werror=format-security

# Default target
all: $(TARGET)

# Linking
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(HARDEN_FLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

# Compilation
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(HARDEN_FLAGS) -c $< -o $@

# Clean
clean:
	rm -f $(OBJS) $(TARGET)
	find . -name '*.gc*' -delete

.PHONY: all clean