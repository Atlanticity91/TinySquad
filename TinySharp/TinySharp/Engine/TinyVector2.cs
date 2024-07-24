using System;
using System.Runtime.CompilerServices;

namespace TinySharp.Engine {
    
    public struct TinyVector2 : IEquatable<TinyVector2> {

        public static readonly TinyVector2 Unit  = new TinyVector2( 1.0f, 1.0f );
        public static readonly TinyVector2 UnitX = new TinyVector2( 1.0f, 0.0f );
        public static readonly TinyVector2 UnitY = new TinyVector2( 0.0f, 1.0f );

        public float X;
        public float Y;

        public TinyVector2( )
            : this( 0.0f, 0.0f ) 
        { }

        public TinyVector2( float scalar )
            : this( scalar, scalar ) 
        { }

        public TinyVector2( float x, float y ) {
            X = x;
            Y = y;
        }

        public static TinyVector2 Add( TinyVector2 value1, TinyVector2 value2 ) {
            value1.X += value2.X;
            value1.Y += value2.Y;

            return value1;
        }

        public static void Add( ref TinyVector2 value1, ref TinyVector2 value2, out TinyVector2 result ) {
            result.X = value1.X + value2.X;
            result.Y = value1.Y + value2.Y;
        }

        public static TinyVector2 Divide( TinyVector2 value1, TinyVector2 value2 ) {
            value1.X /= value2.X;
            value1.Y /= value2.Y;

            return value1;
        }

        public static void Divide( ref TinyVector2 value1, ref TinyVector2 value2, out TinyVector2 result ) {
            result.X = value1.X / value2.X;
            result.Y = value1.Y / value2.Y;
        }

        public static TinyVector2 Divide( TinyVector2 value1, float divider ) {
            float num = 1f / divider;

            value1.X *= num;
            value1.Y *= num;

            return value1;
        }

        public static void Divide( ref TinyVector2 value1, float divider, out TinyVector2 result ) {
            float num = 1f / divider;

            result.X = value1.X * num;
            result.Y = value1.Y * num;
        }

        public static TinyVector2 Multiply( TinyVector2 value1, TinyVector2 value2 ) {
            value1.X *= value2.X;
            value1.Y *= value2.Y;

            return value1;
        }

        public static void Multiply( ref TinyVector2 value1, ref TinyVector2 value2, out TinyVector2 result ) {
            result.X = value1.X * value2.X;
            result.Y = value1.Y * value2.Y;
        }

        public static TinyVector2 Multiply( TinyVector2 value1, float scaleFactor ) {
            value1.X *= scaleFactor;
            value1.Y *= scaleFactor;

            return value1;
        }

        public static void Multiply( ref TinyVector2 value1, float scaleFactor, out TinyVector2 result ) {
            result.X = value1.X * scaleFactor;
            result.Y = value1.Y * scaleFactor;
        }

        public void Ceiling( ) {
            X = MathF.Ceiling( X );
            Y = MathF.Ceiling( Y );
        }

        public static TinyVector2 Subtract( TinyVector2 value1, TinyVector2 value2 ) {
            value1.X -= value2.X;
            value1.Y -= value2.Y;

            return value1;
        }

        public static void Subtract( ref TinyVector2 value1, ref TinyVector2 value2, out TinyVector2 result ) {
            result.X = value1.X - value2.X;
            result.Y = value1.Y - value2.Y;
        }

        public static TinyVector2 Ceiling( TinyVector2 value ) {
            value.X = MathF.Ceiling( value.X );
            value.Y = MathF.Ceiling( value.Y );

            return value;
        }

        public static void Ceiling( ref TinyVector2 value, out TinyVector2 result ) {
            result.X = MathF.Ceiling( value.X );
            result.Y = MathF.Ceiling( value.Y );
        }

        public void Floor( ) {
            X = MathF.Floor( X );
            Y = MathF.Floor( Y );
        }

        public static TinyVector2 Floor( TinyVector2 value ) {
            value.X = MathF.Floor( value.X );
            value.Y = MathF.Floor( value.Y );

            return value;
        }

        public static void Floor( ref TinyVector2 value, out TinyVector2 result ) {
            result.X = MathF.Floor( value.X );
            result.Y = MathF.Floor( value.Y );
        }

        public void Round( ) {
            X = MathF.Round( X );
            Y = MathF.Round( Y );
        }

        public static TinyVector2 Round( TinyVector2 value ) {
            value.X = MathF.Round( value.X );
            value.Y = MathF.Round( value.Y );

            return value;
        }

        public static void Round( ref TinyVector2 value, out TinyVector2 result ) {
            result.X = MathF.Round( value.X );
            result.Y = MathF.Round( value.Y );
        }

        public static TinyVector2 Clamp( TinyVector2 value1, TinyVector2 min, TinyVector2 max ) {
            float x = TinyMath.Clamp( value1.X, min.X, max.X );
            float y = TinyMath.Clamp( value1.Y, min.Y, max.Y );

            return new TinyVector2( x, y );
        }

        public static void Clamp( ref TinyVector2 value1, ref TinyVector2 min, ref TinyVector2 max, out TinyVector2 result ) {
            result.X = TinyMath.Clamp( value1.X, min.X, max.X );
            result.Y = TinyMath.Clamp( value1.Y, min.Y, max.Y );
        }

        public static float Distance( TinyVector2 value1, TinyVector2 value2 ) {
            float num  = value1.X - value2.X;
            float num2 = value1.Y - value2.Y;

            return MathF.Sqrt( num * num + num2 * num2 );
        }

        public static void Distance( ref TinyVector2 value1, ref TinyVector2 value2, out float result ) {
            float num  = value1.X - value2.X;
            float num2 = value1.Y - value2.Y;

            result = MathF.Sqrt( num * num + num2 * num2 );
        }

        public static float DistanceSquared( TinyVector2 value1, TinyVector2 value2 ) {
            float num  = value1.X - value2.X;
            float num2 = value1.Y - value2.Y;

            return num * num + num2 * num2;
        }

        public static void DistanceSquared( ref TinyVector2 value1, ref TinyVector2 value2, out float result ) {
            float num  = value1.X - value2.X;
            float num2 = value1.Y - value2.Y;

            result = num * num + num2 * num2;
        }

        public float Length( )
            => MathF.Sqrt( X * X + Y * Y );

        public float LengthSquared( )
            => X * X + Y * Y;

        public static TinyVector2 Negate( TinyVector2 value ) {
            value.X = 0f - value.X;
            value.Y = 0f - value.Y;

            return value;
        }

        public static void Negate( ref TinyVector2 value, out TinyVector2 result ) {
            result.X = 0f - value.X;
            result.Y = 0f - value.Y;
        }

        public static float Dot( TinyVector2 value1, TinyVector2 value2 ) 
            => value1.X * value2.X + value1.Y * value2.Y;

        public static void Dot( ref TinyVector2 value1, ref TinyVector2 value2, out float result ) 
            => result = value1.X * value2.X + value1.Y * value2.Y;

        public void Normalize( ) {
            float num = 1f / MathF.Sqrt(X * X + Y * Y);

            X *= num;
            Y *= num;
        }

        public static TinyVector2 Normalize( TinyVector2 value ) {
            float num = 1f / MathF.Sqrt(value.X * value.X + value.Y * value.Y);

            value.X *= num;
            value.Y *= num;

            return value;
        }

        public static void Normalize( ref TinyVector2 value, out TinyVector2 result ) {
            float num = 1f / MathF.Sqrt(value.X * value.X + value.Y * value.Y);

            result.X = value.X * num;
            result.Y = value.Y * num;
        }

        public static TinyVector2 Reflect( TinyVector2 vector, TinyVector2 normal ) {
            float num = 2f * (vector.X * normal.X + vector.Y * normal.Y);

            TinyVector2 result = default(TinyVector2);

            result.X = vector.X - normal.X * num;
            result.Y = vector.Y - normal.Y * num;

            return result;
        }

        public static void Reflect( ref TinyVector2 vector, ref TinyVector2 normal, out TinyVector2 result ) {
            float num = 2f * (vector.X * normal.X + vector.Y * normal.Y);

            result.X = vector.X - normal.X * num;
            result.Y = vector.Y - normal.Y * num;
        }

        public override int GetHashCode( ) 
            => ( X.GetHashCode( ) * 397 ) ^ Y.GetHashCode( );

        public override string ToString( ) 
            => "{X:" + X + " Y:" + Y + "}";

        public TinyPoint ToPoint( )
            => new TinyPoint( (int)X, (int)Y );

        public TinyVector3 ToVector3( )
            => new TinyVector3( X, Y, 0.0f );

        public TinyVector4 ToVector4( )
            => new TinyVector4( X, Y, 0.0f, 1.0f );

        public override bool Equals( object obj ) 
            => obj is TinyVector2 ? Equals( (TinyVector2)obj ) : false;

        public bool Equals( TinyVector2 other )
            => X == other.X && Y == other.Y;

        public static TinyVector2 operator-( TinyVector2 value ) {
            value.X = 0f - value.X;
            value.Y = 0f - value.Y;

            return value;
        }

        public static TinyVector2 operator +( TinyVector2 value1, TinyVector2 value2 ) {
            value1.X += value2.X;
            value1.Y += value2.Y;

            return value1;
        }

        public static TinyVector2 operator -( TinyVector2 value1, TinyVector2 value2 ) {
            value1.X -= value2.X;
            value1.Y -= value2.Y;

            return value1;
        }

        public static TinyVector2 operator *( TinyVector2 value1, TinyVector2 value2 ) {
            value1.X *= value2.X;
            value1.Y *= value2.Y;

            return value1;
        }

        public static TinyVector2 operator *( TinyVector2 value, float scaleFactor ) {
            value.X *= scaleFactor;
            value.Y *= scaleFactor;

            return value;
        }

        public static TinyVector2 operator *( float scaleFactor, TinyVector2 value ) {
            value.X *= scaleFactor;
            value.Y *= scaleFactor;

            return value;
        }

        [MethodImpl( MethodImplOptions.AggressiveInlining )]
        public static TinyVector2 operator /( TinyVector2 value1, TinyVector2 value2 ) {
            value1.X /= value2.X;
            value1.Y /= value2.Y;

            return value1;
        }

        [MethodImpl( MethodImplOptions.AggressiveInlining )]
        public static TinyVector2 operator /( TinyVector2 value1, float divider ) {
            float num = 1f / divider;

            value1.X *= num;
            value1.Y *= num;

            return value1;
        }

        public static bool operator ==( TinyVector2 value1, TinyVector2 value2 ) 
            => value1.X == value2.X && value1.Y == value2.Y;

        public static bool operator !=( TinyVector2 value1, TinyVector2 value2 ) 
            => value1.X != value2.X || value1.Y != value2.Y;

    }

}
