#include "PlayerShip.h"
#include "DebugMemory.h"
#include "Shape.h"
#include "Core.h"
#include "Game.h"
#include <cmath>

// this should make the ship 59x59 pixels
static Vector2 ship[] = {
	// top
	Vector2(0,-29),
	
	// right side
	Vector2(3,-4), Vector2(25,14),Vector2(27,1),
	Vector2(29,22),Vector2(10,11),Vector2(9,15),Vector2(4,14),
	
	// bottom
	Vector2(0,29),

	// left side
	Vector2(-4,14),Vector2(-9,15),Vector2(-10,11),
	Vector2(-29,22),Vector2(-27,1),Vector2(-25,14),Vector2(-3,-4)
};

static Vector2 gunShape[] = { Vector2(0, -4), Vector2(2, 3), Vector2(-2, 3) };

const float PlayerShip::BASE_A = 25.f;
const float PlayerShip::MAX_V = 350.0f;
const float PlayerShip::ROT_D = 2.0f;
const float PlayerShip::SPEED = 7000.0f;
const float PlayerShip::FRICTION = 50.0f;
const float PlayerShip::TURRET_OFFSET = 5.0f;
const float PlayerShip::FIRE_DELAY = 220;

PlayerShip::PlayerShip(Vector2 startPos)
: GameObject(startPos, SHAPE(ship)) {
	gun = new GameObject(startPos, SHAPE(gunShape));
	gun->color = Color::YELLOW;
	lastFired = 0;
	isDead = false;

	leftPs = new ParticleSystem(50);
	leftPs->minVelocity = Vector2(-2,0);
	leftPs->minLifeTime = .1f;
	leftPs->maxLifeTime  = .25f;
	leftPs->minRadius = 4;
	leftPs->maxRadius = 6;
	leftPs->startColor = RGBA(255,230,0,100);
	leftPs->endColor = RGBA(255,0,0,255);
	leftPs->sizeDelta = 0;

	rightPs = new ParticleSystem(leftPs->size);
	rightPs->minVelocity = leftPs->minVelocity;
	rightPs->minLifeTime = leftPs->minLifeTime;
	rightPs->maxLifeTime  = leftPs->maxLifeTime;
	rightPs->minRadius = leftPs->minRadius;
	rightPs->maxRadius = leftPs->maxRadius;
	rightPs->startColor = leftPs->startColor;
	rightPs->endColor = leftPs->endColor;
	rightPs->sizeDelta = leftPs->sizeDelta;

	Game::particleManager->add(leftPs);
	Game::particleManager->add(rightPs);

	hp = 10;
}

PlayerShip::~PlayerShip() {
	delete gun;

	projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(), 
	[](Projectile* p) {
		delete p;
		return true;
	}), projectiles.end());
}

void PlayerShip::update(float dt) {
	rotate(dt);
	move(dt);
	
	velocity += acceleration * dt;

	// max out velocity
	velocity.x = velocity.x > 0 ? min(MAX_V, velocity.x) : max(-MAX_V, velocity.x);
	velocity.y = velocity.y > 0 ? min(MAX_V, velocity.y) : max(-MAX_V, velocity.y);

	position += velocity * dt;

	// turret logic
	int mX, mY;
	Core::Input::GetMousePos(mX, mY);
	gun->position = position + (Vector2(-sin(rotation), cos(rotation)) * TURRET_OFFSET);
	Vector2 diff = (Vector2((float)mX, (float)mY) - gun->position).perpCW();
	gun->rotation = atan2(-diff.y, -diff.x);

	if (fireController != NULL && fireController()) {
		ULONGLONG now = GetTickCount64();
		if (now - lastFired > FIRE_DELAY) {
			lastFired = now;
			Projectile* p = new Projectile(gun->position, gun->rotation);
			projectiles.push_back(p);
		}
	}

	projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(), 
		[&](Projectile* p) {
			p->update(dt);

			Vector2 pos = p->position;
			bool isDead = p->isDead() || pos.x < -5 || pos.x > Game::SCREEN_WIDTH + 5 || pos.y < -5 || pos.y > Game::SCREEN_HEIGHT + 5;

			if (isDead) {
				delete p;
				return true;
			}

			return false;
		}), projectiles.end());

	leftPs->position = Matrix3::translation(position)*Matrix3::rotation(rotation)*Vector2(-24,22);
	rightPs->position =  Matrix3::translation(position)*Matrix3::rotation(rotation)*Vector2(24,22);

	float tailSpeed = 10 + ((abs(velocity.x) + abs(velocity.y))/(MAX_V*2)) * 40;

	leftPs->minVelocity = Matrix3::rotation(rotation)*(Vector2(-2,0));
	rightPs->minVelocity = leftPs->minVelocity;

	leftPs->maxVelocity = velocity + Matrix3::rotation(rotation)*(Vector2(2,tailSpeed));
	rightPs->maxVelocity = leftPs->maxVelocity;

	leftPs->minPositionOffset = Matrix3::rotation(rotation)*Vector2(-2,0);
	rightPs->minPositionOffset = leftPs->minPositionOffset;
	leftPs->maxPositionOffset = Matrix3::rotation(rotation)*Vector2(2,4);
	rightPs->maxPositionOffset = leftPs->maxPositionOffset;

	unsigned int parts = 20+(int)(((abs(velocity.x) + abs(velocity.y))/(MAX_V*2) + (abs(acceleration.x) + abs(acceleration.y))/1000) * 70);

	leftPs->size = parts;
	rightPs->size = leftPs->size;

}

void PlayerShip::draw(EnhancedGraphics& g) {
	gun->draw(g);
	GameObject::draw(g);
	for (unsigned int i = 0; i < projectiles.size(); i++) {
		GameObject* p = projectiles[i];
		p->draw(g);
	}
}

inline void PlayerShip::rotate(float dt) {
	if (rotateLeftController != NULL && rotateLeftController())
		rotation -= ROT_D * dt;
	else if (rotateRightController != NULL && rotateRightController())
		rotation += ROT_D * dt;
}

inline void PlayerShip::move(float dt) {
	if (moveUpController != NULL && moveUpController())
		acceleration = Vector2(sin(rotation), -cos(rotation)) * SPEED * dt;
	else if (moveDownController != NULL && moveDownController())
		acceleration = Vector2(sin(rotation), -cos(rotation)) * -SPEED * dt;
	else { // friction
		acceleration = Vector2();
		velocity.x = velocity.x > 0 ? max(0, velocity.x - FRICTION*dt) : min(0, velocity.x + FRICTION*dt);
		velocity.y = velocity.y > 0 ? max(0, velocity.y - FRICTION*dt) : min(0, velocity.y + FRICTION*dt);
	}
}

void PlayerShip::hit(EnemyProjectile& p) {
	p;
	hp--;

	if (hp < 1)
		isDead = true;

	ExplosionParticleSystem * ps = new ExplosionParticleSystem(250);
	ps->position = position;
	ps->radial = false;
	ps->minVelocity = Vector2(-100);
	ps->maxVelocity = Vector2(100);
	ps->minLifeTime = .25f;
	ps->maxLifeTime  = .85f;
	ps->minRadius = 1;
	ps->maxRadius = 2;
	ps->startColor = AFilter(color,100);
	ps->endColor = RGBA(0,0,0,255);

	Game::particleManager->add(ps);
}

void PlayerShip::registerRotateLeft(ShipController c) { rotateLeftController = c; }
void PlayerShip::registerRotateRight(ShipController c) { rotateRightController = c; }
void PlayerShip::registerMoveUp(ShipController c) { moveUpController = c; }
void PlayerShip::registerMoveDown(ShipController c) { moveDownController = c; }
void PlayerShip::registerFire(ShipController c) { fireController = c; }