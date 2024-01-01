#include <sstream>
#include "crails/render_target.hpp"
#include "crails/shared_vars.hpp"
#include "crails/template.hpp"
#include <crails/utils/semantics.hpp>
#include <crails/cli/conventions.hpp>

class render_ProjectModelsTraits : public Crails::Template
{
public:
  render_ProjectModelsTraits(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars) :
    Crails::Template(renderer, target, vars), 
    traits_classname( Crails::naming_convention.classnames("application_traits")), 
    user_classname( Crails::naming_convention.classnames("user")), 
    user_filename( Crails::naming_convention.filenames("user")), 
    group_classname( Crails::naming_convention.classnames("user_group")), 
    group_filename( Crails::naming_convention.filenames("user_group"))
  {}

  void render()
  {
ecpp_stream << "#pragma once\n#include \"" << ( user_filename );
  ecpp_stream << ".hpp\"\n#include \"" << ( group_filename );
  ecpp_stream << ".hpp\"\n\nstruct " << ( traits_classname );
  ecpp_stream << "\n{\n  typedef " << ( user_classname );
  ecpp_stream << " UserModel;\n  typedef " << ( group_classname );
  ecpp_stream << " UserGroupModel;\n};\n";
    std::string _out_buffer = ecpp_stream.str();
    _out_buffer = this->apply_post_render_filters(_out_buffer);
    this->target.set_body(_out_buffer);
  }
private:
  std::stringstream ecpp_stream;
  std::string traits_classname;
  std::string user_classname;
  std::string user_filename;
  std::string group_classname;
  std::string group_filename;
};

void render_project_models_traits(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_ProjectModelsTraits(renderer, target, vars).render();
}