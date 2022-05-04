install:
	xargs apt-get install -y <requirements.txt

build:
	gcc -Wall ${file}.c -o bin/${file} -I /usr/include/postgresql/ -lpq -lcurl -ljson-c 

run: 
	make build file=weather
	./bin/weather

clean:
	rm tmp/* bin/*
