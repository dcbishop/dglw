#ifndef DGLW_RESOURCEMANAGER_HPP_
#define DGLW_RESOURCEMANAGER_HPP_

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <tuple> 
#include <boost/filesystem.hpp>

#include <dglw/dglw.hpp>

namespace dglw {

typedef std::unordered_map<std::string, ShaderPtr> ShaderMap;
typedef std::unordered_map<std::string, ProgramPtr> ProgramMap;

class ResourceManager {
   public:
      ResourceManager();

      const ProgramPtr& getVFProgram(const std::string& vertfile, const std::string& fragfile);
      const ShaderPtr& getShader(const std::string& filename, const dglw::Shader::Type& type);
      const ShaderPtr& getVertexShader(const std::string& filename);
      const ShaderPtr& getFragmentShader(const std::string& filename);

      const ProgramPtr& getShaderProgram(const std::string& filename);

   private:
      std::vector<boost::filesystem::path> findDataPaths_();
      boost::filesystem::path findImageFile_(const boost::filesystem::path& filename);
      boost::filesystem::path findShaderFile_(const boost::filesystem::path& filename);
      std::vector<char> readIntoVector_(const boost::filesystem::path& filename);

      Shader loadShader_(const boost::filesystem::path& filename, const Shader::Type& type);

      ShaderMap shaders_;
      ProgramMap programs_;

      std::vector<boost::filesystem::path> hardcoded_data_paths;
      std::vector<boost::filesystem::path> data_paths_;
};

typedef std::shared_ptr<ResourceManager> ResourceManagerPtr;

} /* namespace dglw */

#endif /* DGLW_RESOURCEMANAGER_HPP_ */
