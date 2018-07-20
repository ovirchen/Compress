#!/bin/sh
	mkdir -p build
	cd build
	cmake ../ && make
	mv compress ../compress
	cd ..
	rm -rf build