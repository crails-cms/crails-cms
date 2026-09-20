#include <crails/template_stream.hpp>
#include "crails/render_target.hpp"
#include "crails/shared_vars.hpp"
#include "crails/template.hpp"
#include <crails/cli/conventions.hpp>

class render_ProjectConfigCmsMenusHpp : public Crails::Template
{
public:
  render_ProjectConfigCmsMenusHpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars) :
    Crails::Template(renderer, target, vars), 
    menu_classname( Crails::naming_convention.classnames("Menu"))
  {}

  void render()
  {
    ecpp_stream.reserve(946);
    // BEGIN TEMPLATE BODY
ecpp_stream << "#pragma once\n#include <crails/cms/views/menu.hpp>\n#include \"app/models/menu.hpp\"\n#include \"autogen/odb/application-odb.hpp\"\n\nclass ApplicationMenus : public Crails::Cms::MenuManager\n{\n  SINGLETON_IMPLEMENTATION(ApplicationMenus, Crails::Cms::MenuManager)\n\n  std::shared_ptr<Crails::Cms::Menu> find_menu(const std::string& name) const override\n  {\n    return find_menu_with_type<" << ( menu_classname );
  ecpp_stream << ">(name);\n  }\n};\n";
    // END TEMPLATE BODY
    std::string _out_buffer = std::move(ecpp_stream).extract();
    this->target.set_body(this->apply_post_render_filters(std::move(_out_buffer)));
  }
private:
  Crails::TemplateStream ecpp_stream;
  std::string menu_classname;
};

void render_project_config_cms_menus_hpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_ProjectConfigCmsMenusHpp(renderer, target, vars).render();
}