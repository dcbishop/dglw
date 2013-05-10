#ifndef DGLW_RESOURCEMANAGER_HPP_
#define DGLW_RESOURCEMANAGER_HPP_

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <tuple> 
#include <boost/filesystem.hpp>

#include "dglw.hpp"

namespace dglw {
using namespace std;
typedef unordered_map<string, shared_ptr<Shader>> ShaderMap;
typedef unordered_map<string, ProgramPtr> ProgramMap;

class ResourceManager {
   public:
      ResourceManager();

      const ProgramPtr& getVFProgram(const string& vertfile, const string& fragfile);
      const shared_ptr<Shader>& getShader(const string& filename, const dglw::Shader::Type& type);
      
      const shared_ptr<Shader>& getVertexShader(const string& filename);
      const shared_ptr<Shader>& getFragmentShader(const string& filename);

      const ProgramPtr& getShaderProgram(const string& filename);

   private:
      vector<boost::filesystem::path> findDataPaths_();
      boost::filesystem::path findImageFile_(const boost::filesystem::path& filename);
      boost::filesystem::path findShaderFile_(const boost::filesystem::path& filename);
      vector<char> readIntoVector_(const boost::filesystem::path& filename);

      unique_ptr<Shader> loadShader_(const boost::filesystem::path& filename, const Shader::Type& type);

      ShaderMap shaders_;
      ProgramMap programs_;

      vector<boost::filesystem::path> hardcoded_data_paths;
      vector<boost::filesystem::path> data_paths_;
};

typedef shared_ptr<ResourceManager> ResourceManagerPtr;

} /* namespace dglw */

#endif /* DGLW_RESOURCEMANAGER_HPP_ */
