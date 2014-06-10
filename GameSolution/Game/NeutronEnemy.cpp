#include "NeutronEnemy.h"

const float NeutronEnemy::MINION_DELAY = 0.5f;

NeutronEnemy::NeutronEnemy(GameObject* target, Vector2 pos) : target(target), Enemy(pos, *Shape::generate(20,15)) {
	shrink = false;
	timer.start();
	points = 250;
	radius = 20;
	color = RGB(230,0,255);
	hueInter = new Interpolation(0,360,2.5f);
	hp = 5;
}

void NeutronEnemy::update(float dt) {
	GameObject::update(dt);

	rotation += 0.1f;

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
	} else if (timer.intervalElapsed() >= MINION_DELAY && minions.size() < 25) {
		EnemyMinionShip* minion = new EnemyMinionShip(this);
		minions.push_back(minion);
		Game::enemyManager->queue->push_back(minion);
		timer.interval();
	}

}

void NeutronEnemy::draw(EnhancedGraphics& g) {
	GameObject::draw(g);
	//shape.draw(g,RGB(255,0,0),position+(Matrix3::rotation(rotation) * Vector3(Vector2(10))),.4f);
	//shape.draw(g,RGB(0,255,0),position+(Vector2(-10,10)),.4f);
	//shape.draw(g,RGB(0,0,255),position+(Vector2(0,-10)),.4f);

}

void NeutronEnemy::explode(Projectile& p) {
	p;
	if (--hp <= 0) {
		shrink = true;
	}
}