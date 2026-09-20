#include <crails/template_stream.hpp>
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
    ecpp_stream.reserve(1052);
    // BEGIN TEMPLATE BODY
ecpp_stream << "#include <crails/odb/connection.hpp>\n\nvoid install_plugin_database()\n{\n  Crails::Odb::Connection database;\n\n  database.transaction.require(\"odb\");\n  // insert table creation here\n  // Example:\n  //\n  //  database.execute(\n  //    \"CREATE TABLE \\\"Plugin_ClassName\\\" ();\"\n  //  );\n  //\n  database.commit();\n}\n\nvoid uninstall_plugin_database()\n{\n  Crails::Odb::Connection database;\n\n  database.transaction.require(\"odb\");\n  // insert table droping here\n  database.commit();\n}\n";
    // END TEMPLATE BODY
    std::string _out_buffer = std::move(ecpp_stream).extract();
    this->target.set_body(this->apply_post_render_filters(std::move(_out_buffer)));
  }
private:
  Crails::TemplateStream ecpp_stream;
};

void render_plugin_app_database_cpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_PluginAppDatabaseCpp(renderer, target, vars).render();
}