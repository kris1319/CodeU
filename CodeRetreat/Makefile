GTEST_DIR = contrib/googletest/googletest
GTEST_SRCS = $(GTEST_DIR)/src/*.cc
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
				$(GTEST_DIR)/include/gtest/internal/*.h

CPPFLAGS += -isystem $(GTEST_DIR)/include
CXXFLAGS += -g -Wall -Wextra --std=c++11

gtest-all.o : $(GTEST_SRCS)
	$(CXX) $(CPPFLAGS) -I $(GTEST_DIR) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS)
	$(CXX) $(CPPFLAGS) -I $(GTEST_DIR) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest_main.cc

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

game_of_life.o : game_of_life.cpp game_of_life.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c game_of_life.cpp

game_of_life_ut.o : game_of_life_ut.cpp game_of_life.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c game_of_life_ut.cpp

unittest : game_of_life.o game_of_life_ut.o gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@

clean :
	rm -rf *.o
	rm -rf *.a
