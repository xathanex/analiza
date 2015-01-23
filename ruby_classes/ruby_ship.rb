class RubyShip
	def initialize
		@energy = 100
		@move = 0
		@turn = 0
		@max_speed = 8
		@max_turn_speed = 4
		@radar_turn = 0
		@radar_max_turn_speed = 45
		@gun_turn = 0
		@gun_max_turn_speed = 15
		@lastBulletShot = nil
		@fire_power = nil
		@fired = false
		@y = 0
		@x = 0
	end

	def x
		return @x
	end

	def x= value
		@x = value
	end

	def y
		return @y
	end

	def y= value
		@y = value
	end

	def fire_power
		return @fire_power
	end
	
	def fire_power= value
		return @fire_power
	end
	
	def fired
		return @fired
	end
	
	def fired= value
		return @fired = value
	end

	def energy
		return @energy
	end
	
	def energy= value
		@energy = value
	end
	
	def move
		return @move
	end
	
	def move= value
		return @move = value
	end
	
	def turn
		return @turn
	end
	
	def turn= value
		return @turn = value
	end
	
	def max_speed
		return @max_speed
	end
	
	def max_speed= value
		return @max_speed = value
	end
	
	def max_turn_speed
		return @max_turn_speed
	end
	
	def max_turn_speed= value
		return @max_turn_speed = value
	end
	
	def radar_turn
		return @radar_turn
	end
	
	def radar_turn= value
		return @radar_turn = value
	end
	
	def radar_max_turn_speed
		return @radar_max_turn_speed
	end
	
	def radar_max_turn_speed= value
		return @radar_max_turn_speed = value
	end

	def gun_turn
		return @gun_turn
	end
	
	def gun_turn= value
		return @gun_turn = value
	end
	
	def gun_max_turn_speed
		return @gun_max_turn_speed
	end
	
	def gun_max_turn_speed= value
		return @gun_max_turn_speed = value
	end

	def onScannedShip scannedShipEvent
	end

	def onHitByBullet hitByBulletEvent
	end

	def onBulletHitBullet bulletHitBulletEvent
	end

	def onBulletHit bulletHitEvent
	end
	
	def onShipHit shipHitEvent
	end

	def run
	end

	def setAhead mv
		@move = mv
	end

	def setBack mv
		setAhead -mv
	end

	def setTurnLeft angle
		@turn = angle
	end

	def setTurnRight angle
		setTurnLeft -angle
	end

	def setTurnRadarLeft angle
		@radar_turn = angle
	end

	def setTurnRadarRight angle
		setTurnRadarLeft -angle
	end
	
end
