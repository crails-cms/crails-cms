#include <sstream>
#include "crails/render_target.hpp"
#include "crails/shared_vars.hpp"
#include "crails/template.hpp"

class render_ProjectAppMain : public Crails::Template
{
public:
  render_ProjectAppMain(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars) :
    Crails::Template(renderer, target, vars)
  {}

  void render()
  {
ecpp_stream << "#include <crails/renderer.hpp>\n#include <crails/router.hpp>\n#include <crails/cipher.hpp>\n#include <crails/cms/views/style.hpp>\n#include <crails/cms/views/admin_menu.hpp>\n#include <crails/cms/routes.hpp>\n#include <crails/icons/fontawesome.hpp>\n#include \"config/cms/layouts.hpp\"\n#include \"config/cms/menus.hpp\"\n#include \"config/i18n.hpp\"\n#include \"config/renderers.hpp\"\n#include \"config/server.hpp\"\n\nusing namespace std;\nusing namespace Crails;\n\nint main(int argc, const char **argv)\n{\n  SingletonInstantiator<ApplicationI18n> translations;\n  SingletonInstantiator<ApplicationMenus> menus;\n  SingletonInstantiator<ApplicationLayouts> layouts;\n  SingletonInstantiator<ApplicationServer> server;\n  SingletonInstantiator<ApplicationRenderers> renderers;\n  SingletonInstantiator<Router> router;\n  SingletonInstantiator<Crails::Cms::Routes> cms_routes;\n  SingletonInstantiator<Crails::Cms::Style> style;\n  SingletonInstantiator<Crails::Cms::AdminMenu> admin_menu;\n  SingletonInstantiator<Crails::FontAwesome::V5> icon_theme;\n\n  router->initialize();\n  admin_menu->add_default_entries();\n  Cipher::initialize();\n  server->launch(argc, argv);\n  return 0;\n}\n";
    this->target.set_body(ecpp_stream.str());
  }
private:
  std::stringstream ecpp_stream;
};

void render_project_app_main(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_ProjectAppMain(renderer, target, vars).render();
}