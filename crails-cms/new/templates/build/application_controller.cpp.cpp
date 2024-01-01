#include <sstream>
#include "crails/render_target.hpp"
#include "crails/shared_vars.hpp"
#include "crails/template.hpp"
#include <crails/cli/conventions.hpp>

class render_ProjectControllersApplicationCpp : public Crails::Template
{
public:
  render_ProjectControllersApplicationCpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars) :
    Crails::Template(renderer, target, vars), 
    classname( Crails::naming_convention.classnames("ApplicationController"))
  {}

  void render()
  {
ecpp_stream << "#include <crails/cms/views/layout.hpp>\n#include \"application.hpp\"\n#include \"lib/odb/application-odb.hxx\"\n\nusing namespace std;\n" << ( classname );
  ecpp_stream << "::" << ( classname );
  ecpp_stream << "(Crails::Context& context) : Crails::Cms::Controller(context)\n{\n}\n\nshared_ptr<Crails::Cms::Settings> " << ( classname );
  ecpp_stream << "::find_settings()\n{\n  if (!settings)\n  {\n    shared_ptr<" << ( Crails::naming_convention.classnames("Settings") );
  ecpp_stream << "> result;\n\n    database.find_one(result);\n    settings = result;\n  }\n  return settings;\n}\n\nvoid " << ( classname );
  ecpp_stream << "::initialize()\n{\n  Crails::Cms::Controller::initialize();\n  if (settings)\n    vars[\"layout\"] = settings->get_layout().get_layout_path();\n}\n";
    std::string _out_buffer = ecpp_stream.str();
    _out_buffer = this->apply_post_render_filters(_out_buffer);
    this->target.set_body(_out_buffer);
  }
private:
  std::stringstream ecpp_stream;
  std::string classname;
};

void render_project_controllers_application_cpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_ProjectControllersApplicationCpp(renderer, target, vars).render();
}