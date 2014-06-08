#include "EnemyMinionShip.h"
#include "ExplosionParticleSystem.h"
#include "Game.h"

//static Vector2 diamond[] = {
//	Vector2(0,-10),Vector2(10,0),
//	Vector2(0,10),Vector2(-10,0)
//};

static Vector2 diamond[] = {
	Vector2(0,3.6f),Vector2(-6,-3.6f),Vector2(6,-3.6f)
};

const float EnemyMinionShip::PING_DELAY = .250f;
const float EnemyMinionShip::SPEED = 200;

EnemyMinionShip::EnemyMinionShip() : Enemy(Vector2(200,200), *SHAPE(diamond)) {
	radius = 10;
	mu = 0;
	muInc = 0;
	color = RGB(225+Math::random(-45,40),128+Math::random(-40,40),Math::random(0,50));

	timer.start();
	targetPosition = Game::player->position;
}

void EnemyMinionShip::update(float dt) {
	GameObject::update(dt);
	
	//rotation += 0.02f;
	Vector2 diff = (targetPosition - position).perpCCW();
	rotation = atan2(-diff.y, -diff.x);

	if (muInc == 0 || timer.intervalElapsed() >= (PING_DELAY + Math::random(-PING_DELAY/8,PING_DELAY/8))) {
		muInc = 1;
		timer.interval();

		if (position.distance(targetPosition) < 120+Math::random(-10,10))
			if (Math::random(0,10) >= 5)
				velocity = velocity.perpCCW();
			else
				velocity = velocity.perpCW();
		else {
			start = position;
			targetPosition = Game::player->position;

			Vector2 diff = (targetPosition - start).normalize() * (SPEED+Math::random(-50,50));

			velocity = diff + Vector2(Math::random(-SPEED/5,SPEED/5),Math::random(-SPEED/5,SPEED/5));
		}
	}



	//position = Vector2(cosInter(start.x,targetPosition.x,mu), cosInter(start.y,targetPosition.y,mu));
	//mu += (muInc * dt);
}

inline float EnemyMinionShip::inter(float a, float b, float mu) {
	return ((1 - mu) * a) + (mu * b);
}

inline float EnemyMinionShip::cosInter(float a, float b, float mu) {
	float mu2 = (1-cos(mu*Engine::Math::PI))/2;
	return (a*(1-mu2)+b*mu2);
}

inline void EnemyMinionShip::draw(EnhancedGraphics& g) {
	GameObject::draw(g);
}

void EnemyMinionShip::explode(Projectile& pro) {
	isDead = true;
	pro;
	ExplosionParticleSystem * ps = new ExplosionParticleSystem(120);
	ps->position = position;
	ps->radial = false;
	ps->minVelocity = Vector2(-70);
	ps->maxVelocity = Vector2(70);
	ps->minLifeTime = .15f;
	ps->maxLifeTime  = .5f;
	ps->minRadius = 1;
	ps->maxRadius = 2;
	ps->startColor = RGBA(GetRValue(color),GetGValue(color),GetBValue(color),170);
	ps->endColor = RGBA(GetRValue(color),GetGValue(color),GetBValue(color),255);
		
	Game::particleManager->add(ps);
}