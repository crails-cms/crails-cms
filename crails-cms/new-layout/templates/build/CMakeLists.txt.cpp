#include <sstream>
#include "crails/render_target.hpp"
#include "crails/shared_vars.hpp"
#include "crails/template.hpp"

class render_LayoutPluginCmakelistsTxt : public Crails::Template
{
public:
  render_LayoutPluginCmakelistsTxt(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars) :
    Crails::Template(renderer, target, vars), 
    project_name(Crails::cast<std::string>(vars, "project_name")), 
    library_name( project_name + "_layout")
  {}

  void render()
  {
ecpp_stream << "cmake_minimum_required(VERSION 3.0)\n\nproject(" << ( library_name );
  ecpp_stream << "_plugin)\n\nfind_package(PkgConfig)\npkg_check_modules(CRAILS_CMS REQUIRED libcrails-cms>=2.0.0)\n\ninclude_directories(${CRAILS_CMS_INCLUDE_DIRS} .)\n\nexecute_process(COMMAND ./prebuild.sh WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})\n\nfile(GLOB plugin_files\n  src/*.cpp\n  lib/*.cpp\n  lib/renderers/*.cpp\n  lib/renderers/html/*.cpp)\n\nadd_library(" << ( library_name );
  ecpp_stream << " SHARED ${plugin_files})\nset_property(TARGET " << ( library_name );
  ecpp_stream << " PROPERTY ENABLE_EXPORTS ON)\ntarget_link_libraries(" << ( library_name );
  ecpp_stream << " ${CRAILS_CMS_LIBRARIES})\n";
    std::string _out_buffer = ecpp_stream.str();
    _out_buffer = this->apply_post_render_filters(_out_buffer);
    this->target.set_body(_out_buffer);
  }
private:
  std::stringstream ecpp_stream;
  std::string project_name;
  std::string library_name;
};

void render_layout_plugin_cmakelists_txt(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_LayoutPluginCmakelistsTxt(renderer, target, vars).render();
}