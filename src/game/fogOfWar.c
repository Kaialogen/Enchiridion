#include "fogOfWar.h"

int hasLOS(Entity *src, int x2, int y2);

static int hasSolid[MAP_WIDTH][MAP_HEIGHT];

void updateFogOfWar(void)
{
	int x, y, mx, my;
	Entity *e;

	for (x = 0 ; x < MAP_WIDTH ; x++)
	{
		for (y = 0 ; y < MAP_HEIGHT ; y++)
		{
			hasSolid[x][y] = 0;

			dungeon.map[x][y].visible = 0;
		}
	}

	for (e = dungeon.entityHead.next ; e != NULL ; e = e->next)
	{
		if (e != dungeon.player && e->solid)
		{
			hasSolid[e->x][e->y] = 1;
		}
	}

	for (y = -VIS_DISTANCE ; y <= VIS_DISTANCE ; y++)
	{
		for (x = -VIS_DISTANCE ; x <= VIS_DISTANCE ; x++)
		{
			mx = dungeon.player->x + x;
			my = dungeon.player->y + y;

			if (getDistance(dungeon.player->x, dungeon.player->y, mx, my) <= VIS_DISTANCE)
			{
				if (mx >= 0 && my >= 0 && mx < MAP_WIDTH && my < MAP_HEIGHT)
				{
					if (!dungeon.map[mx][my].visible && hasLOS(dungeon.player, mx, my))
					{
						dungeon.map[mx][my].revealed = dungeon.map[mx][my].visible = 1;
					}
				}
			}
		}
	}
}

int hasLOS(Entity *src, int x2, int y2)
{
	int x1, y1, dx, dy, sx, sy, err, e2;

	x1 = src->x;
	y1 = src->y;

	dx = abs(x2 - x1);
	dy = abs(y2 - y1);

	sx = (x1 < x2) ? 1 : -1;
	sy = (y1 < y2) ? 1 : -1;
	err = dx - dy;

	while (1)
	{
		e2 = 2 * err;

		if (e2 > -dy)
		{
			err -= dy;
			x1 += sx;
		}

		if (e2 < dx)
		{
			err += dx;
			y1 += sy;
		}

		if (x1 == x2 && y1 == y2)
		{
			return 1;
		}

		if (dungeon.map[x1][y1].tile >= TILE_WALL || hasSolid[x1][y1])
		{
			return 0;
		}
	}

	return 0;
}
