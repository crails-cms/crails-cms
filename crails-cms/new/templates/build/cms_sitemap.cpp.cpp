#include <crails/template_stream.hpp>
#include "crails/render_target.hpp"
#include "crails/shared_vars.hpp"
#include "crails/template.hpp"

class render_ProjectConfigCmsSitemapCpp : public Crails::Template
{
public:
  render_ProjectConfigCmsSitemapCpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars) :
    Crails::Template(renderer, target, vars)
  {}

  void render()
  {
    ecpp_stream.reserve(1496);
    // BEGIN TEMPLATE BODY
ecpp_stream << "#include \"sitemap.hpp\"\n#include <crails/cms/controllers/sitemap.hpp>\n#include <crails/cms/sitemap_resource.hpp>\n#include <crails/odb/connection.hpp>\n#include \"app/controllers/page.hpp\"\n#include \"app/autogen/odb/application-odb.hpp\"\n\nusing namespace std;\nusing namespace Crails;\n\nshared_ptr<Cms::Settings> ApplicationSiteMap::find_settings() const\n{\n  Crails::Odb::ConnectionHandle database;\n  shared_ptr<Settings> result;\n\n  if (!database.find_one(result))\n    result = make_shared<Settings>();\n  return result;\n}\n\nvoid ApplicationSiteMap::initialize()\n{\n  add_index(\n    \"Pages\",\n    make_unique<Cms::SiteMap::ResourceIndex<PageController, PageTraits>>()\n  );\n  initialize_plugin_indexes();\n}\n";
    // END TEMPLATE BODY
    std::string _out_buffer = std::move(ecpp_stream).extract();
    this->target.set_body(this->apply_post_render_filters(std::move(_out_buffer)));
  }
private:
  Crails::TemplateStream ecpp_stream;
};

void render_project_config_cms_sitemap_cpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_ProjectConfigCmsSitemapCpp(renderer, target, vars).render();
}