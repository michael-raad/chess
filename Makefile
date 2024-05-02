all: main

projname=chess

main:
	mkdir -p build && cd build && cmake ..
	make -C build
	cp -f build/${projname} .

debug:
	mkdir -p build && cd build && cmake -DCMAKE_BUILD_TYPE=Debug ..
	make -C build
	cp -f build/${projname} .

clean:
	rm -rf build
