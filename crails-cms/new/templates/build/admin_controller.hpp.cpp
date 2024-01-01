#include <sstream>
#include "crails/render_target.hpp"
#include "crails/shared_vars.hpp"
#include "crails/template.hpp"
#include <crails/cli/conventions.hpp>

class render_ProjectControllersAdminApplicationHpp : public Crails::Template
{
public:
  render_ProjectControllersAdminApplicationHpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars) :
    Crails::Template(renderer, target, vars), 
    classname( Crails::naming_convention.classnames("AdminApplicationController")), 
    super( Crails::naming_convention.classnames("ApplicationController"))
  {}

  void render()
  {
ecpp_stream << "#pragma once\n#include \"../application.hpp\"\n\nclass " << ( classname );
  ecpp_stream << " : public " << ( super );
  ecpp_stream << "\n{\npublic:\n  static constexpr const char* scope = \"/admin\";\n\n  " << ( classname );
  ecpp_stream << "(Crails::Context& context) : " << ( super );
  ecpp_stream << "(context)\n  {\n  }\n\n  void initialize()\n  {\n    " << ( super );
  ecpp_stream << "::initialize();\n    vars[\"layout\"] = std::string(\"layouts/admin\");\n  }\n};\n";
    std::string _out_buffer = ecpp_stream.str();
    _out_buffer = this->apply_post_render_filters(_out_buffer);
    this->target.set_body(_out_buffer);
  }
private:
  std::stringstream ecpp_stream;
  std::string classname;
  std::string super;
};

void render_project_controllers_admin_application_hpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_ProjectControllersAdminApplicationHpp(renderer, target, vars).render();
}