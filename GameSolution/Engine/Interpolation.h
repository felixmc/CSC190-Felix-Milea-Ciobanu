#ifndef _ENGINE_INTERPOLATION_H_
#define _ENGINE_INTERPOLATION_H_

#include "EngineMath.h"
#include "DebugMemory.h"
#include <limits>
#include <cmath>

namespace Engine {

	typedef float (*InterpolationMethod)(float,float,float,float);
	enum Direction { Normal, Reverse, Alternate, AlternateReverse };

	class Interpolation {
		float currentTime, value;
		float start, end, duration, repeat;
		int its;
		InterpolationMethod fn;
		Direction direction;

		
	public:
		Interpolation( float start, float end, float duration = 120.0f,  InterpolationMethod fn = linear,
			Direction direction = Normal, float repeat = std::numeric_limits<float>::infinity()) :
			start(start), end(end), duration(duration), repeat(repeat), fn(fn), direction(direction) {
				currentTime = 0;
				its = 0;
				value = start;
		}

		inline float getValue() {
			return value;
		}

		void update(float dt) {
			if ( its < repeat ) {
				float val0 = 0, val1 = 0;

				switch(direction) {
				case Normal : val0 = start; val1 = end; break;
				case Reverse : val0 = end; val1 = start; break;
				case Alternate : if ( its % 2 == 0 ) { val0 = start; val1 = end; } else { val0 = end; val1 = start; } break;
				case AlternateReverse : if ( its % 2 != 0 ) { val0 = start; val1 = end; } else { val0 = end; val1 = start; } break;
				}

				//float mu = currentTime / duration;
				value = fn( currentTime, val0, val1 - val0, duration );

				if ( currentTime >= duration ) {
					its++;
					currentTime = 0;
				} else {
					currentTime += dt;
				}

			}
		}

		static float linear(float t, float b, float c, float d) {
			return ( c * ( t / d ) ) + b;
		}

		static float easeInQuad(float t, float b, float c, float d) {
			float mu = t / d;
			return ( c * mu * mu ) + b;
		}

		static float easeOutQuad(float t, float b, float c, float d) {
			float mu = t / d;
			return ( -c * mu * ( mu - 2 ) ) + b;
		}

		static float easeInOutQuad(float t, float b, float c, float d) {
			float mu = t / ( d / 2 );
			if ( mu < 1 ) return ( ( c / 2 ) * mu * mu ) + b;
			mu = mu - 1;
			return ( ( -c / 2 ) * ( ( mu * ( mu - 2 ) ) - 1 ) ) + b;
		}

		static float easeInCubic(float t, float b, float c, float d) {
			float mu = t / d;
			return ( c * mu * mu * mu ) + b;
		}

		static float easeOutCubic(float t, float b, float c, float d) {
			float mu = ( t / d ) - 1;
			return ( c * ( ( mu * mu * mu ) + 1 ) ) + b;
		}

		static float easeInOutCubic(float t, float b, float c, float d) {
			float mu = t / ( d / 2 );
			if ( mu < 1 ) return ( ( c / 2 ) * ( mu * mu * mu ) ) + b;
			mu = mu - 2;
			return ( ( c / 2 ) * ( ( mu * mu * mu ) + 2 ) ) + b;
		}

		static float easeInQuart(float t, float b, float c, float d) {
			float mu = t / d;
			return ( c * mu * mu * mu * mu ) + b;
		}

		static float easeOutQuart(float t, float b, float c, float d) {
			float mu = ( t / d ) - 1;
			return ( -c * ( ( mu * mu * mu * mu ) - 1 ) ) + b;
		}

		static float easeInOutQuart(float t, float b, float c, float d) {
			float mu = t / ( d / 2 );
			if ( mu < 1 ) return ( ( c / 2 ) * ( mu * mu * mu * mu ) ) + b;
			mu = mu - 2;
			return ( ( c / -2 ) * ( ( mu * mu * mu * mu ) - 2 ) ) + b;
		}

		static float easeInQuint(float t, float b, float c, float d) {
			float mu = t / d;
			return ( c * mu * mu * mu * mu * mu ) + b;
		}

		static float easeOutQuint(float t, float b, float c, float d) {
			float mu = ( t / d ) - 1;
			return ( c * ( ( mu * mu * mu * mu * mu ) + 1 ) ) + b;
		}

		static float easeInOutQuint(float t, float b, float c, float d) {
			float mu = t / ( d / 2 );
			if ( mu < 1 ) return ( ( c / 2 ) * ( mu * mu * mu * mu * mu ) ) + b;
			mu = mu - 2;
			return ( ( c / 2 ) * ( ( mu * mu * mu * mu * mu ) + 2 ) ) + b;
		}

		static float easeInSine(float t, float b, float c, float d) {
			return ( -c * cos( ( t / d ) * ( Engine::Math::PI / 2 ) ) ) + c + b;
		}

		static float easeOutSine(float t, float b, float c, float d) {
			return ( c * sin( ( t / d ) * ( Engine::Math::PI / 2 ) ) ) + b;
		}

		static float easeInOutSine(float t, float b, float c, float d) {
			return ( ( -c / 2 ) * ( cos( Engine::Math::PI * ( t / d ) ) - 1 ) ) + b;
		}

		static float easeInExpo(float t, float b, float c, float d) {
			return ( c * (float)pow( 2, 10 * ( ( t / d ) - 1 ) ) ) + b;
		}

		static float easeOutExpo(float t, float b, float c, float d) {
			return ( c * ( -(float)pow( 2, -10 * ( t / d ) ) + 1 ) ) + b;
		}

		static float easeInOutExpo(float t, float b, float c, float d) {
			float mu = t / ( d / 2 );
			if ( mu < 1 ) return ( ( c / 2 ) * (float)pow( 2, 10 * ( mu - 1 ) ) ) + b;
			mu = mu - 1;
			return ( ( c / 2 ) * ( (float)pow( 2, -10 * mu ) + 2 ) ) + b;
		}

		static float easeInCirc(float t, float b, float c, float d) {
			float mu = t / d;
			return ( -c * ( sqrt( 1 - ( mu * mu ) ) - 1 ) ) + b;
		}

		static float easeOutCirc(float t, float b, float c, float d) {
			float mu = ( t / d ) - 1;
			return ( c * sqrt( 1 - ( mu * mu ) ) ) + b;
		}

		static float easeInOutCirc(float t, float b, float c, float d) {
			float mu = t / ( d / 2 );
			if ( mu < 1 ) return ( ( c / -2 ) * ( sqrt( 1 - ( mu * mu ) ) - 1 ) ) + b;
			mu = mu - 2;
			return ( ( c / 2 ) * ( sqrt( 1 - ( mu * mu ) ) + 1 ) ) + b;
		}

		static float easeInBack(float t, float b, float c, float d) {
			float mu = t / d;
			float s = 1.70158f;
			return ( c * mu * mu * ( ( ( s + 1 ) * mu ) - s ) ) + b;
		}

		static float easeOutBack(float t, float b, float c, float d) {
			float mu = ( t / d ) - 1;
			float s = 1.70158f;
			return ( c * ( mu * mu * ( ( ( s + 1 ) * mu ) + s ) + 1 ) ) + b;
		}

		static float easeInOutBack(float t, float b, float c, float d) {
			float mu = t / ( d / 2 );
			float s = 1.70158f * 1.525f;
			if ( mu < 1 ) return ( ( c / 2 ) * ( mu * mu * ( ( ( s + 1 ) * mu ) - s ) ) ) + b;
			mu = mu - 2;
			return ( ( c / 2 ) * ( mu * mu * ( ( ( s + 1 ) * mu ) + s ) + 2 ) ) + b;
		}

		static float easeOutBounce(float t, float b, float c, float d) {
			float mu = t / d;
			if ( mu < ( 1 / 2.75 ) ) {
				return c * ( 7.5625f * mu * mu ) + b;
			} else if ( t < ( 2 / 2.75 ) ) {
				mu = mu - ( 1.5f / 2.75f );
				return c * ( 7.5625f * mu * mu + .75f ) + b;
			} else if ( t < ( 2.5 / 2.75 ) ) {
				mu = mu - ( 2.25f / 2.75f );
				return c * ( 7.5625f * mu * mu + .9375f ) + b;
			} else {
				mu = mu - ( 2.625f / 2.75f );
				return c * ( 7.5625f * mu * mu + .984375f ) + b;
			}
		}

		static float easeInBounce(float t, float b, float c, float d) {
			return c - easeOutBounce( d - t, 0, c, d ) + b;
		}

		static float easeInOutBounce(float t, float b, float c, float d) {
			if ( t < d / 2 ) return easeInBounce( t * 2, 0, c, d ) / 2 + b;
			return ( easeOutBounce( t * 2 - d, 0, c, d ) / 2 ) + ( c / 2 ) + b;
		}
	};

}

#endif