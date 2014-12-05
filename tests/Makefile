all:
	g++ -O2 -std=c++11 -lruby -lcrypt ruby_bridge_test.cpp ../sources/ruby_bridge.cpp -o ruby_bridge_test.x
	
clean:
	rm *~ *.x
	
run:
	./ruby_bridge_test.x
