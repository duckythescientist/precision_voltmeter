#include <fp64lib.h>

class Double {
  public:
    Double()        { x = 0ULL; }
    Double( double f )    { x = fp64_sd( f ); }
    Double( float f )   { x = fp64_sd( f ); }
    Double( int16_t n )   { x = fp64_int16_to_float64( n ); }
    Double( uint16_t n )  { x = fp64_uint16_to_float64( n ); }
    Double( int32_t n )  { x = fp64_int32_to_float64( n ); }
    Double( uint32_t n )  { x = fp64_uint32_to_float64( n ); }
    Double( const Double& d ) { x = d.x; }
    Double( float64_t f ) { x = f; }
    const char* toString() { 
      return fp64_to_string( x, 17, 15);
      }
    Double operator+=( const Double& y ) {
      this->x = fp64_add( this->x, y.x );
      return( *this );
      }
    Double operator+( const Double& y ) {
      Double res;
      res.x = fp64_add( this->x, y.x );
      return( res );
      }
    Double operator-=( const Double& y ) {
      this->x = fp64_sub( this->x, y.x );
      return( *this );
      }
    Double operator-( const Double& y ) {
      Double res;
      res.x = fp64_sub( this->x, y.x );
      return( res );
      }
    Double operator*=( const Double& y ) {
      this->x = fp64_mul( this->x, y.x );
      return( *this );
      }
    Double operator*( const Double& y ) {
      Double res;
      res.x = fp64_mul( this->x, y.x );
      return( res );
      }
    Double operator/=( const Double& y ) {
      this->x = fp64_div( this->x, y.x );
      return( *this );
      }
    Double operator/( const Double& y ) {
      Double res;
      res.x = fp64_div( this->x, y.x );
      return( res );
      }
    Double operator%=( const Double& y ) {
      this->x = fp64_fmod( this->x, y.x );
      return( *this );
      }
    Double operator%( const Double &y ) {
      Double res;
      res.x = fp64_fmod( this->x, y.x );
      return( res );
      }
    operator float64_t() {
      return x;
    }
    operator float() {
      return fp64_ds(x);
    }
   private:
      float64_t x;
};
