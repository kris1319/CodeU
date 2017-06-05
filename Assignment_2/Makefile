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

tree_ut.o: tree_ut.cpp tree.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c tree_ut.cpp

unittest: gtest_main.a tree_ut.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o unittest

clean:
	rm -rf *.o
	rm -rf *.a
