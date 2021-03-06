#pragma once
#include "../GameObjects/GameObject.h"
#include "../Animations/Animation.h"
#include "../GameObjects/Whip.h"
#include "../DaggerWeapon.h"
#include "../CombatWeapon.h"
#include "../BaseInfo.h"
#include "../ObjectStair.h"
#include "../MovingMap.h"

class Simon: public GameObject
{
private: 
	int ani;
	int untouchable;
	DWORD untouchable_start;
	DWORD comeEntranceStart = 0;
	DWORD invisible_Potion_Start = 0;
	bool isInSpawn = false;
	std::string activateNameEnemy;
	EntityID idEnemySpawn;
	bool enableSubWeapon = false;
	bool isjumping = false;
	bool checkRewind = false;
	bool isOnStair = false;
	bool hasMovedEndMap = false;
	bool isVisible = false;
	bool isMovingDoor = false;
	DWORD startAtack = 0;
	DWORD startAtackSub= 0;
	DWORD startHurt;
	DWORD startDie = 0;
	DWORD startChangeColor = 0;
	bool OnGround = false;
	ObjectStair* originalStair = nullptr;
	ObjectStair* reverseStair = nullptr;
	D3DXVECTOR2 resetPosition;
	bool istartsandup = false;
	Flip flip;

	Whip* whip;
	int levelWhip;
	int WHIP_STATE;
	int changeColorId = 0;
	int startThrowWeapon = 0;
	BaseInfo* baseInfo;
	std::vector<LPGAMEOBJECT> objectCollision;
	static Simon* _instance;
	Simon();
public:
	enum State
	{
		SIMON_STATE_IDLE,
		SIMON_STATE_WALKING_RIGHT,
		SIMON_STATE_WALKING_LEFT,
		SIMON_STATE_JUMPING,
		SIMON_STATE_JUMPTOUCHGROUND,
		SIMON_STATE_SITDOWN,
		SIMON_STATE_ATTACK_STAND,
		SIMON_STATE_ATTACK_STAND_SUBWEAPON,
		SIMON_STATE_ATTACK_SITDOWN,
		SIMON_STATE_ATTACK_SITDOWN_SUBWEAPON,
		SIMON_STATE_ATTACK_JUMP,
		SIMON_STATE_ATTACK_JUMP_SUBWEAPON,
		SIMON_STATE_DIE,
		SIMON_STATE_CHANGECOLOR,
		SIMON_STATE_GO_UP_STAIR,
		SIMON_STATE_GO_DOWN_STAIR,
		SIMON_STATE_IDLE_UP_STAIR,
		SIMON_STATE_IDLE_DOWN_STAIR,
		SIMON_STATE_ATTACK_UP_STAIR,
		SIMON_STATE_ATTACK_DOWN_STAIR,
		SIMON_STATE_HURT,
		SIMON_STATE_AUTO_GOES_RIGHT
	};

	static Simon* getInstance();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render(Viewport* viewport);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);

	BaseInfo* getBaseInfo() { return baseInfo; }
	ObjectStair*  getOriginalStair() { return originalStair; }
	void setActivateEnemyName(std::string nameEnemy) { this->activateNameEnemy = nameEnemy; }
	std::string getActivateEnemyName() { return activateNameEnemy; }

	bool isMovedEndMap();
	void SetStateMoveEndMap(bool hasMovedMap);
	bool isOnGround();
	bool IsOnStair() { return isOnStair; }
	void SetIsOnStair(bool isOnStair){}
	bool IsMovingDoor() { return isMovingDoor; }
	void setIsMovingDoor(bool isMovingDoor) {this->isMovingDoor = isMovingDoor;}
	void SetState(int state);
	bool checkisInSpawn() { return isInSpawn; }
	void setIsInSpawn(bool isInSpawn) { this->isInSpawn = isInSpawn; }
	EntityID getIdEnemySpawn() { return idEnemySpawn; }
	void setIdEnemySpawn(EntityID idEnemySpawn) { this->idEnemySpawn = idEnemySpawn; }
	void Reset(int state);
	void updateCollisionStair();
	void updateCollisionSubStair();
	void Simon::handleOutOfStair();
	void handleCollisionObjectGame(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void handleAfterCollision(vector<LPGAMEOBJECT> *coObjects, EntityID id ,int i, vector<LPCOLLISIONEVENT> *coEvents);
	void handleCollisionIntersectedObject(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	void resetWhenDie();
	void setResetPosition(D3DXVECTOR2 pos);
	D3DXVECTOR2 getResetPosition() { return resetPosition; }

	void SetUpJump();

	void RemoveWhip();
	void SetupAtacking();
	void SetupSubWeapon(vector<LPGAMEOBJECT> *coObjects);
	void RenderWeapon(LPANIMATION animation, Viewport* viewport);
	void UpdateWeapon(DWORD dt, vector<LPGAMEOBJECT> *coObjects);

	void OnKeyStateChange(BYTE *states);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
	~Simon();
};

	