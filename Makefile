install:
	xargs apt-get install -y <requirements.txt

build:
	gcc -Wall ${file}.c -o ${file} -I /usr/include/postgresql/ -lpq -lcurl -ljson-c

run: 
	make build file=weather
	./weather

clean:
	rm tmp/* bin/*
