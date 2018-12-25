# -----------------------------------------------------------------------------------------------------------------------------#
CCX    = g++
CFLAGS = -no-pie -fno-PIE -fno-pic -fno-PIC -fno-stack-protector -Wno-unused-result
CFAST  = -Ofast -march=native -funroll-loops -flto -pipe -DNDEBUG
CLIBS  = -lm

# -----------------------------------------------------------------------------------------------------------------------------#
all: evert

clean:
	rm -f evert geom*.oogl geom*.bezier

# -----------------------------------------------------------------------------------------------------------------------------#
evert: evert.cpp makefile
	$(CCX) $< -o evert $(CFLAGS) $(CLIBS)

release: evert.cpp makefile
	$(CCX) $< -o evert $(CFLAGS) $(CLIBS) $(CFAST)

manual:
	latex manual

oogl: oogl00 oogl01 oogl02 oogl03 oogl04 oogl05 oogl06 oogl07 oogl08 oogl09 oogl10
bezier: bezier00 bezier01 bezier02 bezier03 bezier04 bezier05 bezier06 bezier07 bezier08 bezier09 bezier10

# -----------------------------------------------------------------------------------------------------------------------------#
oogl00:
	./evert -time 0.0          -nstrips 8 -scale 1  -umin 0 -umax 1 -du .04167  -vmin 0  -vmax 1 -dv .04167  >  geom_00.oogl
oogl01:
	./evert -time 0.1          -nstrips 8 -scale 1  -umin 0 -umax 1 -du .04167  -vmin 0  -vmax 1 -dv .04167  >  geom_01.oogl
oogl02:
	./evert -time 0.2          -nstrips 8 -scale 1  -umin 0 -umax 1 -du .04167  -vmin 0  -vmax 1 -dv .04167  >  geom_02.oogl
oogl03:
	./evert -time 0.3          -nstrips 8 -scale 1  -umin 0 -umax 1 -du .04167  -vmin 0  -vmax 1 -dv .04167  >  geom_03.oogl
oogl04:
	./evert -time 0.4          -nstrips 8 -scale 1  -umin 0 -umax 1 -du .04167  -vmin 0  -vmax 1 -dv .04167  >  geom_04.oogl
oogl05:
	./evert -time 0.5          -nstrips 8 -scale 1  -umin 0 -umax 1 -du .04167  -vmin 0  -vmax 1 -dv .04167  >  geom_05.oogl
oogl06:
	./evert -time 0.6          -nstrips 8 -scale 1  -umin 0 -umax 1 -du .04167  -vmin 0  -vmax 1 -dv .04167  >  geom_06.oogl
oogl07:
	./evert -time 0.7          -nstrips 8 -scale 1  -umin 0 -umax 1 -du .04167  -vmin 0  -vmax 1 -dv .04167  >  geom_07.oogl
oogl08:
	./evert -time 0.8          -nstrips 8 -scale 1  -umin 0 -umax 1 -du .04167  -vmin 0  -vmax 1 -dv .04167  >  geom_08.oogl
oogl09:
	./evert -time 0.9          -nstrips 8 -scale 1  -umin 0 -umax 1 -du .04167  -vmin 0  -vmax 1 -dv .04167  >  geom_09.oogl
oogl10:
	./evert -time 1.0          -nstrips 8 -scale 1  -umin 0 -umax 1 -du .04167  -vmin 0  -vmax 1 -dv .04167  >  geom_10.oogl

# -----------------------------------------------------------------------------------------------------------------------------#
bezier00:
	./evert -time 0.0 -bezier  -nstrips 8 -scale 1  -umin 0 -umax 1 -du .04167  -vmin 0  -vmax 1 -dv .04167  >  geom_00.bezier
bezier01:
	./evert -time 0.1 -bezier  -nstrips 8 -scale 1  -umin 0 -umax 1 -du .04167  -vmin 0  -vmax 1 -dv .04167  >  geom_01.bezier
bezier02:
	./evert -time 0.2 -bezier  -nstrips 8 -scale 1  -umin 0 -umax 1 -du .04167  -vmin 0  -vmax 1 -dv .04167  >  geom_02.bezier
bezier03:
	./evert -time 0.3 -bezier  -nstrips 8 -scale 1  -umin 0 -umax 1 -du .04167  -vmin 0  -vmax 1 -dv .04167  >  geom_03.bezier
bezier04:
	./evert -time 0.4 -bezier  -nstrips 8 -scale 1  -umin 0 -umax 1 -du .04167  -vmin 0  -vmax 1 -dv .04167  >  geom_04.bezier
bezier05:
	./evert -time 0.5 -bezier  -nstrips 8 -scale 1  -umin 0 -umax 1 -du .04167  -vmin 0  -vmax 1 -dv .04167  >  geom_05.bezier
bezier06:
	./evert -time 0.6 -bezier  -nstrips 8 -scale 1  -umin 0 -umax 1 -du .04167  -vmin 0  -vmax 1 -dv .04167  >  geom_06.bezier
bezier07:
	./evert -time 0.7 -bezier  -nstrips 8 -scale 1  -umin 0 -umax 1 -du .04167  -vmin 0  -vmax 1 -dv .04167  >  geom_07.bezier
bezier08:
	./evert -time 0.8 -bezier  -nstrips 8 -scale 1  -umin 0 -umax 1 -du .04167  -vmin 0  -vmax 1 -dv .04167  >  geom_08.bezier
bezier09:
	./evert -time 0.9 -bezier  -nstrips 8 -scale 1  -umin 0 -umax 1 -du .04167  -vmin 0  -vmax 1 -dv .04167  >  geom_09.bezier
bezier10:
	./evert -time 1.0 -bezier  -nstrips 8 -scale 1  -umin 0 -umax 1 -du .04167  -vmin 0  -vmax 1 -dv .04167  >  geom_10.bezier
