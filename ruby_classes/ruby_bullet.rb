class Bullet
  def initialize x, y, power, ship_name
    @x = x
    @y = y
    @power = power
    @ship_name = ship_name
  end

  def setPos x, y
    @x = x
    @y = y
  end

  def getPower
   return @power
  end

  def getX
   return @x
  end

  def getY
   return @y
  end
 
  def getOwnerName
    return @ship_name
  end
end

