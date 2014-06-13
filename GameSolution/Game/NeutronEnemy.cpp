#include "NeutronEnemy.h"
#include "DebugMemory.h"

const float NeutronEnemy::MINION_DELAY = 0.5f;
const float NeutronEnemy::FIRE_DELAY = .5f;
const float NeutronEnemy::FIRE_CHANCE = 1;

NeutronEnemy::NeutronEnemy(GameObject* target, Vector2 pos) : target(target), Enemy(pos, Shape::generate(20,15)) {
	shrink = false;
	timer.start();
	fireTimer.start();
	points = 300;
	radius = 15;
	color = RGB(230,0,255);
	float hOffset = Math::random(-100,100);
	hueInter = new Interpolation(hOffset,360+hOffset,1.0f+Math::random(-.3f,.3f),Interpolation::easeInOutCubic,Direction::Alternate);
	float offset = Math::random(-1.57f,1.57f);
	posInter = new Interpolation(0+offset,6.28f+offset,2.0f+Math::random(-.5f,.5f));
	scaleInter = new Interpolation(.7f,1,.6f+Math::random(-.2f,.2f),Interpolation::easeInOutCubic,Direction::Alternate);
	hp = 15;
}

NeutronEnemy::~NeutronEnemy() {
	delete hueInter;
	delete posInter;
	delete scaleInter;
}

void NeutronEnemy::update(float dt) {
	GameObject::update(dt);

	rotation += 0.1f;

	posInter->update(dt);
	hueInter->update(dt);

	color = HSB((int)hueInter->getValue(),100,100);

	minions.erase(std::remove_if(minions.begin(), minions.end(), 
		[&](Enemy* p) {
			return p->isDead;
	}), minions.end());

	if (shrink) {
		if (scale <= 0) {
			for (unsigned int i = 0; i < minions.size(); i++) {
				minions.at(i)->target = target;
			}
			isDead = true;
		} else {
			scale -= .08f;
			while (minions.size() < 30) {
				EnemyMinionShip* minion = new EnemyMinionShip(this);
				minion->position = position;
				minions.push_back(minion);
				Game::enemyManager->queue.push_back(minion);
				timer.interval();
			}
		}
	} else{
		if (Game::timer.elapsed() > 3 && fireTimer.intervalElapsed() > FIRE_DELAY && Math::random(0,100) < FIRE_CHANCE) {
			Vector2 diff = (Game::player->position - position).perpCW();
			float rotation = atan2(-diff.y, -diff.x);
			EnemyProjectile* p = new EnemyProjectile(position, rotation);
			Game::enemyManager->projectiles.push_back(p);
			fireTimer.interval();
		}

		scaleInter->update(dt);
		scale = scaleInter->getValue();

		if (timer.intervalElapsed() >= MINION_DELAY && minions.size() < 20) {
			EnemyMinionShip* minion = new EnemyMinionShip(this);
			minion->position = position;
			minions.push_back(minion);
			Game::enemyManager->queue.push_back(minion);
			timer.interval();
		}
	}

}

void NeutronEnemy::draw(EnhancedGraphics& g) {
	shape.draw(g,color,position+(Vector2(-sin(posInter->getValue()),cos(posInter->getValue()))*20),scale,rotation);
	shape.draw(g,HSB((int)hueInter->getValue()+30,100,100),position+(Vector2(-sin(posInter->getValue()),cos(posInter->getValue()))*20),scale*.6f,rotation);
	shape.draw(g,HSB((int)hueInter->getValue()+60,100,100),position+(Vector2(-sin(posInter->getValue()),cos(posInter->getValue()))*20),scale*.3f,rotation);
}

bool NeutronEnemy::explode(Projectile& p) {
	ExplosionParticleSystem * ps = new ExplosionParticleSystem(120);
	ps->position = p.position;
	ps->radial = false;
	ps->minVelocity = Vector2(-70);
	ps->maxVelocity = Vector2(70);
	ps->minLifeTime = .15f;
	ps->maxLifeTime  = .5f;
	ps->minRadius = 1;
	ps->maxRadius = 2;
	ps->startColor = AFilter(p.color,180);
	ps->endColor = RGBA(0,0,0,255);

	Game::particleManager->add(ps);

	if (--hp <= 0) {
		shrink = true;
	}

	isDying = shrink;

	return shrink;
}