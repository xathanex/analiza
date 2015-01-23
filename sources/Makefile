all:
	g++ -O2 -std=c++11 -I /usr/include/ruby-1.9.1/ -I /usr/include/ruby-1.9.1/x86_64-linux/ -lruby -lcrypt -lSDL -lglu32 -lGL bullet.cpp engine.cpp main.cpp ruby_bridge.cpp ruby_ship.cpp ruby_bullet.cpp ship.cpp graphics/AssetLoader.cpp graphics/Model.cpp graphics/Scene.cpp graphics/SceneObjects.cpp graphics/Vector3.cpp graphics/Water.cpp -o ../RubyShips.x

clean:
	rm *~ *.x

run:
	../RubyShips.x
