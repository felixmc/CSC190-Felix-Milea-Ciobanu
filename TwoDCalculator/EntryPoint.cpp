#include "RenderUI.h"
//#include "Engine.h"

#include "Vector2.h"
#include "Vector3.h"
#include "Matrix2.h"
#include "Matrix3.h"

using namespace Engine;

static Vector2 left, right, result,
			   original, normal, cw, ccw,
			   p, n,
			   vector1, vector2, projection, rejection,
			   a, b, aMinusB, lerpA, lerpB, lerpResult, vmm2r;

static Vector3 afResults[5]; 

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
	if (!data.projectOntoLeftVector) {
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

void linearTransformationCallback(const LinearTransformationData& data) {
	vmm2r = Matrix2(Vector2(data.m00, data.m01), Vector2(data.m10, data.m11)) * Vector2(data.v0, data.v1);
}

void affineTransformationCallback(const AffineTransformationData& data) {
	Matrix3 m3 = Matrix3(data.data[0],data.data[1],data.data[2],data.data[3],data.data[4],data.data[5],data.data[6],data.data[7],data.data[8]);

	for(int i = 0; i < 5; i++) {
		int offset = (i * 3);
		afResults[i] = m3 * Vector3(data.data[9 + offset], data.data[10 + offset], data.data[11 + offset]);
	}

}

static float scale = .5f;

static const Vector2 lines[8] = { Vector2(-scale,-scale),Vector2(-scale,scale),Vector2(-scale,scale),Vector2(scale,scale),Vector2(scale,scale),Vector2(scale,-scale),Vector2(scale,-scale),Vector2(-scale,-scale) };
static Matrix3 matrices[10];
static Matrix3 currentM;

void matrixTransformCallback2D(const MatrixTransformData2D& data) {
	matrices[data.selectedMatrix] = Matrix3::scaleX(data.scaleX) * Matrix3::scaleY(data.scaleY)
		* Matrix3::rotation(data.rotate) * Matrix3::translation(data.translateX, data.translateY);
	
	currentM = Matrix3();

	for(int i = 0; i < 10; i++) {
		currentM = currentM * matrices[i];
	}
}

int main(int argc, char* argv[])
{
	//Engine::Init();
	RenderUI renderUI;

	renderUI.setBasicVectorEquationData(basicEquationCalback, &left.x, &right.x, &result.x);
	renderUI.setPerpendicularData(&original.x, &normal.x, &cw.x, &ccw.x, perpendicularCallback);
	renderUI.setLineEquationData(&p.x, &n.x, &d, lineEquationCallback);
	renderUI.setDotProductData(&vector1.x, &vector2.x, &projection.x, &rejection.x, dotProductCallback);
	renderUI.setLerpData(&a.x, &b.x, &aMinusB.x, &lerpA.x, &lerpB.x, &lerpResult.x, lerpCallback);
	renderUI.setLinearTransformationData(&vmm2r.x, linearTransformationCallback);
	renderUI.setAffineTransformationData(&afResults[0].x, affineTransformationCallback);
	renderUI.set2DMatrixVerticesTransformData(&lines[0].x, 4, &matrices[0].x1, &currentM.x1, matrixTransformCallback2D);

	if( ! renderUI.initialize(argc, argv))
		return -1;
	else
		return renderUI.run();
}