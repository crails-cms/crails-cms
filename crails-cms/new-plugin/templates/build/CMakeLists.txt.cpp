#include <sstream>
#include "crails/render_target.hpp"
#include "crails/shared_vars.hpp"
#include "crails/template.hpp"

class render_PluginCmakelistsTxt : public Crails::Template
{
public:
  render_PluginCmakelistsTxt(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars) :
    Crails::Template(renderer, target, vars), 
    project_name(Crails::cast<std::string>(vars, "project_name"))
  {}

  void render()
  {
ecpp_stream << "cmake_minimum_required(VERSION 3.5)\n\nproject(crails-cms-" << ( project_name );
  ecpp_stream << "-plugin)\n\nset(CMAKE_SHARED_LINKER_FLAGS \"${CMAKE_SHARED_LINKER_FLAGS} -Wl,--no-undefined\")\n\nfind_package(PkgConfig)\npkg_check_modules(CRAILS_CMS REQUIRED\n  libcrails-cms>=2.0.0\n  libcrails-templates>=2.0.0\n  libcrails-json-views>=2.0.0\n  libcrails-html-views>=2.0.0\n)\n\ninclude_directories(. ../.. ${CRAILS_CMS_INCLUDE_DIRS})\nlink_directories(../../build)\n\nset(ENV{CRAILS_CMS_INCLUDE_DIRS} \"${CRAILS_CMS_INCLUDE_DIRS}\")\nexecute_process(COMMAND ./prebuild.sh WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})\n\nfile(GLOB_RECURSE plugin_files\n  app/*.cpp app/*.cxx\n  lib/*.cpp lib/*.cxx)\n\nadd_library(" << ( project_name );
  ecpp_stream << " SHARED ${plugin_files})\nadd_definitions(-DWITH_ODB)\nset_target_properties(" << ( project_name );
  ecpp_stream << " PROPERTIES ENABLE_EXPORTS ON)\nset_target_properties(" << ( project_name );
  ecpp_stream << " PROPERTIES PREFIX \"\")\ntarget_link_libraries(" << ( project_name );
  ecpp_stream << "\n  ${CRAILS_CMS_LIBRARIES}\n  crails-app)\ninstall(TARGETS " << ( project_name );
  ecpp_stream << " LIBRARY DESTINATION lib/libcrails-cms)\n";
    std::string _out_buffer = ecpp_stream.str();
    _out_buffer = this->apply_post_render_filters(_out_buffer);
    this->target.set_body(_out_buffer);
  }
private:
  std::stringstream ecpp_stream;
  std::string project_name;
};

void render_plugin_cmakelists_txt(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_PluginCmakelistsTxt(renderer, target, vars).render();
}