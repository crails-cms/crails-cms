#include <sstream>
#include "crails/render_target.hpp"
#include "crails/shared_vars.hpp"
#include "crails/template.hpp"

class render_PluginAppMainCpp : public Crails::Template
{
public:
  render_PluginAppMainCpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars) :
    Crails::Template(renderer, target, vars), 
    project_name(Crails::cast<std::string>(vars, "project_name"))
  {}

  void render()
  {
ecpp_stream << "#include <string>\n\nvoid initialize_plugin_routes();\nvoid initialize_plugin_renderers();\nvoid install_plugin_database();\nvoid uninstall_plugin_database();\n\nextern unsigned char " << ( project_name );
  ecpp_stream << "_plugin_application_js[];\nextern unsigned int  " << ( project_name );
  ecpp_stream << "_plugin_application_js_len;\nextern unsigned char " << ( project_name );
  ecpp_stream << "_plugin_admin_js[];\nextern unsigned int  " << ( project_name );
  ecpp_stream << "_plugin_admin_js_len;\n\nextern \"C\"\n{\n  void initialize()\n  {\n    initialize_plugin_routes();\n    initialize_plugin_renderers();\n  }\n\n  void install()\n  {\n    install_plugin_database();\n  }\n\n  void uninstall()\n  {\n    uninstall_plugin_database();\n  }\n\n  std::string_view plugin_javascript()\n  {\n    return std::string_view(\n      reinterpret_cast<const char*>(" << ( project_name );
  ecpp_stream << "_plugin_application_js),\n      " << ( project_name );
  ecpp_stream << "_plugin_application_js_len\n    );\n  }\n\n  std::string_view plugin_admin_javascript()\n  {\n    return std::string_view(\n      reinterpret_cast<const char*>(" << ( project_name );
  ecpp_stream << "_plugin_admin_js),\n      " << ( project_name );
  ecpp_stream << "_plugin_admin_js_len\n    );\n  }\n}\n";
    std::string _out_buffer = ecpp_stream.str();
    _out_buffer = this->apply_post_render_filters(_out_buffer);
    this->target.set_body(_out_buffer);
  }
private:
  std::stringstream ecpp_stream;
  std::string project_name;
};

void render_plugin_app_main_cpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_PluginAppMainCpp(renderer, target, vars).render();
}