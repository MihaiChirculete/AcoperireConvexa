all:
	g++ proiect.cpp -lglut -lGL -o proiect.a

clean:	proiect.a
	rm proiect.a