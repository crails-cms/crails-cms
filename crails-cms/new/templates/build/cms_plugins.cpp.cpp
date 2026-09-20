#include <crails/template_stream.hpp>
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
    ecpp_stream.reserve(778);
    // BEGIN TEMPLATE BODY
ecpp_stream << "#include <crails/odb/connection.hpp>\n#include \"plugins.hpp\"\n#include \"app/models/settings.hpp\"\n#include \"app/autogen/odb/application-odb.hpp\"\n\nApplicationPlugins::ApplicationPlugins()\n{\n  Crails::Odb::Connection database;\n  std::shared_ptr<Settings> settings;\n\n  database.find_one(settings);\n  if (settings)\n    initialize(settings->get_plugins());\n}\n";
    // END TEMPLATE BODY
    std::string _out_buffer = std::move(ecpp_stream).extract();
    this->target.set_body(this->apply_post_render_filters(std::move(_out_buffer)));
  }
private:
  Crails::TemplateStream ecpp_stream;
};

void render_project_config_cms_plugins_cpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_ProjectConfigCmsPluginsCpp(renderer, target, vars).render();
}