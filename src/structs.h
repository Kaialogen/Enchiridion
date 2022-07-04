typedef struct Entity Entity;
typedef struct AtlasImage AtlasImage;
typedef struct Texture Texture;
typedef struct InitFunc InitFunc;
typedef struct Node Node;

struct AtlasImage {
	char filename[MAX_FILENAME_LENGTH];
	SDL_Texture *texture;
	SDL_Rect rect;
	int rotated;
	AtlasImage *next;
};

struct Texture {
	char name[MAX_FILENAME_LENGTH];
	SDL_Texture *texture;
	Texture *next;
};

struct Node {
	int x;
	int y;
	int g;
	int f;
	int h;
	int closed;
	Node *parent;
	Node *next;
};

struct Entity {
	int id;
	int type;
	char name[MAX_NAME_LENGTH];
	int x;
	int y;
	int dead;
	int solid;
	int facing;
	void (*data);
	AtlasImage *texture;
	Entity *next;
};

typedef struct {
	int hp, maxHP;
	int minAttack;
	int maxAttack;
	int defence;
	int alert;
	int visRange;
	SDL_Point patrolDest;
} Monster;

struct InitFunc {
	char name[MAX_NAME_LENGTH];
	void (*init)(Entity *e);
	InitFunc *next;
};

typedef struct {
	int tile;
	int visible;
	int revealed;
} MapTile;

typedef struct {
	int entityId;
	Entity entityHead, *entityTail;
	Entity deadHead, *deadTail;
	Entity *player, *currentEntity, *attackingEntity;
	MapTile map[MAP_WIDTH][MAP_HEIGHT];
	SDL_Point camera;
	SDL_Point attackDir;
	double animationTimer;
} Dungeon;

typedef struct {
	struct {
		void (*logic)(void);
		void (*draw)(void);
	} delegate;

	double deltaTime;
	double fontScale;
	SDL_Renderer *renderer;
	SDL_Window *window;
	int keyboard[MAX_KEYBOARD_KEYS];

	struct {
		int fps;
	} dev;
} App;
