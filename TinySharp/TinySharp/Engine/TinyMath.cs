using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TinySharp.Engine {

    /*
     [[nodiscard]] static auto FInterpTo( T1  Current, T2 Target, T3 DeltaTime, T4 InterpSpeed )
	{
		using RetType = decltype(T1() * T2() * T3() * T4());
	
		// If no interp speed, jump to target value
		if( InterpSpeed <= 0.f )
		{
			return static_cast<RetType>(Target);
		}

		// Distance to reach
		const RetType Dist = Target - Current;

		// If distance is too small, just set the desired location
		if( FMath::Square(Dist) < UE_SMALL_NUMBER )
		{
			return static_cast<RetType>(Target);
		}

		// Delta Move, Clamp so we do not over shoot.
		const RetType DeltaMove = Dist * FMath::Clamp<RetType>(DeltaTime * InterpSpeed, 0.f, 1.f);

		return Current + DeltaMove;				
	}
     */

    public static class TinyMath {

        public const float E	   = MathF.E;
        public const float Log10E  = 0.4342945f;
        public const float Log2E   = 1.442695f;
        public const float Pi	   = MathF.PI;
        public const float PiOver2 = MathF.PI * 0.5f;
        public const float PiOver4 = MathF.PI * 0.25f;
        public const float TwoPi   = MathF.PI * 2f;
        public const float Tau	   = MathF.PI * 2f;

        public static int Clamp( int value, int min, int max ) {
            value = ( ( value > max ) ? max : value );
            value = ( ( value < min ) ? min : value );

            return value;
        }

        public static float Clamp( float value, float min, float max ) {
            value = ( ( value > max ) ? max : value );
            value = ( ( value < min ) ? min : value );

            return value;
        }

        public static TinyVector2 InterpTo( TinyVector2 current, TinyVector2 target, float delta, float speed ) {
			if ( speed <= 0.0f )
				return target;

			var distance = 0.1f; // target - current;

			if ( MathF.Sqrt( distance ) < 0.00000001f )
				return target;

			return current + target;
		}

    }

}
