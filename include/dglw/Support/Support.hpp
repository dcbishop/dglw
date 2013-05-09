#ifndef SUPPORT_HPP_
#define SUPPORT_HPP_

#include <memory>

namespace dglw {

template<typename T, typename ...Args>
std::unique_ptr<T> make_unique( Args&& ...args )
{
       return std::unique_ptr<T>( new T( std::forward<Args>(args)... ) );
}

} /* namespace dglw */

#endif /* SUPPORT_HPP_ */
