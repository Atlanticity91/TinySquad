using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TinySharp.Engine {
    
    public struct TinyVector4 {

        public float X;
        public float Y;
        public float Z;
        public float W;

        public TinyVector4( float x, float y, float z, float w ) {
            X = x;
            Y = y;
            Z = z;
            W = w;
        }

    }

}
