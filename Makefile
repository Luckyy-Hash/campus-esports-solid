CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

SRCS = main.cpp \
       src/EmailNotification.cpp \
       src/SMSNotification.cpp \
       src/SoloRegistration.cpp \
       src/SquadRegistration.cpp \
       src/RegistrationManager.cpp

OBJS = $(SRCS:.cpp=.o)
TARGET = campus_esports
UNIFIED_TARGET = campus_esports_unified

all: $(TARGET) $(UNIFIED_TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

$(UNIFIED_TARGET): campus_esports_unified.cpp
	$(CXX) $(CXXFLAGS) -o $(UNIFIED_TARGET) campus_esports_unified.cpp

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

run-demo: $(TARGET)
	./$(TARGET) --demo

clean:
	rm -f $(OBJS) $(TARGET) $(TARGET).exe $(UNIFIED_TARGET) $(UNIFIED_TARGET).exe
