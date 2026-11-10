CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

SRCS = main.cpp \
       src/EmailNotification.cpp \
       src/SMSNotification.cpp \
       src/SoloRegistration.cpp \
       src/SquadRegistration.cpp \
       src/RegistrationManager.cpp

OBJS = $(SRCS:.cpp=.o)
TARGET = campus_esports.exe

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

