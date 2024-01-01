#include <sstream>
#include "crails/render_target.hpp"
#include "crails/shared_vars.hpp"
#include "crails/template.hpp"

class render_PluginAppDatabaseCpp : public Crails::Template
{
public:
  render_PluginAppDatabaseCpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars) :
    Crails::Template(renderer, target, vars)
  {}

  void render()
  {
ecpp_stream << "#include <crails/odb/connection.hpp>\n\nvoid install_plugin_database()\n{\n  Crails::Odb::Connection database;\n\n  database.transaction.require(\"odb\");\n  // insert table creation here\n  // Example:\n  //\n  //  database.transaction.get_database().execute(\n  //    \"CREATE TABLE \\\"Plugin_ClassName\\\" ();\"\n  //  );\n  //\n  database.commit();\n}\n\nvoid uninstall_plugin_database()\n{\n  Crails::Odb::Connection database;\n\n  database.transaction.require(\"odb\");\n  // insert table droping here\n  database.commit();\n}\n";
    std::string _out_buffer = ecpp_stream.str();
    _out_buffer = this->apply_post_render_filters(_out_buffer);
    this->target.set_body(_out_buffer);
  }
private:
  std::stringstream ecpp_stream;
};

void render_plugin_app_database_cpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_PluginAppDatabaseCpp(renderer, target, vars).render();
}