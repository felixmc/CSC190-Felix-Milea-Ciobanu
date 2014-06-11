#include "NeutronEnemy.h"

const float NeutronEnemy::MINION_DELAY = 0.5f;

NeutronEnemy::NeutronEnemy(GameObject* target, Vector2 pos) : target(target), Enemy(pos, *Shape::generate(20,15)) {
	shrink = false;
	timer.start();
	points = 500;
	radius = 15;
	color = RGB(230,0,255);
	hueInter = new Interpolation(220,370,1.0f+Math::random(-.3f,.3f),Interpolation::easeInOutCubic,Direction::Alternate);
	float offset = Math::random(-1.57f,1.57f);
	posInter = new Interpolation(0+offset,6.28f+offset,2.0f+Math::random(-.5f,.5f));
	scaleInter = new Interpolation(.7f,1,.6f+Math::random(-.2f,.2f),Interpolation::easeInOutCubic,Direction::Alternate);
	hp = 25;
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
		} else
			scale -= .08f;
	} else{
		scaleInter->update(dt);
		scale = scaleInter->getValue();

		if (timer.intervalElapsed() >= MINION_DELAY && minions.size() < 20) {
			EnemyMinionShip* minion = new EnemyMinionShip(this);
			minion->position = position;
			minions.push_back(minion);
			Game::enemyManager->queue->push_back(minion);
			timer.interval();
		}
	}

}

void NeutronEnemy::draw(EnhancedGraphics& g) {
	shape.draw(g,color,position+(Vector2(-sin(posInter->getValue()),cos(posInter->getValue()))*20),scale,rotation);
	shape.draw(g,HSB((int)hueInter->getValue()+30,100,100),position+(Vector2(-sin(posInter->getValue()),cos(posInter->getValue()))*20),scale*.6f,rotation);
	shape.draw(g,HSB((int)hueInter->getValue()+60,100,100),position+(Vector2(-sin(posInter->getValue()),cos(posInter->getValue()))*20),scale*.3f,rotation);
	//shape.draw(g,RGB(255,0,0),position+(Matrix3::rotation(rotation) * Vector3(Vector2(10))),.4f);
	//shape.draw(g,RGB(0,255,0),position+(Vector2(-10,10)),.4f);
	//shape.draw(g,RGB(0,0,255),position+(Vector2(0,-10)),.4f);
}

bool NeutronEnemy::explode(Projectile& p) {
	p;

	ExplosionParticleSystem * ps = new ExplosionParticleSystem(120);
	ps->position = p.position;
	ps->radial = false;
	ps->minVelocity = Vector2(-70);
	ps->maxVelocity = Vector2(70);
	ps->minLifeTime = .15f;
	ps->maxLifeTime  = .5f;
	ps->minRadius = 1;
	ps->maxRadius = 2;
	ps->startColor = p.color;
	ps->endColor = RGBA(0,0,0,0);

	Game::particleManager->add(ps);

	if (--hp <= 0) {
		shrink = true;
	}

	isDying = shrink;

	return shrink;
}