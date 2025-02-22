#include <sstream>
#include "crails/render_target.hpp"
#include "crails/shared_vars.hpp"
#include "crails/template.hpp"
#include <crails/cli/conventions.hpp>
#define CLASSNAME(name) Crails::naming_convention.classnames(#name)
#define CMS_ROUTES(method, controller) (std::string("register_cms_routes(") + #method + ", " + CLASSNAME(controller) + ')')

class render_ProjectAppRoutesCpp : public Crails::Template
{
public:
  render_ProjectAppRoutesCpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars) :
    Crails::Template(renderer, target, vars)
  {}

  void render()
  {
ecpp_stream << "#include <crails/cms/routes.hpp>\n#include \"config/router.hpp\"\n#include \"autogen/odb/application-odb.hxx\"\n#include \"controllers/home.hpp\"\n#include \"controllers/signin.hpp\"\n#include \"controllers/page.hpp\"\n#include \"controllers/attachment.hpp\"\n#include \"controllers/admin/page.hpp\"\n#include \"controllers/admin/user.hpp\"\n#include \"controllers/admin/user_group.hpp\"\n#include \"controllers/admin/menu.hpp\"\n#include \"controllers/admin/settings.hpp\"\n#include \"controllers/admin/wizard.hpp\"\n#include \"controllers/admin/attachment.hpp\"\n#include \"controllers/admin/opengraph.hpp\"\n#define register_cms_routes(METHOD, CONTROLLER) \\\n  std::bind(&Crails::Cms::Routes::METHOD<CONTROLLER>, &cms_routes, std::ref(*this))\n\nApplicationRouter::ApplicationRouter()\n{\n  auto& cms_routes = Crails::Cms::Routes::singleton::require();\n\n  match_action(\"GET\", \"/\", " << ( CLASSNAME(HomeController) );
  ecpp_stream << ", index);\n  signin_actions(\"/session\", ::" << ( CLASSNAME(SessionController) );
  ecpp_stream << ");\n\n  Crails::Cms::initialize_cms_routes(*this);\n\n  scope(\"/pages\", " << ( CMS_ROUTES(register_page_routes, PageController) );
  ecpp_stream << ");\n\n  scope(\"/attachments\", [&]()\n  {\n    cms_routes.register_attachments_routes<" << ( CLASSNAME(AttachmentController) );
  ecpp_stream << ">(*this);\n  });\n\n  scope(\"/admin\", [&]()\n  {\n    match_action(\"GET\", \"/\", " << ( CLASSNAME(AdminSettingsController) );
  ecpp_stream << ", redirect_to_root);\n    scope(\"/settings\",    " << ( CMS_ROUTES(register_settings_admin_routes,    AdminSettingsController) );
  ecpp_stream << ");\n    scope(\"/attachments\", " << ( CMS_ROUTES(register_attachments_admin_routes, AdminAttachmentController) );
  ecpp_stream << ");\n    scope(\"/menus\",       " << ( CMS_ROUTES(register_menus_admin_routes,       AdminMenuController) );
  ecpp_stream << ");\n    scope(\"/users\",       " << ( CMS_ROUTES(register_users_admin_routes,       AdminUserController) );
  ecpp_stream << ");\n    scope(\"/user_groups\", " << ( CMS_ROUTES(register_user_groups_admin_routes, AdminUserGroupController) );
  ecpp_stream << ");\n    scope(\"/pages\",       [&]() { cms_routes.register_page_admin_routes<" << ( CLASSNAME(PageController) );
  ecpp_stream << ", " << ( CLASSNAME(AdminPageController) );
  ecpp_stream << ">(*this); });\n    scope(\"/wizard\",      " << ( CMS_ROUTES(register_wizard_routes,            AdminWizardController) );
  ecpp_stream << ");\n    cms_routes.register_opengraph_routes<OpenGraphController>(*this);\n  });\n}\n";
    std::string _out_buffer = ecpp_stream.str();
    _out_buffer = this->apply_post_render_filters(_out_buffer);
    this->target.set_body(_out_buffer);
  }
private:
  std::stringstream ecpp_stream;
};

void render_project_app_routes_cpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_ProjectAppRoutesCpp(renderer, target, vars).render();
}