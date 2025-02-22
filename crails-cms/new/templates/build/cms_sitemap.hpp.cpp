#include <sstream>
#include "crails/render_target.hpp"
#include "crails/shared_vars.hpp"
#include "crails/template.hpp"

class render_ProjectConfigCmsSitemapHpp : public Crails::Template
{
public:
  render_ProjectConfigCmsSitemapHpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars) :
    Crails::Template(renderer, target, vars)
  {}

  void render()
  {
ecpp_stream << "#pragma once\n#include <crails/cms/controllers/sitemap.hpp>\n\nclass ApplicationSiteMap : public Crails::Cms::SiteMap::Controller\n{\n  SINGLETON_IMPLEMENTATION(ApplicationSiteMap, Crails::Cms::SiteMap::Controller)\n\n  std::shared_ptr<Crails::Cms::Settings> find_settings() const override;\npublic:\n  void initialize();\n};\n";
    std::string _out_buffer = ecpp_stream.str();
    _out_buffer = this->apply_post_render_filters(_out_buffer);
    this->target.set_body(_out_buffer);
  }
private:
  std::stringstream ecpp_stream;
};

void render_project_config_cms_sitemap_hpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_ProjectConfigCmsSitemapHpp(renderer, target, vars).render();
}