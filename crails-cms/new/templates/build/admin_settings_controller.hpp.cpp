#include <sstream>
#include "crails/render_target.hpp"
#include "crails/shared_vars.hpp"
#include "crails/template.hpp"
#include <crails/cli/conventions.hpp>

class render_ProjectControllersAdminSettingsHpp : public Crails::Template
{
public:
  render_ProjectControllersAdminSettingsHpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars) :
    Crails::Template(renderer, target, vars), 
    class_name( Crails::naming_convention.classnames("AdminSettingsController")), 
    super( "Crails::Cms::AdminSettingsController<"
  + Crails::naming_convention.classnames("User") + ", "
  + Crails::naming_convention.classnames("Settings") + ", "
  + Crails::naming_convention.classnames("Page") + ", "
  + Crails::naming_convention.classnames("AdminApplicationController")
  + '>')
  {}

  void render()
  {
ecpp_stream << "#pragma once\n#include <crails/cms/controllers/admin/settings.hpp>\n#include \"application.hpp\"\n#include \"app/models/user.hpp\"\n#include \"app/models/settings.hpp\"\n#include \"app/models/page.hpp\"\n\nclass " << ( class_name );
  ecpp_stream << " : public " << ( super );
  ecpp_stream << "\n{\n  typedef " << ( super );
  ecpp_stream << " Super;\npublic:\n  " << ( class_name );
  ecpp_stream << "(Crails::Context& context) : Super(context)\n  {\n    vars[\"local_route\"] = \"/admin/settings\";\n  }\n};\n";
    std::string _out_buffer = ecpp_stream.str();
    _out_buffer = this->apply_post_render_filters(_out_buffer);
    this->target.set_body(_out_buffer);
  }
private:
  std::stringstream ecpp_stream;
  std::string class_name;
  std::string super;
};

void render_project_controllers_admin_settings_hpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_ProjectControllersAdminSettingsHpp(renderer, target, vars).render();
}