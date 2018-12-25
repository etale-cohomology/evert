# -----------------------------------------------------------------------------------------------------------------------------#
CCX    = g++
CFLAGS = -no-pie -fno-PIE -fno-pic -fno-PIC -fno-stack-protector -Wno-unused-result
CFAST  = -Ofast -march=native -funroll-loops -flto -pipe -DNDEBUG
CLIBS  = -lm

# -----------------------------------------------------------------------------------------------------------------------------#
all: evert

clean:
	rm -f evert

# -----------------------------------------------------------------------------------------------------------------------------#
evert: evert.cpp makefile
	$(CCX) $< -o $@ $(CFLAGS) $(CLIBS)

release: evert.cpp makefile
	$(CCX) $< -o $@ $(CFLAGS) $(CLIBS) $(CFAST)

manual:
	latex manual
