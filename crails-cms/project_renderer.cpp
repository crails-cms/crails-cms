#include "project_renderer.hpp"
#define declare_renderer(name) \
  void render_##name(const Crails::Renderer&, Crails::RenderTarget&, Crails::SharedVars&);
#define add_renderer(path, name) \
  templates.insert(pair<string, Generator>(path, render_##name))

using namespace std;

const vector<string>& ProjectRenderer::get_mimetypes() const
{
  static const vector<string> mimetypes;
  return mimetypes;
}

declare_renderer(project_app_main)
declare_renderer(project_app_routes_cpp)
declare_renderer(project_config_renderers)
declare_renderer(project_config_request_pipe)
declare_renderer(project_config_cms_layouts_hpp)
declare_renderer(project_config_cms_layouts_cpp)
declare_renderer(project_config_cms_menus_hpp)
declare_renderer(project_config_cms_plugins_hpp)
declare_renderer(project_config_cms_plugins_cpp)
declare_renderer(project_models_traits)
declare_renderer(project_models_model_hpp)
declare_renderer(project_models_model_cpp)
declare_renderer(project_models_resource_traits_hpp)
declare_renderer(project_models_tag_query_hpp)
declare_renderer(project_models_user_hpp)
declare_renderer(project_models_user_group_hpp)
declare_renderer(project_models_user_group_cpp)
declare_renderer(project_models_permission_rule_hpp)
declare_renderer(project_models_permission_rule_cpp)
declare_renderer(project_models_homepage_hpp)
declare_renderer(project_controllers_application_hpp)
declare_renderer(project_controllers_application_cpp)
declare_renderer(project_controllers_signin_cpp)
declare_renderer(project_controllers_signin_hpp)
declare_renderer(project_controllers_home_hpp)
declare_renderer(project_controllers_home_cpp)
declare_renderer(project_controllers_resource_hpp)
declare_renderer(project_controllers_admin_application_hpp)
declare_renderer(project_controllers_admin_resource_hpp)
declare_renderer(project_controllers_admin_settings_hpp)
declare_renderer(project_controllers_admin_opengraph_hpp)

declare_renderer(layout_plugin_crailsfile)
declare_renderer(layout_plugin_cmakelists_txt)
declare_renderer(layout_plugin_webpack_config_js)
declare_renderer(layout_plugin_package_json)
declare_renderer(layout_plugin_main_cpp)
declare_renderer(layout_plugin_prebuild_sh)
declare_renderer(layout_plugin_style_hpp)
declare_renderer(layout_plugin_layout_hpp)
declare_renderer(layout_plugin_layout_cpp)
declare_renderer(layout_plugin_layout_html)
declare_renderer(layout_plugin_layout_scss)
declare_renderer(layout_plugin_admin_scss)
declare_renderer(layout_plugin_fonts_scss)
declare_renderer(layout_plugin_theme_scss)
declare_renderer(layout_plugin_editor_js)
declare_renderer(layout_plugin_index_js)

declare_renderer(plugin_crailsfile)
declare_renderer(plugin_cmakelists_txt)
declare_renderer(plugin_prebuild_sh)
declare_renderer(plugin_package_json)
declare_renderer(plugin_app_main_cpp)
declare_renderer(plugin_app_routes_cpp)
declare_renderer(plugin_app_renderers_cpp)
declare_renderer(plugin_app_database_cpp)
declare_renderer(plugin_webpack_config_js)

ProjectRenderer::ProjectRenderer()
{
  add_renderer("app/main.cpp", project_app_main);
  add_renderer("app/routes.cpp", project_app_routes_cpp);
  add_renderer("config/renderers.cpp", project_config_renderers);
  add_renderer("config/request_pipe.cpp", project_config_request_pipe);
  add_renderer("config/cms/layouts.hpp", project_config_cms_layouts_hpp);
  add_renderer("config/cms/layouts.cpp", project_config_cms_layouts_cpp);
  add_renderer("config/cms/menus.hpp", project_config_cms_menus_hpp);
  add_renderer("config/cms/plugins.hpp", project_config_cms_plugins_hpp);
  add_renderer("config/cms/plugins.cpp", project_config_cms_plugins_cpp);
  add_renderer("app/models/traits.hpp", project_models_traits);
  add_renderer("app/models/model.hpp", project_models_model_hpp);
  add_renderer("app/models/model.cpp", project_models_model_cpp);
  add_renderer("app/models/resource_traits.hpp", project_models_resource_traits_hpp);
  add_renderer("app/models/tag_query.hpp", project_models_tag_query_hpp);
  add_renderer("app/models/user.hpp", project_models_user_hpp);
  add_renderer("app/models/user_group.hpp", project_models_user_group_hpp);
  add_renderer("app/models/user_group.cpp", project_models_user_group_cpp);
  add_renderer("app/models/permission_rule.hpp", project_models_permission_rule_hpp);
  add_renderer("app/models/permission_rule.cpp", project_models_permission_rule_cpp);
  add_renderer("app/models/homepage.hpp", project_models_homepage_hpp);
  add_renderer("app/controllers/application.hpp", project_controllers_application_hpp);
  add_renderer("app/controllers/application.cpp", project_controllers_application_cpp);
  add_renderer("app/controllers/signin.hpp", project_controllers_signin_hpp);
  add_renderer("app/controllers/signin.cpp", project_controllers_signin_cpp);
  add_renderer("app/controllers/home.hpp", project_controllers_home_hpp);
  add_renderer("app/controllers/home.cpp", project_controllers_home_cpp);
  add_renderer("app/controllers/resource.hpp", project_controllers_resource_hpp);
  add_renderer("app/controllers/admin/application.hpp", project_controllers_admin_application_hpp);
  add_renderer("app/controllers/admin/resource.hpp", project_controllers_admin_resource_hpp);
  add_renderer("app/controllers/admin/settings.hpp", project_controllers_admin_settings_hpp);
  add_renderer("app/controllers/admin/opengraph.hpp", project_controllers_admin_opengraph_hpp);

  add_renderer("layouts/.crails", layout_plugin_crailsfile);
  add_renderer("layouts/CMakeLists.txt", layout_plugin_cmakelists_txt);
  add_renderer("layouts/package.json", layout_plugin_package_json);
  add_renderer("layouts/webpack.config.js", layout_plugin_webpack_config_js);
  add_renderer("layouts/prebuild.sh", layout_plugin_prebuild_sh);
  add_renderer("layouts/src/main.cpp", layout_plugin_main_cpp);
  add_renderer("layouts/src/style.hpp", layout_plugin_style_hpp);
  add_renderer("layouts/src/layout.hpp", layout_plugin_layout_hpp);
  add_renderer("layouts/src/layout.cpp", layout_plugin_layout_cpp);
  add_renderer("layouts/views/layouts/themes/layout.html", layout_plugin_layout_html);
  add_renderer("layouts/javascripts/editor.js", layout_plugin_editor_js);
  add_renderer("layouts/javascripts/index.js", layout_plugin_index_js);
  add_renderer("layouts/stylesheets/admin.scss", layout_plugin_admin_scss);
  add_renderer("layouts/stylesheets/layout.scss", layout_plugin_layout_scss);
  add_renderer("layouts/stylesheets/_fonts.scss", layout_plugin_fonts_scss);
  add_renderer("layouts/stylesheets/_theme.scss", layout_plugin_theme_scss);

  add_renderer("plugins/.crails", plugin_crailsfile);
  add_renderer("plugins/CMakeLists.txt", plugin_cmakelists_txt);
  add_renderer("plugins/prebuild.sh", plugin_prebuild_sh);
  add_renderer("plugins/package.json", plugin_package_json);
  add_renderer("plugins/app/main.cpp", plugin_app_main_cpp);
  add_renderer("plugins/app/routes.cpp", plugin_app_routes_cpp);
  add_renderer("plugins/app/renderers.cpp", plugin_app_renderers_cpp);
  add_renderer("plugins/app/database.cpp", plugin_app_database_cpp);
  add_renderer("plugins/webpack.config.js", plugin_webpack_config_js);
}
