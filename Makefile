# In  order  to  execute  this  "Makefile " just  type  "make "
OBJS     = main.o euclideanNode.o hashFunction.o List.o Node.o hashFunctionCosine.o hashFunctionEuclidean.o hashFunctionMatrix.o hashtable.o lsh.o psedoRandomNumbers.o readFile.o 
SOURCE   = main.cpp euclideanNode.cpp hashFunction.cpp List.cpp Node.cpp hashFunctionCosine.cpp hashFunctionEuclidean.cpp hashFunctionMatrix.cpp hashtable.cpp lsh.cpp psedoRandomNumbers.cpp readFile.cpp
HEADER   = dataTypes.h euclideanNode.h hashFunction.h List.h Node.h hashFunctionCosine.h hashFunctionEuclidean.h hashFunctionMatrix.h hashtable.h lsh.h psedoRandomNumbers.h readFile.h
OUT      = lsh
CC       = g++
FLAGS    = -g -c
# -g  option  enables  debugging  mode
# -c flag  generates  object  code  for  separate  files
all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT)
#  create/ compile  the  individual  files  >> separately <<

main.o: main.cpp $(HEADER)
	$(CC) $(FLAGS) main.cpp

euclideanNode.o: euclideanNode.cpp euclideanNode.h
	$(CC) $(FLAGS) euclideanNode.cpp
	
hashFunction.o: hashFunction.cpp hashFunction.h
	$(CC) $(FLAGS) hashFunction.cpp

hashtable.o: hashtable.cpp hashtable.h
	$(CC) $(FLAGS) hashtable.cpp

List.o: List.cpp List.h
	$(CC) $(FLAGS) List.cpp

Node.o: Node.cpp Node.h
	$(CC) $(FLAGS) Node.cpp

hashFunctionCosine.o: hashFunctionCosine.cpp hashFunctionCosine.h
	$(CC) $(FLAGS) hashFunctionCosine.cpp
	
hashFunctionEuclidean.o: hashFunctionEuclidean.cpp hashFunctionEuclidean.h
	$(CC) $(FLAGS) hashFunctionEuclidean.cpp
	
hashFunctionMatrix.o: hashFunctionMatrix.cpp hashFunctionMatrix.h
	$(CC) $(FLAGS) hashFunctionMatrix.cpp
	
lsh.o: lsh.cpp lsh.h
	$(CC) $(FLAGS) lsh.cpp

psedoRandomNumbers.o: psedoRandomNumbers.cpp psedoRandomNumbers.h
	$(CC) $(FLAGS) psedoRandomNumbers.cpp

readFile.o: readFile.cpp readFile.h
	$(CC) $(FLAGS) readFile.cpp

#  clean  house
clean :
	rm -f $(OBJS) $(OUT)
