CC = g++
CFLAGS = -fpermissive
LIBS = -lm

SPHEREOBJS= sphere.o evert.o threejet.o threejetvec.o spline.o figureeight.o twojet.o twojetvec.o

.cpp.o:
	$(CC) $(CFLAGS) -c ${@:o=cpp}

evert: $(SPHEREOBJS)
	$(CC) $(CFLAGS) $(SPHEREOBJS) $(LIBS) -o evert

clean:
	rm -f $(SPHEREOBJS) evert

manual:
	latex manual
