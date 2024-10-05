#ifndef WAVE_HPP
#define WAVE_HPP

#include "enemy_type.hpp"

#include <vector>

struct Wave
{
	struct SpawnEvent
	{
		double interval = 0;
		int spawn_point = 1;
		EnemyType enemy_type = EnemyType::Slim;
	};

	double rawards = 0;
	double interval = 0;
	std::vector<SpawnEvent> spawn_event_list;
};

#endif // WAVE_HPP