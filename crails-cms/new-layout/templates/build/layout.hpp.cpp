#include <sstream>
#include "crails/render_target.hpp"
#include "crails/shared_vars.hpp"
#include "crails/template.hpp"
#include <crails/cli/conventions.hpp>

class render_LayoutPluginLayoutHpp : public Crails::Template
{
public:
  render_LayoutPluginLayoutHpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars) :
    Crails::Template(renderer, target, vars), 
    project_name(Crails::cast<std::string>(vars, "project_name")), 
    classname( Crails::naming_convention.classnames(project_name))
  {}

  void render()
  {
ecpp_stream << "#pragma once\n#include <crails/cms/views/layout.hpp>\n\nstruct " << ( classname );
  ecpp_stream << " : public Crails::Cms::Layout\n{\n  " << ( classname );
  ecpp_stream << "();\n\n  const Crails::Cms::Style& get_style() const override;\n};\n";
    this->target.set_body(ecpp_stream.str());
  }
private:
  std::stringstream ecpp_stream;
  std::string project_name;
  std::string classname;
};

void render_layout_plugin_layout_hpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_LayoutPluginLayoutHpp(renderer, target, vars).render();
}