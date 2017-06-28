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

disjoint_set.o : disjoint_set.cpp disjoint_set.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c disjoint_set.cpp

disjoint_set_ut.o : disjoint_set_ut.cpp disjoint_set.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c disjoint_set_ut.cpp

islands.o : islands.cpp islands.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c islands.cpp

islands_ut.o : islands_ut.cpp islands.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c islands_ut.cpp

unittest : disjoint_set.o disjoint_set_ut.o islands.o islands_ut.o gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@

clean :
	rm -rf *.o
	rm -rf *.a
