#ifndef DGLW_INITILIZER_HPP_
#define DGLW_INITILIZER_HPP_

#include <vector>
#include "common.hpp"

namespace dglw {

class Initializer {
   public:
      Initializer();
      void initialize();
      bool isInitialized();
      void addInitializeFunction(VoidFunction vf);


   private:
      bool is_initialized_;
      std::vector<VoidFunction> init_list_;
};

void initialize();

} /* namespace dglw */

#endif /* DGLW_INITILIZER_HPP_ */
