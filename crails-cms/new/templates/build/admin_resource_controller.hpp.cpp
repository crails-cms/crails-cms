#include <sstream>
#include "crails/render_target.hpp"
#include "crails/shared_vars.hpp"
#include "crails/template.hpp"
#include <crails/utils/semantics.hpp>
#include <crails/cli/conventions.hpp>

class render_ProjectControllersAdminResourceHpp : public Crails::Template
{
public:
  render_ProjectControllersAdminResourceHpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars) :
    Crails::Template(renderer, target, vars), 
    resource_name(Crails::cast< std::string >(vars, "resource_name")), 
    local_route(Crails::cast< std::string >(vars, "local_route")), 
    classname( Crails::naming_convention.classnames("admin_" + resource_name + "_controller")), 
    resource_traits(Crails::cast< std::string >(vars, "resource_traits",  resource_name + "_traits")), 
    traits_classname( Crails::naming_convention.classnames(resource_traits)), 
    super( "Crails::Cms::Admin"
  + Crails::camelize(resource_name)
  + "Controller<" + traits_classname + ", "
  + Crails::naming_convention.classnames("AdminApplicationController")
  + '>')
  {}

  void render()
  {
ecpp_stream << "#pragma once\n#include <crails/cms/controllers/admin/" << ( resource_name );
  ecpp_stream << ".hpp>\n#include \"application.hpp\"\n#include \"app/models/" << ( Crails::naming_convention.filenames(resource_traits) );
  ecpp_stream << ".hpp\"\n\nclass " << ( classname );
  ecpp_stream << " : public " << ( super );
  ecpp_stream << "\n{\n  typedef " << ( super );
  ecpp_stream << " Super;\npublic:\n  static constexpr const char* scope = \"" << ( local_route );
  ecpp_stream << "\";\n\n  " << ( classname );
  ecpp_stream << "(Crails::Context& context) : Super(context)\n  {\n    vars[\"local_route\"] = std::string(Super::scope) + '/' + scope;\n  }\n};\n";
    std::string _out_buffer = ecpp_stream.str();
    _out_buffer = this->apply_post_render_filters(_out_buffer);
    this->target.set_body(_out_buffer);
  }
private:
  std::stringstream ecpp_stream;
  std::string resource_name;
  std::string local_route;
  std::string classname;
  std::string resource_traits;
  std::string traits_classname;
  std::string super;
};

void render_project_controllers_admin_resource_hpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_ProjectControllersAdminResourceHpp(renderer, target, vars).render();
}