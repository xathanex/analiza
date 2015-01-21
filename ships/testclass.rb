class Testclass < RubyShip
	def onScannedShip scannedShipEvent
		puts scannedShipEvent.inspect
		setAhead(100)
	end

	def onHitByBullet hitByBulletEvent
		puts hitByBulletEvent.inspect
		setAhead(10)
	end

	def onBulletHit bulletHitEvent
		puts bulletHitEvent.inspect
		setAhead(20)
	end

	def onBulletHitBullet bulletHitBulletEvent
		puts bulletHitBulletEvent.inspect
		setAhead(30)
	end

	def onShipHit shipHitEvent
		puts shipHitEvent.inspect
		setAhead(40)
	end

	def run
		setAhead(100)
		setTurnLeft(0.2)
		setTurnRadarLeft(999)
	end
end

