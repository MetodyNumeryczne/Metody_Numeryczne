all:
	g++ -L /usr/lib/lapack -L /usr/lib/blas  main.cpp core.cpp -o main -lblas -llapack
