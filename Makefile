# ---------------------------------------------------------------------------
# "THE BEER-WARE LICENSE" (Revision 42):
# <floreal@nimukaito.net> wrote this file. As long as you retain this notice
# you can do whatever you want with this stuff. If we meet some day, and you
# think this stuff is worth it, you can buy me a beer in return.
# Floréal Toumikian
# ---------------------------------------------------------------------------

CFLAGS += -std=c11 -Inanotest

SRC = $(wildcard src/*.c)
OBJ = $(shell echo $(SRC) | sed 's/\.c/\.o/g')

TEST_SRC = $(wildcard test/test_*.c)
TEST_OBJ = $(shell echo $(TEST_SRC) | sed 's/\.c/\.o/g')

NANOTEST_SRC = $(wildcard nanotest/*.c)
NANOTEST_OBJ = $(shell echo $(NANOTEST_SRC) | sed 's/\.c/\.o/g')

SCRIPT_BUILD_TESTSUITE = scripts/build_testsuite.sh

TESTSUITE = test/main.c
TESTSUITE_COMPILED = test/run

all: $(OBJ)
	# compile your lib or executable here

$(TESTSUITE_COMPILED): $(TEST_OBJ) $(OBJ) $(TESTSUITE) $(NANOTEST_OBJ)
	$(CC) $(CFLAGS) -o $(TESTSUITE_COMPILED) $(TEST) $(OBJ) $(TESTSUITE) $(NANOTEST_OBJ)

check: $(TESTSUITE_COMPILED)
	@$<

%.c: %.h

%.o: %.c
	$(CC) $(CFLAGS) -Isrc -o $@ -c $<

$(TESTSUITE): $(SCRIPT_BUILD_TESTSUITE)
	$(SCRIPT_BUILD_TESTSUITE) > $(TESTSUITE)

clean:
	$(RM) -Rf $(OBJ) $(TEST_OBJ) $(TAP) $(TESTSUITE) $(TESTSUITE_COMPILED) $(NANOTEST_OBJ)

.PHONY: check all clean compile-test
