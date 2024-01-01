#include <sstream>
#include "crails/render_target.hpp"
#include "crails/shared_vars.hpp"
#include "crails/template.hpp"
#include <crails/cli/conventions.hpp>

class render_ProjectControllersHomeHpp : public Crails::Template
{
public:
  render_ProjectControllersHomeHpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars) :
    Crails::Template(renderer, target, vars), 
    classname( Crails::naming_convention.classnames("HomeController")), 
    parent_class( Crails::naming_convention.classnames("ApplicationController"))
  {}

  void render()
  {
ecpp_stream << "#pragma once\n#include \"application.hpp\"\n#include \"../models/page.hpp\"\n\nclass " << ( classname );
  ecpp_stream << " : public " << ( parent_class );
  ecpp_stream << "\n{\npublic:\n  " << ( classname );
  ecpp_stream << "(Crails::Context&);\n\n  void initialize();\n  void index();\n\nprivate:\n  std::shared_ptr<Crails::Cms::Settings> find_settings() override;\n\n  std::shared_ptr<" << ( Crails::naming_convention.classnames("Page") );
  ecpp_stream << "> page;\n};\n";
    std::string _out_buffer = ecpp_stream.str();
    _out_buffer = this->apply_post_render_filters(_out_buffer);
    this->target.set_body(_out_buffer);
  }
private:
  std::stringstream ecpp_stream;
  std::string classname;
  std::string parent_class;
};

void render_project_controllers_home_hpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_ProjectControllersHomeHpp(renderer, target, vars).render();
}