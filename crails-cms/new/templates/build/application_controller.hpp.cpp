#include <sstream>
#include "crails/render_target.hpp"
#include "crails/shared_vars.hpp"
#include "crails/template.hpp"
#include <crails/cli/conventions.hpp>

class render_ProjectControllersApplicationHpp : public Crails::Template
{
public:
  render_ProjectControllersApplicationHpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars) :
    Crails::Template(renderer, target, vars), 
    classname( Crails::naming_convention.classnames("ApplicationController"))
  {}

  void render()
  {
ecpp_stream << "#pragma once\n#include <crails/cms/controllers/controller.hpp>\n#include \"app/models/" << ( Crails::naming_convention.filenames("settings") );
  ecpp_stream << ".hpp\"\n\nclass " << ( classname );
  ecpp_stream << " : public Crails::Cms::Controller\n{\npublic:\n  void initialize();\nprotected:\n  " << ( classname );
  ecpp_stream << "(Crails::Context&);\n\n  virtual std::shared_ptr<Crails::Cms::Settings> find_settings() override;\n};\n";
    std::string _out_buffer = ecpp_stream.str();
    _out_buffer = this->apply_post_render_filters(_out_buffer);
    this->target.set_body(_out_buffer);
  }
private:
  std::stringstream ecpp_stream;
  std::string classname;
};

void render_project_controllers_application_hpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_ProjectControllersApplicationHpp(renderer, target, vars).render();
}