#include <sstream>
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
ecpp_stream << "#pragma once\n#include <crails/cms/views/menu.hpp>\n#include \"app/models/menu.hpp\"\n#include \"lib/odb/application-odb.hxx\"\n\nclass ApplicationMenus : public Crails::Cms::MenuManager\n{\n  SINGLETON_IMPLEMENTATION(ApplicationMenus, Crails::Cms::MenuManager)\n\n  std::shared_ptr<Crails::Cms::Menu> find_menu(const std::string& name) const override\n  {\n    return find_menu_with_type<" << ( menu_classname );
  ecpp_stream << ">(name);\n  }\n};\n";
    std::string _out_buffer = ecpp_stream.str();
    _out_buffer = this->apply_post_render_filters(_out_buffer);
    this->target.set_body(_out_buffer);
  }
private:
  std::stringstream ecpp_stream;
  std::string menu_classname;
};

void render_project_config_cms_menus_hpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_ProjectConfigCmsMenusHpp(renderer, target, vars).render();
}