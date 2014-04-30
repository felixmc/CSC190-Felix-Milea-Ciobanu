#include "RenderUI.h"
#include "Engine.h"

#include "Vector2.h"

static Vector2 left, right, result,
			   original, normal, cw, ccw,
			   p, n,
			   vector1, vector2, projection, rejection,
			   a, b, aMinusB, lerpA, lerpB, lerpResult;
			   //,tResult;

static float d;

void basicEquationCalback(const BasicVectorEquationInfo& data) {
	left = Vector2(data.x1, data.y1) * data.scalar1;
	right = Vector2(data.x2, data.y2) * data.scalar2;
	result = data.add ? left + right : left - right;
}

void perpendicularCallback(const PerpendicularData& data) {
	original = Vector2(data.x, data.y);
	normal = original.normalize();
	cw = original.perpCW();
	ccw = original.perpCCW();
}

void lineEquationCallback(const LineEquationData& data) {
	d = data.d;
	n = Vector2(data.n_i, data.n_j).normalize();
	p = Vector2(data.p_x, (d - (n.x * data.p_x)) / n.y);
}

void dotProductCallback(const DotProductData& data) {
	vector1 = Vector2(data.v1i, data.v1j);
	vector2 = Vector2(data.v2i, data.v2j);
	if (data.projectOntoLeftVector) {
		projection = (vector1.dot(vector2) / vector2.lengthSquared()) * vector2;
		rejection = vector1 - projection;
	} else {
		projection = (vector2.dot(vector1) / vector1.lengthSquared()) * vector1;
		rejection = vector2 - projection;
	}
}

void lerpCallback(const LerpData& data) {
	a = Vector2(data.a_i, data.a_j);
	b = Vector2(data.b_i, data.b_j);
	aMinusB = b - a;
	lerpA = (1 - data.beta) * a;
	lerpB = (data.beta) * b;
	lerpResult = lerpA + lerpB;
}

//void linearTransformationCallback(const LinearTransformationData& data) {
//
//}

int main(int argc, char* argv[])
{
	Engine::Init();
	RenderUI renderUI;

	renderUI.setBasicVectorEquationData(basicEquationCalback, &left.x, &right.x, &result.x);
	renderUI.setPerpendicularData(&original.x, &normal.x, &cw.x, &ccw.x, perpendicularCallback);
	renderUI.setLineEquationData(&p.x, &n.x, &d, lineEquationCallback);
	renderUI.setDotProductData(&vector1.x, &vector2.x, &projection.x, &rejection.x, dotProductCallback);
	renderUI.setLerpData(&a.x, &b.x, &aMinusB.x, &lerpA.x, &lerpB.x, &lerpResult.x, lerpCallback);
	//renderUI.setLinearTransformationData(&tResult.x, linearTransformationCallback);

	if( ! renderUI.initialize(argc, argv))
		return -1;
	else
		return renderUI.run();
}