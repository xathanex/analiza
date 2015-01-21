all:
	g++ -O2 -std=c++11 -lruby -lcrypt ruby_bridge_test.cpp ../sources/ruby_bridge.cpp -o ruby_bridge_test.x
	g++ -O2 -std=c++11 -lruby -lcrypt -I ../sources ruby_ship_test.cpp ../sources/ruby_bridge.cpp ../sources/ruby_ship.cpp ../sources/ruby_bullet.cpp -o ruby_ship_test.x
	g++ -O2 -std=c++11 -lruby -lcrypt -I ../sources ruby_bullet_test.cpp ../sources/ruby_bridge.cpp ../sources/ruby_bullet.cpp -o ruby_bullet_test.x
	
clean:
	rm *~ *.x
	
run:
	@echo ""
	@echo "RubyBridge tests"
	@./ruby_bridge_test.x
	
	@echo ""
	@echo "RubyShip tests"
	@./ruby_ship_test.x
	
	@echo ""
	@echo "RubyBullet tests"
	@./ruby_bullet_test.x
