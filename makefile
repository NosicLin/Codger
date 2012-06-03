main:
	make -C src
	mkdir -p bin
	cp src/engine/bin/codger.exe bin/codger 

install:
	cp bin/codger  /usr/bin/

rm:
	rm -f /usr/bin/codger 
