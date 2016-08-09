/**
 *  file: DeleteObject.hh
 *  date: 2016.01.17
 */

#ifndef DELETE_OBJECT_HH
#define DELETE_OBJECT_HH

#include <utility>

//_____________________________________________________________________
struct DeleteObject
{
  template<typename Type>
  void operator ()( Type*& object ) const
  {
    if(object){
      delete object;
      object = NULL;
    }
    return;
  }
    
  template<typename Type1, typename Type2>
  void operator ()( std::pair<Type1, Type2*>& object ) const
  {
    operator ()(object.second);
    return;
  }

};

#endif
