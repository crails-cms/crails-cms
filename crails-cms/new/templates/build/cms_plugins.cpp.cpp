#include <sstream>
#include "crails/render_target.hpp"
#include "crails/shared_vars.hpp"
#include "crails/template.hpp"

class render_ProjectConfigCmsPluginsCpp : public Crails::Template
{
public:
  render_ProjectConfigCmsPluginsCpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars) :
    Crails::Template(renderer, target, vars)
  {}

  void render()
  {
ecpp_stream << "#include <crails/odb/connection.hpp>\n#include \"plugins.hpp\"\n#include \"app/models/settings.hpp\"\n#include \"autogen/odb/application-odb.hxx\"\n\nApplicationPlugins::ApplicationPlugins()\n{\n  Crails::Odb::Connection database;\n  std::shared_ptr<Settings> settings;\n\n  database.find_one(settings);\n  if (settings)\n    initialize(settings->get_plugins());\n}\n";
    std::string _out_buffer = ecpp_stream.str();
    _out_buffer = this->apply_post_render_filters(_out_buffer);
    this->target.set_body(_out_buffer);
  }
private:
  std::stringstream ecpp_stream;
};

void render_project_config_cms_plugins_cpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_ProjectConfigCmsPluginsCpp(renderer, target, vars).render();
}