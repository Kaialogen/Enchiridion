#include "aStar.h"

static int isBlocked(int x, int y);

static Node nodeHead;
static Node *nodeTail;
static Entity *owner;

void initAStar(void)
{
	memset(&nodeHead, 0, sizeof(Node));
	nodeTail = &nodeHead;
}

void resetAStar(void)
{
	Node *n;

	while (nodeHead.next != NULL)
	{
		n = nodeHead.next;
		nodeHead.next = n->next;
		free(n);
	}

	nodeTail = &nodeHead;
}

static void addNodeToOpenList(Node *node)
{
	Node *n;

	if (node->f != -1)
	{
		for (n = nodeHead.next ; n != NULL ; n = n->next)
		{
			if (n->x == node->x && n->y == node->y)
			{
				if (node->f < n->f)
				{
					n->f = node->f;
					n->g = node->g;
					n->h = node->h;
					n->closed = 0;
					n->parent = node->parent;
				}

				free(node);

				return;
			}
		}

		nodeTail->next = node;
		nodeTail = node;
	}
	else
	{
		free(node);
	}
}

static Node *getSmallestNode(void)
{
	Node *smallest, *n;

	smallest = n = NULL;

	for (n = nodeHead.next ; n != NULL ; n = n->next)
	{
		if (!n->closed && n->f != -1 && (smallest == NULL || n->f < smallest->f))
		{
			smallest = n;
		}
	}

	return smallest;
}

static void buildRouteMap(int sx, int sy, int ex, int ey)
{
	int x, y, count;
	Node *start;
	Node *currentNode;
	Node *newNode;

	start = malloc(sizeof(Node));
	memset(start, 0, sizeof(Node));
	start->x = sx;
	start->y = sy;
	addNodeToOpenList(start);

	currentNode = start;

	count = 0;

	while (1)
	{
		for (y = -1 ; y <= 1; y++)
		{
			for (x = -1 ; x <= 1; x++)
			{
				if (x == 0 && y == 0)
				{
					continue;
				}

				if (currentNode->x + x < 0 || currentNode->y + y < 0 || currentNode->x + x >= MAP_WIDTH || currentNode->y + y >= MAP_HEIGHT)
				{
					continue;
				}

				newNode = malloc(sizeof(Node));
				memset(newNode, 0, sizeof(Node));

				newNode->x = currentNode->x + x;
				newNode->y = currentNode->y + y;

				if (!isBlocked(newNode->x, newNode->y))
				{
					if (x != 0 && y != 0)
					{
						newNode->g = currentNode->g + 14;
					}
					else
					{
						newNode->g = currentNode->g + 10;
					}

					newNode->h = 10 * (abs(newNode->x - ex) + abs(newNode->y - ey));

					newNode->f = newNode->g + newNode->h;
				}
				else
				{
					newNode->f = -1;
					newNode->g = -1;
					newNode->h = -1;
				}

				newNode->parent = currentNode;

				addNodeToOpenList(newNode);

				if (++count >= MAP_HEIGHT * MAP_WIDTH)
				{
					return;
				}
			}
		}

		currentNode = getSmallestNode();

		if (!currentNode)
		{
			break;
		}

		currentNode->closed = 1;

		if (currentNode->x == ex && currentNode->y == ey)
		{
			break;
		}
	}
}

static int isBlocked(int x, int y)
{
	Entity *e;

	if (dungeon.map[x][y].tile == TILE_HOLE || dungeon.map[x][y].tile >= TILE_WALL)
	{
		return 1;
	}

	e = getEntityAt(x, y);

	if (e != NULL && e != owner && e->solid)
	{
		return 1;
	}

	return 0;
}

static Node *findNextMove(int x, int y)
{
	Node *n;

	for (n = nodeHead.next ; n != NULL ; n = n->next)
	{
		if (n->x == x && n->y == y)
		{
			return n->parent;
		}
	}

	return NULL;
}

void createAStarRoute(Entity *e, int x, int y, int *dx, int *dy)
{
	Node *n;

	owner = e;

	*dx = 0;
	*dy = 0;

	resetAStar();

	buildRouteMap(x, y, e->x, e->y);

	n = findNextMove(e->x, e->y);

	if (n != NULL)
	{
		*dx = n->x - e->x;
		*dy = n->y - e->y;
	}
}
