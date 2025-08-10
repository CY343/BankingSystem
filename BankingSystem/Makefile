# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -O2 -g
CXXFLAGS += -I/usr/include/boost -I/usr/include/openssl

# Security hardening flags
HARDEN_FLAGS = -D_FORTIFY_SOURCE=2 -fstack-protector-strong -Wformat -Werror=format-security

# Output executables
MAIN_TARGET = BankingSystem
TEST_TARGET = BankingSystemTests

TEST_DIR = ../tests

# Source files
SRCS = Customers.cpp BankAccount.cpp CreditCard.cpp DebitCard.cpp \
       Services.cpp Card.cpp Transaction.cpp SavingAccount.cpp CheckingAccount.cpp \
       SecurityHelper.cpp CardGenerator.cpp

# Test source files  ✅  FIXED PATHS & ADDED YOUR FILE
TEST_SRCS = $(TEST_DIR)/BankAccount_test.cpp \
            $(TEST_DIR)/Customers_test.cpp \
    		$(TEST_DIR)/Card_test.cpp \
    		$(TEST_DIR)/test_checkingaccount.cpp \
			$(TEST_DIR)/CreditCard_test.cpp \
			$(TEST_DIR)/DebitCard_test.cpp \
			$(TEST_DIR)/SavingAccount_test.cpp \
			$(TEST_DIR)/Services_test.cpp \

# Object files
OBJS = $(SRCS:.cpp=.o)
TEST_OBJS = $(TEST_SRCS:.cpp=.o) $(filter-out main.o, $(OBJS))

# Library paths and linking
LDFLAGS = -L/usr/lib/x86_64-linux-gnu -L/usr/local/lib
LIBS = -lcrypto -lssl -lmysqlcppconn -lboost_system -lboost_filesystem -pthread
TEST_LIBS = $(LIBS) -lgtest -lgtest_main -lpthread

# Default target
all: $(MAIN_TARGET)

# Main application
$(MAIN_TARGET): main.o $(OBJS)
	$(CXX) $(CXXFLAGS) $(HARDEN_FLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

# Test executable
$(TEST_TARGET): $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) $(HARDEN_FLAGS) $(LDFLAGS) -o $@ $^ $(TEST_LIBS)

# Compilation
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(HARDEN_FLAGS) -c $< -o $@

# Test compilation ✅ FIXED TO MATCH NEW PATH
../tests/%.o: ../tests/%.cpp
	$(CXX) $(CXXFLAGS) $(HARDEN_FLAGS) -I. -I.. -c $< -o $@

# Test command
test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Clean
clean:
	rm -f $(OBJS) main.o $(TEST_OBJS) $(MAIN_TARGET) $(TEST_TARGET)
	find . -name '*.gc*' -delete

.PHONY: all clean test
