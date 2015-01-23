#ifndef TURN_DATA_H
#define TURN_DATA_H

struct TurnData
{
	double energy, turn, max_turn_speed, radar_turn, radar_max_turn_speed, gun_turn, gun_max_turn_speed, fire_power;
	short move;
  unsigned short max_speed, x, y;
	bool fire, fired;
	int last_fired_bullet_id;
};

#endif
