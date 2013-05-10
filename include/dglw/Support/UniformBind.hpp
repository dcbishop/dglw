#ifndef DGLW_UNIFORMBIND_HPP_
#define DGLW_UNIFORMBIND_HPP_

#include "OpenGL/Program.hpp"

namespace dglw {

template<class T>
class UniformBind {
   public:
      UniformBind(const ProgramPtr& program, const UniformInfo ui) {
         program_ = program;
         info_ = ui;
      }

      void set(const T& data) {
         DEBUG_M("The index: %d", info_.index);
         if(info_.index < 0) {
            return;
         }
         program_->uniform(data, info_.index);
      }

      typedef std::shared_ptr< UniformBind<T> > Ptr;

   private:
      UniformInfo info_;
      ProgramPtr program_; 
};

template <class T>
UniformBind<T> makeUniformBind(const ProgramPtr& program, const std::string name) {
   
   UniformInfo ui = program->getUniformInfo(name);
   DEBUG_M("making UniformBind with index %d", ui.index);

   UniformBind<T> ub(program, ui);
   return ub;
}

} /* namespace dglw  */

#endif /* DGLW_UNIFORMBIND_HPP_ */
