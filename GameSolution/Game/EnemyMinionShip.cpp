#include "DebugMemory.h"
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

const float EnemyMinionShip::PING_DELAY = .200f;
const float EnemyMinionShip::SPEED = 200;

EnemyMinionShip::EnemyMinionShip(GameObject* target) : Enemy(Vector2(200,200), SHAPE(diamond)), target(target) {
	radius = 10;
	mu = 0;
	muInc = 0;
	points = 10;

	hueInter = new Interpolation(-40,50,.8f+Math::random(-.2f,.2f),Interpolation::easeInOutCirc,Engine::Direction::Alternate);

	timer.start();
	targetPosition = target->position;
}

EnemyMinionShip::~EnemyMinionShip() {
	delete hueInter;
}

void EnemyMinionShip::update(float dt) {
	GameObject::update(dt);
	
	hueInter->update(dt);
	color = HSB((int)hueInter->getValue()+(target == &Game::player ? 0 : -100),100,100);
	Vector2 diff = (targetPosition - position).perpCCW();
	rotation = atan2(-diff.y, -diff.x);

	if (muInc == 0 || timer.intervalElapsed() >= (PING_DELAY + Math::random(-PING_DELAY/10,PING_DELAY/10))) {
		muInc = 1;
		timer.interval();

		if (velocity == Vector2()) {
			velocity = Vector2(Math::random(-10,10),Math::random(-10,10)).normalize() * (SPEED+Math::random(-50,50));
		} else if (position.distance(targetPosition) < 60+Math::random(-10,10))
			if (Math::random(0,10) >= 5)
				velocity = velocity.perpCCW();
			else
				velocity = velocity.perpCW();
		else {
			start = position;
			targetPosition = target->position;

			Vector2 diff = (targetPosition - start).normalize() * (SPEED+Math::random(-50,50));

			velocity = diff + Vector2(Math::random(-SPEED/5,SPEED/5),Math::random(-SPEED/5,SPEED/5));
		}
	}

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

bool EnemyMinionShip::explode(Projectile& pro) {
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
		
	Game::particleManager.add(ps);

	return isDead;
}