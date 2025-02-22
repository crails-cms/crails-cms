#include <sstream>
#include "crails/render_target.hpp"
#include "crails/shared_vars.hpp"
#include "crails/template.hpp"
#include <crails/utils/semantics.hpp>
#include <crails/cli/conventions.hpp>

class render_ProjectControllersResourceHpp : public Crails::Template
{
public:
  render_ProjectControllersResourceHpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars) :
    Crails::Template(renderer, target, vars), 
    resource_name(Crails::cast< std::string >(vars, "resource_name")), 
    classname( Crails::naming_convention.classnames(resource_name + "_controller")), 
    super( "Crails::Cms::"
  + Crails::camelize(resource_name) + "Controller"
  + '<' + Crails::naming_convention.classnames(resource_name + "_traits")
  + ", " + Crails::naming_convention.classnames("ApplicationController")
  + '>')
  {}

  void render()
  {
ecpp_stream << "#pragma once\n#include \"application.hpp\"\n#include <crails/cms/controllers/" << ( resource_name );
  ecpp_stream << ".hpp>\n#include \"app/models/" << ( Crails::naming_convention.filenames(resource_name + "_traits") );
  ecpp_stream << ".hpp\"\n\nclass " << ( classname );
  ecpp_stream << " : public " << ( super );
  ecpp_stream << "\n{\n  typedef " << ( super );
  ecpp_stream << " Super;\npublic:\n  " << ( classname );
  ecpp_stream << "(Crails::Context& context) : Super(context)\n  {\n  }\n};\n";
    std::string _out_buffer = ecpp_stream.str();
    _out_buffer = this->apply_post_render_filters(_out_buffer);
    this->target.set_body(_out_buffer);
  }
private:
  std::stringstream ecpp_stream;
  std::string resource_name;
  std::string classname;
  std::string super;
};

void render_project_controllers_resource_hpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_ProjectControllersResourceHpp(renderer, target, vars).render();
}