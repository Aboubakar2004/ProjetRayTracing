# Shortcuts for the CMake commands. Run inside the dev container: make <target>
.PHONY: build run test clean

build:
	cmake --preset debug
	cmake --build --preset debug

run: build
	./build/debug/hello

test: build
	ctest --preset debug

clean:
	rm -rf build
