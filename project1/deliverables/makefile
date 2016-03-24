cipher: cipher.o
	gcc cipher.c -o cipher
cipher.o: cipher.c

decipher: decipher.o
	gcc decipher.c -o decipher
decipher: decipher.c

test: test1 test2
test1:
	./cipher 1 5 smallRaw smallEncrypted
	./decipher smallEncrypted smallDecrypted LetFreq
	diff -s smallRaw smallDecrypted >> test1Result
test2:
	./cipher 1 7 largeRaw largeEncrypted
	./decipher largeEncrypted largeDecrypted LetFreq
	diff -s largeRaw largeDecrypted >> test2Result

