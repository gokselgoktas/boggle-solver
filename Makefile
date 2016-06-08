CXXFLAGS += -std=c++11 -Wall -Iinclude -g0 -O3 -DNDEBUG

LIBRARY_SOURCES = api.cpp board.cpp depth-first-search.cpp \
	dictionary-originated-search.cpp optimized-search.cpp dictionary.cpp \
	trie-node.cpp trie.cpp

COMMON_SOURCES = $(addprefix ./src/,$(LIBRARY_SOURCES))

SANDBOX_SOURCES = $(COMMON_SOURCES) ./src/main.cpp

API_DEMO_SOURCES = $(COMMON_SOURCES) ./examples/api-demo.cpp
DEMO_SOURCES = $(COMMON_SOURCES) ./examples/demo.cpp

TASK_SOURCES = $(COMMON_SOURCES) ./test/task.cpp
STRESS_SOURCES = $(COMMON_SOURCES) ./test/stress.cpp
WORST_CASE_SOURCES = $(COMMON_SOURCES) ./test/worst-case.cpp
REENTRANCY_SOURCES = $(COMMON_SOURCES) ./test/reentrancy.cpp
Q_SOURCES = $(COMMON_SOURCES) ./test/q.cpp

TEST_SOURCES = $(TASK_SOURCES) $(FUZZ_SOURCES) $(WORST_CASE_SOURCES)
TEST_SOURCES += $(REENTRANCY_SOURCES) $(Q_SOURCES)

all: sandbox examples test

.PHONY: examples test

run: sandbox
	@./bin/boggle

run-demo: examples
	@./examples/demo ./examples/350k.txt

run-api-demo: examples
	@./examples/api-demo ./test/task.txt

sandbox: $(SANDBOX_SOURCES)
	c++ $(CXXFLAGS) $(SANDBOX_SOURCES) -o ./bin/boggle

examples: $(DEMO_SOURCES) $(API_DEMO_SOURCES)
	c++ $(CXXFLAGS) $(DEMO_SOURCES) -o ./examples/demo
	c++ $(CXXFLAGS) $(API_DEMO_SOURCES) -o ./examples/api-demo

test: test-task test-stress test-worst-case test-reentrancy test-q
	@echo "SUCCESS: All tests passed!"

test-task: $(TASK_SOURCES)
	c++ $(CXXFLAGS) $(TASK_SOURCES) -o ./test/task
	@./test/task

test-stress: $(STRESS_SOURCES)
	c++ $(CXXFLAGS) $(STRESS_SOURCES) -o ./test/stress
	@./test/stress

test-worst-case: $(WORST_CASE_SOURCES)
	c++ $(CXXFLAGS) $(WORST_CASE_SOURCES) -o ./test/worst-case
	@./test/worst-case

test-reentrancy: $(REENTRANCY_SOURCES)
	c++ $(CXXFLAGS) $(REENTRANCY_SOURCES) -o ./test/reentrancy
	@./test/reentrancy

test-q: $(Q_SOURCES)
	c++ $(CXXFLAGS) $(Q_SOURCES) -o ./test/q
	@./test/q

clean:
	-@rm -f ./bin/boggle
	-@rm -f ./examples/demo
	-@rm -f ./examples/api-demo
	-@rm -f ./test/task
	-@rm -f ./test/stress
	-@rm -f ./test/worst-case
	-@rm -f ./test/reentrancy
	-@rm -f ./test/q
