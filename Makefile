CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -MMD -MP

TARGET = sistema_treino
SRCS = main.cpp Sistema.cpp Exercicio.cpp Cardio.cpp Forca.cpp Ficha.cpp Historico.cpp
OBJS = $(SRCS:.cpp=.o)
DEPS = $(OBJS:.o=.d)

TEST_TARGET = tests
TEST_SRCS = tests.cpp Sistema.cpp Exercicio.cpp Cardio.cpp Forca.cpp Ficha.cpp Historico.cpp
TEST_OBJS = $(TEST_SRCS:.cpp=.o)
TEST_DEPS = $(TEST_OBJS:.o=.d)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

test: $(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_OBJS)

-include $(DEPS)
-include $(TEST_DEPS)

clean:
	rm -f $(OBJS) $(DEPS) $(TARGET) $(TEST_OBJS) $(TEST_DEPS) $(TEST_TARGET)

run: $(TARGET)
	./$(TARGET)

run_tests: $(TEST_TARGET)
	./$(TEST_TARGET)
